package backends

import (
	"SpreadSimulator/config"
	"SpreadSimulator/simulator"
	"fmt"
	"time"
)

type NoGUI struct {
	simulator *simulator.SpreadSimulator
	verbose   bool
}

func NewNoGUI(config config.Configuration, verbose bool) *NoGUI {
	return &NoGUI{
		simulator.New(config),
		verbose,
	}
}

func (noguiInst *NoGUI) Run() {
	for tick := 0; tick < noguiInst.simulator.Config.Ticks; tick++ {
		if noguiInst.verbose {
			noguiInst.simulator.Stats.Print()
		}

		noguiInst.simulator.Tick()
	}
}

func (noguiInst *NoGUI) SaveStats(name string) {
	now := time.Now()
	noguiInst.simulator.Stats.SaveCSV(name + fmt.Sprintf("_%d_%d_%d_%d:%d:%d_", now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second()))
}
