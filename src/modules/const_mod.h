#ifndef _CONST_MOD_H_
#define _CONST_MOD_H_

#include <math.h>

#include "base_mod.h"

namespace noise
{
    class const_mod : public base_mod
    {
      public:
        const_mod() : base_mod(0), n_com_value(0.0f) {}
        const_mod(const float& new_value) : 
            base_mod(0), n_com_value(new_value)
        {}
        
        void set_value(const float& new_value) { n_com_value = new_value; }
        float get_value() { return n_com_value; }
        
        float get_val(const float& x, const float& y)
        {
            return n_com_value;
        }   // float get_val(float,float)
        
      private:
        float n_com_value;
    };  // const_mod
    
}   // namespace noise

#endif  // _CONST_MOD_H_
