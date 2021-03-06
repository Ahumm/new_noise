#ifndef _ABS_MOD_H_
#define _ABS_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class abs_mod : public base_mod
    {
      public:
        abs_mod() : base_mod(1) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0]) return fabs(n_bm_sub_mods[0]->get_val(x,y));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // abs_mod
    
}   // namespace noise

#endif  // _ABS_MOD_H_
