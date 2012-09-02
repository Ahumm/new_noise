#ifndef _INTERP_MOD_H_
#define _INTERP_MOD_H_

#include <math.h>

#include "base_mod.h"
#include "../utils/noise_utils.h"

namespace noise
{
    class interp_mod : public base_mod
    {
      public:
        interp_mod() : base_mod(3) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0] && n_bm_sub_mods[1] && n_bm_sub_mods[2]) return c_interpolate(n_bm_sub_mods[0], n_bm_sub_mods[1], (n_bm_sub_mods[2] + 1.0f) / 2.0f);
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // interp_mod
    
}   // namespace noise

#endif  // _INTERP_MOD_H_
