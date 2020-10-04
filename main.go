package main

import (
	"SpreadSimulator/simulator"
	"flag"
)

func main() {
	var configFile string
	flag.StringVar(&configFile, "cfg", "standard", "Select config file")
	var verbose bool
	flag.BoolVar(&verbose, "v", false, "Set verbose logging")

	flag.Parse()

	config := simulator.FromJSON(configFile)

	instance, err := simulator.NewSDLInstance(config, "Simulation", verbose)
	if err != nil {
		panic(err)
	}

	instance.Run()
}
