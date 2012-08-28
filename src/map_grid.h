#ifndef _MAP_GRID_H_
#define _MAP_GRID_H_

#include "modules/base_mod.h"
#include <cstring>


namespace noise
{    
    class map_grid
    {
      public:
        map_grid();
        map_grid(const size_t& new_w, const size_t& new_h);
        ~map_grid();
        
        void set_width(const size_t& new_w);
        void set_height(const size_t& new_h);
        
        size_t get_width();
        size_t get_height();
        
        float* get_data();
        
        void set_module(base_mod* new_module);
        
        int generate(const int& start_x, const int& start_y);
        
        int output_to_file(const char* filename);
      private:
        /* n_mg_width/height represent the currently set width and height to be used in the next generate() call */
        /* n_mg_last_width/height represent the values used in the last generate() call (for printing and access if n_mg_width/height have changed since the last generate() call) */
        /* n_mg_data points to the data generated int he last call to generate(), ALL DATA IS IN THE RANGE (-1.0f, 1.0f)*/
        /* n_mg_module points to the module to be used in the next generate() call */
        size_t n_mg_width, n_mg_height;
        size_t n_mg_last_width, n_mg_last_height;
        float* n_mg_data;
        base_mod* n_mg_module;
    };  // map_grid
}   // namspace noise

#endif  // _MAP_GRID_H_