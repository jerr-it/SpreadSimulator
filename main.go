package main

import "SpreadSimulator/simulator"

func main() {
	config := simulator.NewConfig(
		1000,  //Entity Count
		5,     //Initial Infected
		1000,  //Initial Mobile
		10,    //Hospital Capacity
		10,    //Tests per tick
		24000, //Ticks until decision of life and death
		0.5,   //Chance of infection
		0.5,   //Chance of survival
		0.5,   //Chance of detection
		5.0,   //Radius in which others can be infected
		false, //Active distancing
		0,     //Number of central locations
		800,   //Width of area (and window)
		600)   //Height of area (and window)

	instance, err := simulator.NewSDLInstance(config, "Simulation")
	if err != nil {
		panic(err)
	}

	instance.Run()
}
