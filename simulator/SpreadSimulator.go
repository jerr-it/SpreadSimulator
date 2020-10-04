package simulator

import (
	"SpreadSimulator/quadtree"
	"SpreadSimulator/util"
	"math/rand"
	"sync"
	"time"
)

//Simulator related constants
//TODO make them part of the config
const (
	EntitySpeedLimit      = 50.0
	CentralLocationsRange = 50
	ForcePeriod           = 1024
)

//SpreadSimulator struct
type SpreadSimulator struct {
	positions     []util.Vector2f
	velocities    []util.Vector2f
	accelerations []util.Vector2f
	healthData    []HealthData

	centralLocations []util.Vector2f
	forceDirection   int
	tick             int

	previousTime time.Time
	currentTime  time.Time
	Δt           float64

	Config config
	Stats  statistic

	currentQuadtree *quadtree.Quadtree
}

//NewSimulator creates a new simulator
func NewSimulator(config config) *SpreadSimulator {
	simulator := &SpreadSimulator{
		make([]util.Vector2f, config.EntityCount),
		make([]util.Vector2f, config.EntityCount),
		make([]util.Vector2f, config.EntityCount),
		make([]HealthData, config.EntityCount),
		make([]util.Vector2f, config.CentralLocations),
		1,
		0,
		time.Now(),
		time.Now(),
		0.0,
		config,
		newStats(),
		nil,
	}

	rand.Seed(time.Now().UnixNano())
	simulator.initEntities()

	return simulator
}

//Randomizes all entites position and velocity
func (simulator *SpreadSimulator) initEntities() {
	for i := range simulator.positions {
		simulator.positions[i].X = rand.Float64() * float64(simulator.Config.DimX)
		simulator.positions[i].Y = rand.Float64() * float64(simulator.Config.DimY)

		simulator.velocities[i].X = (rand.Float64() - 0.5) * EntitySpeedLimit
		simulator.velocities[i].Y = (rand.Float64() - 0.5) * EntitySpeedLimit

		simulator.healthData[i].survivalChance = simulator.Config.SurvivalChance

		if i < simulator.Config.InitialInfected {
			simulator.healthData[i].isInfected = true
		}
		if i < simulator.Config.InitialMobile {
			simulator.healthData[i].isMobile = true
		}
	}

	for i := 0; i < simulator.Config.CentralLocations; i++ {
		xpos := rand.Float64() * float64(simulator.Config.DimX)
		ypos := rand.Float64() * float64(simulator.Config.DimY)

		simulator.centralLocations[i] = util.Vector2f{X: xpos, Y: ypos}
	}

	simulator.Stats.newColumn()
	simulator.Stats.Susceptible[len(simulator.Stats.Susceptible)-1] = uint(simulator.Config.EntityCount - simulator.Config.InitialInfected)
	simulator.Stats.Infected[len(simulator.Stats.Infected)-1] = uint(simulator.Config.InitialInfected)
}

//Tick simulates one tick
func (simulator *SpreadSimulator) Tick() {
	if simulator.tick%ForcePeriod == 0 {
		simulator.forceDirection *= -1
	}

	//Update deltaTime
	simulator.currentTime = time.Now()
	simulator.Δt = simulator.currentTime.Sub(simulator.previousTime).Seconds()

	//---
	//Init Quadtree
	simulator.generateQuadtree()

	//---
	//Handle infections etc
	simulator.runInfections()

	//---
	//Test random entities
	simulator.runTests()

	//For delta time
	simulator.previousTime = simulator.currentTime

	//---
	//New column of values for statistic
	simulator.Stats.newColumn()
	simulator.gatherStats()

	simulator.tick++
}

//Initializes the internal quadtree.
//Called every tick
func (simulator *SpreadSimulator) generateQuadtree() {
	ScreenRect := util.NewRect(
		util.Vector2f{X: float64(simulator.Config.DimX / 2), Y: float64(simulator.Config.DimY / 2)},
		util.Vector2f{X: float64(simulator.Config.DimX / 2), Y: float64(simulator.Config.DimY / 2)})
	simulator.currentQuadtree = quadtree.NewQuadtree(ScreenRect)

	for i := range simulator.positions {
		if simulator.healthData[i].isDead { //No point in adding already dead entities
			continue
		}
		simulator.currentQuadtree.Insert(util.PositionIndexPair{Index: i, Position: simulator.positions[i]})
	}
}

//Calculates movement, infections etc
func (simulator *SpreadSimulator) runInfections() {
	var wg sync.WaitGroup

	for i := range simulator.positions {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()

			simulator.moveEntity(i)
			simulator.calculateInfection(i)

			simulator.velocities[i].ClampMag(EntitySpeedLimit)
		}(i)
	}

	wg.Wait()
}

