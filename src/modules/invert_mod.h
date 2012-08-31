#ifndef _INVERT_MOD_H_
#define _INVERT_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class invert_mod : public base_mod
    {
      public:
        invert_mod() : base_mod(1) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0]) return (-1 * (n_bm_sub_mods[0]->get_val(x,y)));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // invert_mod
    
}   // namespace noise

#endif  // _INVERT_MOD_H_
