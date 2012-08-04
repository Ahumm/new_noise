#ifndef _NOISE_UTILS_H_
#define _NOISE_UTILS_H_

namespace noise
{
    float clamp(const float& val, const float& lower, const float& upper)
    {
        return (val < lower) ? lower : ((val > upper) ? upper : val);
    }
}
#endif