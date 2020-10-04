package main

import (
	"SpreadSimulator/simulator"
	"flag"
)

func main() {
	var configFile string
	flag.StringVar(&configFile, "cfg", "standard", "Select config file")

	flag.Parse()

	config := simulator.FromJSON(configFile)

	instance, err := simulator.NewSDLInstance(config, "Simulation")
	if err != nil {
		panic(err)
	}

	instance.Run()
}
