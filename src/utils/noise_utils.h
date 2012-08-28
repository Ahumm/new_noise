#ifndef _NOISE_UTILS_H_
#define _NOISE_UTILS_H_

#include <math.h>

namespace noise
{
    /*
     *  clamp a value between two bounds, inclusive on both ends
     */
    inline float clamp(const float& val, const float& lower, const float& upper)
    {
        return (val < lower) ? lower : ((val > upper) ? upper : val);
    }   // float clamp(float,float,float)
    
    /*
     *  linear interpolation between two values
      */
    inline float l_interpolate(const float& v1, const float& v2, const float& alpha)
    {
        return (v1 * (1 - alpha)) + (v2 * alpha);
    }   // float l_interpolate(float,float,float)
    
    /*
     *  cosine interpolation between two values
     */
    inline float c_interpolate(const float& v1, const float& v2, const float& alpha)
    {
        float ft = alpha * 3.1415927f;
        float f = (1 - cos(ft)) * 0.5f;
        
        return (v1 * (1 - f)) + (v2 * f);
    }   // float c_interpolate(float,float,float)
    
    inline float sCurve_5(const float& f)
    {
        return f * f * f * (f * (f * 6 - 15) + 10);
    }
    
}   // namespace noise

#endif // _NOISE_UTILS_H_