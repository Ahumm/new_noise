#ifndef _SCALE_MOD_H_
#define _SCALE_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class scale_mod : public base_mod
    {
      public:
        scale_mod() : base_mod(1), n_scm_factor(1.0f) {}
        scale_mod(const float& new_factor) : 
            base_mod(1), n_shm_factor(new_factor)
        {}
        
        void set_factor(const float& new_factor) { m_scm_factor = new_factor; }
        float get_factor() { return m_scm_factor; }
        
        float get_val(const float& x, const float& y)
        {
            if(n_bm_sub_mods[0]) return (n_scm_factor * (n_bm_sub_mods[0]->get_val(x,y)));
            return 0.0f;
        }   // float get_val(float,float)
        
      private:
        float n_scm_factor;
    };  // scale_mod
    
}   // namespace noise

#endif  // _SCALE_MOD_H_
