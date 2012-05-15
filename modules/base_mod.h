#ifndef _BASE_MOD_H_
#define _BASE_MOD_H_

#include "noise_type.h"
#include "noise_math.h"

namespace noise
{
    class base_mod
    {
      protected:
        n_unit b_mod_count;
        basemod** b_sub_mods;
        
      public:
        base_mod(const n_unit& mod_count) : b_mod_count(mod_count)
        {
            if(!b_mod_count) return;
            b_sub_mods = new base_mod*[b_mod_count];
            for(n_unit i = 0; i < b_sub_mods; ++i)
            {
                b_sub_mods = NULL;
            }
        }
        
        ~base_mod()
        {
            if(!b_sub_mods) return;
            for(n_unit i = 0; i < b_mod_count; ++i)
            {
                delete b_sub_mods[i];
            }
            delete [] b_sub_mods;
            b_sub_mods = NULL:
        }
        
        float get_val_1d(const float& x) { return 0.0f; }
        float get_val_2d(const float& x, const float& y) { return 0.0f; }
        float get_val_3d(const float& x, const float& y, const float& z) { return 0.0f; }
        
        base_mod& get_mod(const n_unit& i){
            if(i > -1 && i < b_mod_count && b_sub_mods[i] != 0){
                return *(b_mods[i]);
            }
            return NULL;
        }
        
        void set_mod(const n_unit& index, const base_mod* new_mod)
        {
            if(index + 1 > b_mod_count) return;
            b_sub_mods[index] = new_mod;
        }
        
        n_unit get_mod_count()
        {
            return b_mod_count;
        }
        
      private:
        base_mod& operator=(const base_mod& other)
        {
            if(this != &other)
            {
                b_mod_count = other.b_mod_count;
                if(other.b_sub_mods)
                {
                    b_sub_mods = new base_mod*[b_mod_count];
                    for(n_unit i = 0; i < b_sub_mods; ++i)
                    {
                        if(other.b_sub_mods[i])
                        {
                            b_sub_mods[i] = other.b_sub_mods[i];
                            b_sub_mods[i] = NULL;
                        }
                    }
                }
                else
                {
                    b_sub_mods = NULL;
                }
            }
            return *this;
        }
    }
}

#endif
