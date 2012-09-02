#ifndef _SUBT_MOD_H_
#define _SUBT_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class subt_mod : public base_mod
    {
      public:
        subt_mod() : base_mod(2) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0] && n_bm_sub_mods[1]) return (n_bm_sub_mods[0]->get_val(x,y) - n_bm_sub_mods[1]->get_val(x,y));
            if(n_bm_sub_mods[0]) return (n_bm_sub_mods[0]->get_val(x,y));
            if(n_bm_sub_mods[1]) return (n_bm_sub_mods[1]->get_val(x,y));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // subt_mod
    
}   // namespace noise

#endif  // _SUBT_MOD_H_
