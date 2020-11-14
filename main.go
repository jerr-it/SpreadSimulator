package main

import (
	"SpreadSimulator/backends"
	"SpreadSimulator/config"
	"flag"
	"fmt"
	"time"
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

	flag.Parse()

	config, err := config.FromJSON(configFile)
	if err != nil {
		panic(err)
	}

	instance, err := backends.NewSDL(config, "Simulation", verbose)
	if err != nil {
		panic(err)
	}

	instance.Run()

	if export {
		now := time.Now()
		instance.SaveStats(configFile + fmt.Sprintf("_%d_%d_%d_%d:%d:%d_", now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second()))
	}
}
