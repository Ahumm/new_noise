#ifndef _BASE_MOD_H_
#define _BASE_MOD_H_

namespace noise
{
    class base_mod
    {
      public:
        base_mod()
        {
            n_bm_sub_mods = 0;
            n_bm_mod_count = 0;
        }   // base_mod()
        
        /*
         *  Allocate memory for sub modules as necessary
         */
        base_mod(const int& mod_count)
        {
            n_bm_mod_count = mod_count;
            if(n_bm_mod_count <= 0)
            {
                n_bm_sub_mods = 0;
                n_bm_mod_count = 0;
            }
            else
            {
                n_bm_sub_mods = new base_mod*[n_bm_mod_count];
                for(int i = 0; i < n_bm_mod_count; ++i)
                {
                    n_bm_sub_mods[i] = 0;
                }
            }
        }   // base_mod(int)
        
        /*
         *  Make sure all sub modules are properly deleted
         */
        ~base_mod()
        {
            if(n_bm_mod_count > 0 && n_bm_sub_mods)
            {
                for(int i = 0; i < n_bm_mod_count; ++i)
                {
                    if(n_bm_sub_mods[i])
                    {
                        delete n_bm_sub_mods[i];
                        n_bm_sub_mods[i] = 0;
                    }
                    delete [] n_bm_sub_mods;
                    n_bm_sub_mods = 0;
                }
            }
        }   // ~base_mod()
        
        void set_mod(const int& pos, base_mod* new_sub_mod)
        {
            if(pos < 0 || pos > n_bm_mod_count) return;
            if(n_bm_mod_count == 0) return;
            if(!n_bm_sub_mods) return;
            if(n_bm_sub_mods[pos])
            {
                delete n_bm_sub_mods[pos];
            }
            n_bm_sub_mods[pos] = new_sub_mod;
        }   // set_mod(int,base_mod*)
        
        /*
         *  Get the value at a given cell
         */
        virtual float get_val(const float& x, const float& y) { return 0.5f; }
      protected:
        int n_bm_mod_count;
        base_mod** n_bm_sub_mods;
    };  // base_mod
    
}   // namespace noise

#endif  // _BASE_MOD_H_