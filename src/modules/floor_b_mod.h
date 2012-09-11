#ifndef _FLOOR_B_MOD_H_
#define _FLOOR_B_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class floor_b_mod : public base_mod
    {
      public:
        floor_b_mod() : base_mod(1), n_fbm_threshold(0.0f) {}
        floor_b_mod(const float& new_threshold) : 
            base_mod(1), n_fbm_threshold(new_threshold)
        {}
        
        void set_threshold(const float& new_threshold) { n_fbm_threshold = new_threshold; }
        float get_threshold() { return n_fbm_threshold; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0])
            {
                float val = n_bm_sub_mods[0]->get_val(x,y);
                if(val > n_fbm_threshold) return val;
            }
            return -1.0f;
        }   // float get_val(float,float)
        
      private:
        float n_fbm_threshold;
    };  // floor_b_mod
    
}   // namespace noise

#endif  // _FLOOR_B_MOD_H_
