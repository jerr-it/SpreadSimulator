package util

import "math"

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

//GetMag returns the magnitude
func (a *Vector2f) GetMag() float64 {
	return math.Sqrt(a.X*a.X + a.Y*a.Y)
}

//ClampMag limits the magnitude
func (a *Vector2f) ClampMag(max float64) {
	magSq := a.X*a.X + a.Y*a.Y
	if magSq < max*max {
		return
	}

	invSqrt := float64(InverseSquareRoot(float32(magSq)))

	a.X *= invSqrt
	a.Y *= invSqrt

	a.X *= max
	a.Y *= max
}

//InvDist returns the 1/sqrt(distSq) to the vector b
func (a *Vector2f) InvDist(b Vector2f) float64 {
	abx := a.X - b.X
	aby := a.Y - b.Y
	distSq := abx*abx + aby*aby
	return float64(InverseSquareRoot(float32(distSq)))
}
