package util

//Rect struct
type Rect struct {
	Center  Vector2f
	HalfDim Vector2f
}

//NewRect creates a new rect
func NewRect(Center Vector2f, hDim Vector2f) Rect {
	return Rect{
		Center,
		hDim,
	}
}

//ContainsPoint checks if a given point lies inside this rectangle
func (rect *Rect) ContainsPoint(p Vector2f) bool {
	return !(p.X < rect.Center.X-rect.HalfDim.X ||
		p.X > rect.Center.X+rect.HalfDim.X ||
		p.Y < rect.Center.Y-rect.HalfDim.Y ||
		p.Y > rect.Center.Y+rect.HalfDim.Y)
}

//IntersectsRect checks if another rect overlaps with this
func (rect *Rect) IntersectsRect(other Rect) bool {
	return !(other.Center.X-other.HalfDim.X > rect.Center.X+rect.HalfDim.X ||
		other.Center.X+other.HalfDim.X < rect.Center.X-rect.HalfDim.X ||
		other.Center.Y-other.HalfDim.Y > rect.Center.Y+rect.HalfDim.Y ||
		other.Center.Y+other.HalfDim.Y < rect.Center.Y-rect.HalfDim.Y)
}
