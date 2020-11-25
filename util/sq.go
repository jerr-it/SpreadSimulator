package util

import "unsafe"

//Performs Fast Inverse Square Root
//https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
func InverseSquareRoot(number float32) float32 {
	var i int64
	var x2, y float32
	const threeHalfs float32 = 1.5

	x2 = number * 0.5
	y = number
	i = *((*int64)(unsafe.Pointer(&y)))

	i = 0x5f3759df - (i >> 1)
	y = *((*float32)(unsafe.Pointer(&i)))
	y = y * (threeHalfs - (x2 * y * y))

	return y
}
