#ifndef _NOISE_MATH_H_
#define _NOISE_MATH_H_

#include <math.h>

#include "noise_constants.h"

float clamp(const float& f, const float& min, const float& max)
{
    return (f < min) ? (min) : ((f > max) ? (max) : (f));
}

float linear_interpolation(const float& a, const float& b, const float& x)
{
    return (a + (x * (b - a));
}

float cosine_interpolation(const float& a, const float& b, const float& x)
{
    float ft = x * PI;
    float f = (1.0f - cos(ft)) * 0.5f;
    return (a + (f * (b - a));
}

#endif

