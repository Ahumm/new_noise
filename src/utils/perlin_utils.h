#ifndef _PERLIN_UTILS_H_
#define _PERLIN_UTILS_H_

#include "noise_utils.h"

namespace noise
{

    /*
     *  Pseudo-random number generation for noise generation
     */
    float noise_2d(const int& x, const int& y, const int& seed)
    {
        int n = (x + y * 57 + seed * 419) & 0x7fffffff;
        int t = (n >> 13) ^ n;
        return (1.0 - ((t * (t * t * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);  
    }   // float noise_2d(int,int,int)
    
    /*
     *  calculate the cell value based on interpolation of four corner nodes
     */
    float interpolated_noise_2d(const float& x, const float& y, const int& seed)
    {
        int x_i = (int)x;
        int y_i = (int)y;
        
        if(x < 0) x_i -= 1;
        if(y < 0) y_i -= 1;
        
        float x_f = x - (float)x_i;
        float y_f = y - (float)y_i;
        
        float x_a = sCurve_5(x_f);
        float y_a = sCurve_5(y_f);
        
        float v1 = noise_2d(x_i    , y_i    , seed);
        float v2 = noise_2d(x_i + 1, y_i    , seed);
        float v3 = noise_2d(x_i    , y_i + 1, seed);
        float v4 = noise_2d(x_i + 1, y_i + 1, seed);
        
        float i1 = l_interpolate(v1, v2, x_a);
        float i2 = l_interpolate(v3, v4, x_a);
        
        return l_interpolate(i1, i2, y_a);
    }   // float interpolated_noise_2d(float,float,int)
    
}   // namespace noise

#endif  // _PERLIN_UTILS_H_