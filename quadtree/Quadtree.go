package quadtree

import (
	"SpreadSimulator/util"
)

//Quadtree constants
const (
	NodeCapacity = 4
)

//Quadtree struct
type Quadtree struct {
	boundary util.Rect

	entries []util.PositionIndexPair

	northWest *Quadtree
	northEast *Quadtree
	southWest *Quadtree
	southEast *Quadtree
}

//NewQuadtree creates a new Quadtree
func NewQuadtree(boundary util.Rect) *Quadtree {
	return &Quadtree{
		boundary,
		make([]util.PositionIndexPair, 0),
		nil, nil, nil, nil,
	}
}

//Insert function returns true on success
func (qtree *Quadtree) Insert(pair util.PositionIndexPair) bool {
	if !qtree.boundary.ContainsPoint(pair.Position) {
		return false
	}

	if len(qtree.entries) < NodeCapacity && qtree.northWest == nil {
		qtree.entries = append(qtree.entries, pair)
		return true
	}

	if qtree.northWest == nil {
		qtree.subdivide()
	}

	if qtree.northWest.Insert(pair) {
		return true
	}
	if qtree.northEast.Insert(pair) {
		return true
	}
	if qtree.southWest.Insert(pair) {
		return true
	}
	if qtree.southEast.Insert(pair) {
		return true
	}

	//Should not happen
	return false
}

//QueryRange returns all indexed points within the given range
func (qtree *Quadtree) QueryRange(bounds util.Rect) []int {
	inRange := make([]int, 0)

	if !qtree.boundary.IntersectsRect(bounds) {
		return inRange
	}

	for i := range qtree.entries {
		if bounds.ContainsPoint(qtree.entries[i].Position) {
			inRange = append(inRange, qtree.entries[i].Index)
		}
	}

	if qtree.northWest == nil {
		return inRange
	}

	inRange = append(inRange, qtree.northWest.QueryRange(bounds)...)
	inRange = append(inRange, qtree.northEast.QueryRange(bounds)...)
	inRange = append(inRange, qtree.southWest.QueryRange(bounds)...)
	inRange = append(inRange, qtree.southEast.QueryRange(bounds)...)

	return inRange
}

func (qtree *Quadtree) subdivide() {
	NWCenter := util.Vector2f{
		X: qtree.boundary.Center.X - qtree.boundary.HalfDim.X/2,
		Y: qtree.boundary.Center.Y - qtree.boundary.HalfDim.Y/2,
	}
	qtree.northWest = NewQuadtree(util.NewRect(NWCenter, util.Vector2f{X: qtree.boundary.HalfDim.X / 2, Y: qtree.boundary.HalfDim.Y / 2}))

	NECenter := util.Vector2f{
		X: qtree.boundary.Center.X + qtree.boundary.HalfDim.X/2,
		Y: qtree.boundary.Center.Y - qtree.boundary.HalfDim.Y/2,
	}
	qtree.northEast = NewQuadtree(util.NewRect(NECenter, util.Vector2f{X: qtree.boundary.HalfDim.X / 2, Y: qtree.boundary.HalfDim.Y / 2}))

	SWCenter := util.Vector2f{
		X: qtree.boundary.Center.X - qtree.boundary.HalfDim.X/2,
		Y: qtree.boundary.Center.Y + qtree.boundary.HalfDim.Y/2,
	}
	qtree.southWest = NewQuadtree(util.NewRect(SWCenter, util.Vector2f{X: qtree.boundary.HalfDim.X / 2, Y: qtree.boundary.HalfDim.Y / 2}))

	SECenter := util.Vector2f{
		X: qtree.boundary.Center.X + qtree.boundary.HalfDim.X/2,
		Y: qtree.boundary.Center.Y + qtree.boundary.HalfDim.Y/2,
	}
	qtree.southEast = NewQuadtree(util.NewRect(SECenter, util.Vector2f{X: qtree.boundary.HalfDim.X / 2, Y: qtree.boundary.HalfDim.Y / 2}))
}
