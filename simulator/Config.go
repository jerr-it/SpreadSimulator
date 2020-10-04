package simulator

import (
	"encoding/json"
	"io/ioutil"
)

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

//FromJSON creates a config from a given config file
func FromJSON(fileName string) config {
	file, err := ioutil.ReadFile("./configs/" + fileName + ".json")
	if err != nil {
		panic(err)
	}

	var con config
	err = json.Unmarshal(file, &con)
	if err != nil {
		panic(err)
	}

	return con
}

//ToJSON saves this config as a file
func (con *config) ToJSON(fileName string) {
	data, err := json.Marshal(con)
	if err != nil {
		panic(err)
	}

	err = ioutil.WriteFile("./configs/"+fileName+".json", data, 0644)
	if err != nil {
		panic(err)
	}
}
