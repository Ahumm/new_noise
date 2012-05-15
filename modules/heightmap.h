#ifndef _HEIGHTMAP_H_
#define _HEIGHTMAP_H_

#include <iostream>

#include "noise_includes.h"

namespace noise
{
    typedef enum {
        N_BASE_MAP
    } n_map_type;

    class heightmap
    {
      public:
        heightmap(const n_map_type& map_type)
        {
            switch(map_type)
            {
                case N_BASE_MAP:
                default:
                    h_source_mod = new base_mod(0);
                    break;
            }
        }
        
        ~heightmap()
        {
            delete h_source_mod;
        }
        
        void set_height(const n_uint& new_height) { h_height = new_height; }
        void set_width(const n_uint& new_width) { h_width = new_width; }
        
        n_uint get_height() { return h_height; }
        n_uint get_width() { return h_width; }
        
        void to_bmp(const string& filename)
        {
            
        }
        
      private:
        n_uint h_width;
        n_uint h_height;
        
        base_mod* h_source_mod;
    }
}

#endif