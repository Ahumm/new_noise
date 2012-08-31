#ifndef _MIN_MOD_H_
#define _MIN_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class min_mod : public base_mod
    {
      public:
        min_mod() : base_mod(2) {}
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0] && n_bm_sub_mods[1])
            {
                float val1 = n_bm_sub_mods[0]->get_val(x,y);
                float val2 = n_bm_sub_mods[1]->get_val(x,y)
                return ((val1 < val2) ? val1 : val2);
            }
            if(n_bm_sub_mods[0]) return (n_bm_sub_mods[0]->get_val(x,y));
            if(n_bm_sub_mods[1]) return (n_bm_sub_mods[1]->get_val(x,y));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
    };  // min_mod
    
}   // namespace noise

#endif  // _MIN_MOD_H_
