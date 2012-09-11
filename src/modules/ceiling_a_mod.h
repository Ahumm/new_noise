#ifndef _CEILING_A_MOD_H_
#define _CEILING_A_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class ceiling_a_mod : public base_mod
    {
      public:
        ceiling_a_mod() : base_mod(1), n_cam_threshold(0.0f) {}
        ceiling_a_mod(const float& new_threshold) : 
            base_mod(1), n_cam_threshold(new_threshold)
        {}
        
        void set_threshold(const float& new_threshold) { n_cam_threshold = new_threshold; }
        float get_threshold() { return n_cam_threshold; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0])
            {
                float val = n_bm_sub_mods[0]->get_val(x,y);
                if(val < n_cam_threshold) return val;
            }
            return 1.0f;
        }   // float get_val(float,float)
        
      private:
        float n_cam_threshold;
    };  // ceiling_a_mod
    
}   // namespace noise

#endif  // _CEILING_A_MOD_H_
