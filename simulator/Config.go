package simulator

//config struct
//TODO json formatting save
type config struct {
	EntityCount     int
	InitialInfected int
	InitialMobile   int

	HospitalCapacity int
	TestsPerTick     int
	ExpirationTicks  int

	InfectionChance float64
	SurvivalChance  float64
	DetectionChance float64

	InfluenceRadius  float64
	ActiveDistancing bool

	CentralLocations int

	DimX int
	DimY int
}

//NewConfig creates a new configuration for the simulator itself
func NewConfig(EntityCount int, InitialInfected int, mobileCount int,
	hospitalCap int, testsPerTick int, expirationTicks int,
	infectionChance float64, survivalChance float64, detectionChance float64,
	influenceRadius float64, activeDistancing bool,
	centralLocations int, dimX int, dimY int) config {
	return config{
		EntityCount, InitialInfected, mobileCount,
		hospitalCap, testsPerTick, expirationTicks,
		infectionChance, survivalChance, detectionChance,
		influenceRadius, activeDistancing,
		centralLocations, dimX, dimY,
	}
}
