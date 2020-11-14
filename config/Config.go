package config

import (
	"encoding/json"
	"io/ioutil"
)

//config struct
//TODO json formatting save
type Configuration struct {
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

//New creates a new configuration for the simulator itself
func New(EntityCount int, InitialInfected int, mobileCount int,
	hospitalCap int, testsPerTick int, expirationTicks int,
	infectionChance float64, survivalChance float64, detectionChance float64,
	influenceRadius float64, activeDistancing bool,
	centralLocations int, dimX int, dimY int) Configuration {
	return Configuration{
		EntityCount, InitialInfected, mobileCount,
		hospitalCap, testsPerTick, expirationTicks,
		infectionChance, survivalChance, detectionChance,
		influenceRadius, activeDistancing,
		centralLocations, dimX, dimY,
	}
}

//FromJSON creates a config from a given config file
func FromJSON(fileName string) (Configuration, error) {
	file, err := ioutil.ReadFile("./settings/" + fileName + ".json")
	if err != nil {
		return Configuration{}, nil
	}

	var con Configuration
	err = json.Unmarshal(file, &con)
	if err != nil {
		return Configuration{}, nil
	}

	return con, nil
}

//ToJSON saves this config as a file
func (con *Configuration) ToJSON(fileName string) error {
	data, err := json.Marshal(con)
	if err != nil {
		return err
	}

	return ioutil.WriteFile("./settings/"+fileName+".json", data, 0644)
}
