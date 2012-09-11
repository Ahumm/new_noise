#ifndef _FLOOR_A_MOD_H_
#define _FLOOR_A_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class floor_a_mod : public base_mod
    {
      public:
        floor_a_mod() : base_mod(1), n_fam_threshold(0.0f) {}
        floor_a_mod(const float& new_threshold) : 
            base_mod(1), n_fam_threshold(new_threshold)
        {}
        
        void set_threshold(const float& new_threshold) { n_fam_threshold = new_threshold; }
        float get_threshold() { return n_fam_threshold; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0])
            {
                float val = n_bm_sub_mods[0]->get_val(x,y);
                if(val < n_fam_threshold) return val;
            }
            return -1.0f;
        }   // float get_val(float,float)
        
      private:
        float n_fam_threshold;
    };  // floor_a_mod
    
}   // namespace noise

#endif  // _FLOOR_A_MOD_H_