//Calculate position based on current velocity and acceleration
func (simulator *SpreadSimulator) moveEntity(idx int) {
	if !simulator.healthData[idx].isMobile {
		return
	}

	simulator.positions[idx].Add(simulator.velocities[idx].CpyMult(simulator.Δt))
	simulator.velocities[idx].Add(simulator.accelerations[idx])
	simulator.accelerations[idx].Mult(0)

	inXBounds, inYBounds := simulator.inBounds(simulator.positions[idx])
	if !inXBounds {
		simulator.velocities[idx].X *= -1
	}
	if !inYBounds {
		simulator.velocities[idx].Y *= -1
	}

	if simulator.Config.ActiveDistancing {
		bounds := util.NewRect(
			simulator.positions[idx],
			util.Vector2f{X: simulator.Config.InfluenceRadius * 2, Y: simulator.Config.InfluenceRadius * 2},
		)
		inRange := simulator.currentQuadtree.QueryRange(bounds)

		for j := range inRange {
			if idx == j {
				continue
			}

			repulsion := util.Vector2f{X: simulator.positions[idx].X, Y: simulator.positions[idx].Y}
			repulsion.Sub(simulator.positions[inRange[j]])
			repulsion.Mult(simulator.positions[idx].InvDist(simulator.positions[inRange[j]]))
			repulsion.Mult(10 / EntitySpeedLimit)
			simulator.addForce(idx, repulsion)
		}
	}

	for i := range simulator.centralLocations {
		bounds := util.NewRect(
			simulator.centralLocations[i],
			util.Vector2f{X: CentralLocationsRange, Y: CentralLocationsRange},
		)

		inRange := simulator.currentQuadtree.QueryRange(bounds)

		for j := range inRange {
			attraction := util.Vector2f{X: simulator.centralLocations[i].X, Y: simulator.centralLocations[i].Y}
			attraction.Sub(simulator.positions[inRange[j]])
			attraction.Mult(simulator.positions[inRange[j]].InvDist(simulator.centralLocations[i]))
			attraction.Mult(10 / EntitySpeedLimit)
			attraction.Mult(float64(simulator.forceDirection))
			simulator.addForce(inRange[j], attraction)
		}
	}
}

//Test randomly selected entities
func (simulator *SpreadSimulator) runTests() {
	for i := 0; i < simulator.Config.TestsPerTick; i++ {
		if simulator.Stats.Hospitalized[len(simulator.Stats.Hospitalized)-1] >= uint(simulator.Config.HospitalCapacity) {
			//No space in hospital
			//TODO add personal quarantine
			//People are immobile, but their survival chance isn't increased
			return
		}

		rngIdx := rand.Intn(simulator.Config.EntityCount)

		if simulator.healthData[rngIdx].isInfected {
			rng := rand.Float64()
			if rng <= simulator.Config.DetectionChance &&
				!simulator.healthData[rngIdx].inHospital {
				simulator.hospitalizeEvent(rngIdx)
			}
		}
	}
}

//Check if there is a not yet infected in range, and infect him based on the config.
//Increase timecounter of infected
func (simulator *SpreadSimulator) calculateInfection(idx int) {
	if !simulator.healthData[idx].isInfected {
		return
	}

	entitiesInRange := simulator.entitiesInRange(simulator.positions[idx])

	for i := range entitiesInRange {
		rng := rand.Float64()
		if rng <= simulator.Config.InfectionChance {
			simulator.infectionEvent(entitiesInRange[i])
		}
	}

	simulator.healthData[idx].ticksSinceInfection++
	if simulator.healthData[idx].ticksSinceInfection >= simulator.Config.ExpirationTicks {
		rng := rand.Float64()
		if rng <= simulator.healthData[idx].survivalChance {
			simulator.cureEvent(idx)
		} else {
			simulator.deathEvent(idx)
		}

		simulator.dehospitalizeEvent(idx)
	}
}

//Gather stats of current tick
func (simulator *SpreadSimulator) gatherStats() {
	var s, i, c, d, h uint
	for idx := range simulator.healthData {
		if simulator.healthData[idx].isInfected {
			i++
		} else if simulator.healthData[idx].isCured {
			c++
		} else if simulator.healthData[idx].isDead {
			d++
		} else {
			s++
		}

		if simulator.healthData[idx].inHospital {
			h++
		}
	}

	simulator.Stats.setCurrent(s, i, c, d, h)
}

//Apply a force to an entity
func (simulator *SpreadSimulator) addForce(idx int, force util.Vector2f) {
	simulator.accelerations[idx].Add(force)
}

//Calculates if a position is in the window bounds.
//Used to make entites bounce off the edges.
//returns X,Y.
func (simulator *SpreadSimulator) inBounds(pos util.Vector2f) (bool, bool) {
	return !(pos.X <= 0 || pos.X >= float64(simulator.Config.DimX-1)), !(pos.Y <= 0 || pos.Y >= float64(simulator.Config.DimY-1))
}

//Gather all entities within a given range.
//Returns array of indices
func (simulator *SpreadSimulator) entitiesInRange(pos util.Vector2f) []int {
	return simulator.currentQuadtree.QueryRange(util.NewRect(pos, util.Vector2f{X: simulator.Config.InfluenceRadius, Y: simulator.Config.InfluenceRadius}))
}

//---
//Different entity events

func (simulator *SpreadSimulator) infectionEvent(idx int) {
	//Update entity
	simulator.healthData[idx].isInfected = true
}

func (simulator *SpreadSimulator) cureEvent(idx int) {
	//Update entity
	simulator.healthData[idx].isCured = true
	simulator.healthData[idx].isInfected = false
}

func (simulator *SpreadSimulator) deathEvent(idx int) {
	//Update entity
	simulator.healthData[idx].isMobile = false
	simulator.healthData[idx].isDead = true
	simulator.healthData[idx].isInfected = false
}

func (simulator *SpreadSimulator) hospitalizeEvent(idx int) {
	//Update entity
	simulator.healthData[idx].inHospital = true
	simulator.healthData[idx].isMobile = false
	simulator.healthData[idx].survivalChance = 0.9
}

func (simulator *SpreadSimulator) dehospitalizeEvent(idx int) {
	simulator.healthData[idx].inHospital = false
}
