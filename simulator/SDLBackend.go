package simulator

import (
	"github.com/veandco/go-sdl2/sdl"
)

//Drawing constants
const (
	EntityRectWidth int32 = 3
)

//SDLInstance struct
type SDLInstance struct {
	window    *sdl.Window
	renderer  *sdl.Renderer
	simulator *SpreadSimulator
}

//NewSDLInstance creates a new sdl instance
func NewSDLInstance(config config, title string) (*SDLInstance, error) {
	window, err := sdl.CreateWindow(title, sdl.WINDOWPOS_UNDEFINED, sdl.WINDOWPOS_UNDEFINED, int32(config.DimX), int32(config.DimY), sdl.WINDOW_SHOWN)
	if err != nil {
		return nil, err
	}

	renderer, err := sdl.CreateRenderer(window, -1, sdl.RENDERER_ACCELERATED)
	if err != nil {
		return nil, err
	}

	simulator := NewSimulator(config)
	simulator.healthData[0].isInfected = true

	return &SDLInstance{
		window,
		renderer,
		simulator,
	}, nil
}

func (sdlInst *SDLInstance) drawSimulator() {
	for i := 0; i < sdlInst.simulator.Config.EntityCount; i++ {
		r, g, b, a := sdlInst.statusToColor(i)
		sdlInst.renderer.SetDrawColor(r, g, b, a)
		rct := sdl.Rect{
			X: int32(sdlInst.simulator.positions[i].X), Y: int32(sdlInst.simulator.positions[i].Y),
			W: EntityRectWidth, H: EntityRectWidth,
		}
		sdlInst.renderer.FillRect(&rct)
	}
}

func (sdlInst *SDLInstance) statusToColor(idx int) (uint8, uint8, uint8, uint8) {
	if sdlInst.simulator.healthData[idx].isInfected {
		return 255, 0, 0, 255
	} else if sdlInst.simulator.healthData[idx].isDead {
		return 0, 0, 0, 255
	} else if sdlInst.simulator.healthData[idx].isCured {
		return 0, 255, 0, 255
	} else {
		return 255, 255, 255, 255
	}
}

//Run starts the sdl window/event loop
func (sdlInst *SDLInstance) Run() {
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

		sdlInst.renderer.Present()

		//Update entities
		sdlInst.simulator.Tick()
	}
}
