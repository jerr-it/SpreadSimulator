package backends

import (
	"SpreadSimulator/config"
	"SpreadSimulator/simulator"

	"github.com/veandco/go-sdl2/sdl"
)

//Drawing constants
const (
	EntityRectWidth int32 = 3
)

//SDLInstance struct
type SDL struct {
	window    *sdl.Window
	renderer  *sdl.Renderer
	simulator *simulator.SpreadSimulator
	verbose   bool
}

//NewSDL creates a new sdl instance
func NewSDL(config config.Configuration, title string, verbose bool) (*SDL, error) {
	window, err := sdl.CreateWindow(title, sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED, int32(config.DimX), int32(config.DimY), sdl.WINDOW_SHOWN)
	if err != nil {
		return nil, err
	}

	renderer, err := sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		return nil, err
	}

	simulator := simulator.New(config)

	return &SDL{
		window,
		renderer,
		simulator,
		verbose,
	}, nil
}

func (sdlInst *SDL) drawSimulator() {
	for i := 0; i < sdlInst.simulator.Config.EntityCount; i++ {
		r, g, b, a := sdlInst.statusToColor(i)
		sdlInst.renderer.SetDrawColor(r, g, b, a)

		pos := sdlInst.simulator.Positions(i)
		rct := sdl.Rect{
			X: int32(pos.X), Y: int32(pos.Y),
			W: EntityRectWidth, H: EntityRectWidth,
		}
		sdlInst.renderer.FillRect(&rct)
	}

	for i := 0; i < sdlInst.simulator.Config.CentralLocations; i++ {
		sdlInst.renderer.SetDrawColor(30, 144, 255, 255)
		location := sdlInst.simulator.CentralLocations(i)
		rct := sdl.Rect{
			X: int32(location.X - simulator.CentralLocationsRange), Y: int32(location.Y - simulator.CentralLocationsRange),
			W: simulator.CentralLocationsRange * 2, H: simulator.CentralLocationsRange * 2,
		}
		sdlInst.renderer.DrawRect(&rct)
	}
}

func (sdlInst *SDL) statusToColor(idx int) (uint8, uint8, uint8, uint8) {
	hdata := sdlInst.simulator.HealthData(idx)
	if hdata.Infected() {
		return 255, 0, 0, 255
	} else if hdata.Dead() {
		return 0, 0, 0, 255
	} else if hdata.Cured() {
		return 0, 255, 0, 255
	} else {
		return 255, 255, 255, 255
	}
}

//Run starts the sdl window/event loop
func (sdlInst *SDL) Run() {
	running := true

	for running {
		for event := sdl.PollEvent(); event != nil; event = sdl.PollEvent() {
			switch event.(type) {
			case *sdl.QuitEvent:
				running = false
				break
			}
		}
		sdlInst.renderer.SetDrawColor(50, 50, 50, 255)
		sdlInst.renderer.Clear()

		sdlInst.drawSimulator()

		if sdlInst.verbose {
			sdlInst.simulator.Stats.Print()
		}
		sdlInst.renderer.Present()

		//Update entities
		sdlInst.simulator.Tick()
	}
}

//SaveStats saves the internal simulators stats
func (sdlInst *SDL) SaveStats(name string) {
	sdlInst.simulator.Stats.SaveCSV(name)
}
