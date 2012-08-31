#ifndef _AVG_MOD_H_
#define _AVG_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class avg_mod : public base_mod
    {
      public:
        avg_mod() : base_mod(2) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0] && n_bm_sub_mods[1]) return ((n_bm_sub_mods[0]->get_val(x,y) + n_bm_sub_mods[0]->get_val(x,y)) / 2.0f);
            if(n_bm_sub_mods[0]) return (n_bm_sub_mods[0]->get_val(x,y));
            if(n_bm_sub_mods[1]) return (n_bm_sub_mods[1]->get_val(x,y));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // avg_mod
    
}   // namespace noise

#endif  // _AVG_MOD_H_
