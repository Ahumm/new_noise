#ifndef _SHIFT_MOD_H_
#define _SHIFT_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class shift_mod : public base_mod
    {
      public:
        shift_mod() : base_mod(1), n_shm_factor(0.0f) {}
        shift_mod(const float& new_factor) : 
            base_mod(1), n_shm_factor(new_factor)
        {}
        
        void set_factor(const float& new_factor) { n_shm_factor = new_factor; }
        float get_factor() { return n_shm_factor; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0]) return (n_shm_factor + (n_bm_sub_mods[0]->get_val(x,y)));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
        float n_shm_factor;
    };  // shift_mod
    
}   // namespace noise

#endif  // _SHIFT_MOD_H_
