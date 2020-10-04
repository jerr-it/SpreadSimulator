/**
 * Performs Fast inverse square root
 * https://en.wikipedia.org/wiki/Fast_inverse_square_root
 * @param number x
 * @returns 1/sqrt(x)
 */
static float InverseSquare(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5;

    x2 = number * 0.5;
    y = number;

    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
}