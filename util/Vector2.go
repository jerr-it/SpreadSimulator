package util

//Vector2i implements iVector for integers
type Vector2i struct {
	X int
	Y int
}

//Add implements iVector,Add for integers
func (a *Vector2i) Add(b Vector2i) {
	a.X += b.X
	a.Y += b.Y
}

//Sub implements iVector,Sud for integers
func (a *Vector2i) Sub(b Vector2i) {
	a.X -= b.X
	a.Y -= b.Y
}

//Mult scales a vector by scale
func (a *Vector2i) Mult(scale int) {
	a.X *= scale
	a.Y *= scale
}

//Vector2f implements iVector for floats
type Vector2f struct {
	X float64
	Y float64
}

//Add implements iVector,Add for floats
func (a *Vector2f) Add(b Vector2f) {
	a.X += b.X
	a.Y += b.Y
}

//Sub implements iVector,Sud for floats
func (a *Vector2f) Sub(b Vector2f) {
	a.X -= b.X
	a.Y -= b.Y
}

//Mult scales a vector by scale
func (a *Vector2f) Mult(scale float64) {
	a.X *= scale
	a.Y *= scale
}

//CpyMult scales a vector by scale.
//Same as mult, but creates a copy
func (a *Vector2f) CpyMult(scale float64) Vector2f {
	return Vector2f{
		X: a.X * scale,
		Y: a.Y * scale,
	}
}
