#ifndef _CEILING_B_MOD_H_
#define _CEILING_B_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class ceiling_b_mod : public base_mod
    {
      public:
        ceiling_b_mod() : base_mod(1), n_cbm_threshold(0.0f) {}
        ceiling_b_mod(const float& new_threshold) : 
            base_mod(1), n_cbm_threshold(new_threshold)
        {}
        
        void set_threshold(const float& new_threshold) { n_cbm_threshold = new_threshold; }
        float get_threshold() { return n_cbm_threshold; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0])
            {
                float val = n_bm_sub_mods[0]->get_val(x,y);
                if(val > n_cbm_threshold) return val;
            }
            return 1.0f;
        }   // float get_val(float,float)
        
      private:
        float n_cbm_threshold;
    };  // ceiling_b_mod
    
}   // namespace noise

#endif  // _CEILING_B_MOD_H_
