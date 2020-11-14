package main

import (
	"SpreadSimulator/backends"
	"SpreadSimulator/config"
	"flag"
)

const (
	layoutISO = "2006-01-02"
)

func main() {
	var configFile string
	flag.StringVar(&configFile, "cfg", "standard", "Select config file")

	var verbose bool
	flag.BoolVar(&verbose, "v", false, "Set verbose logging")

	var export bool
	flag.BoolVar(&export, "export", false, "Want a csv file containing stats?")

	var nogui bool
	flag.BoolVar(&nogui, "nogui", false, "Graphics?")

	flag.Parse()

	config, err := config.FromJSON(configFile)
	if err != nil {
		panic(err)
	}

	var instance backends.IBackend

	if nogui {
		instance = backends.NewNoGUI(config, verbose)
	} else {
		instance, err = backends.NewSDL(config, "Simulation", verbose)
		if err != nil {
			panic(err)
		}
	}

	instance.Run()

	if export {
		instance.SaveStats(configFile)
	}
}
