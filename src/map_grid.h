#ifndef _MAP_GRID_H_
#define _MAP_GRID_H_

#include "modules/base_mod.h"
#include <cstring>

#include "utils/noise_utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"


namespace noise
{    
    class map_grid
    {
      public:
        map_grid() :
            n_mg_width(0), n_mg_height(0),
            n_mg_x_zoom(6.0f), n_mg_y_zoom(6.0f),
            n_mg_last_width(0), n_mg_last_height(0),
            n_mg_data(0), n_mg_module(0)
        {}
        map_grid(const size_t& new_w, const size_t& new_h) : 
            n_mg_width(new_w), n_mg_height(new_h),
            n_mg_x_zoom(6.0f), n_mg_y_zoom(6.0f),
            n_mg_data(0), n_mg_module(0)
        {}
        ~map_grid()
        {
            if(n_mg_data)
            {
                delete [] n_mg_data;
                n_mg_data = 0;
            }
            if(n_mg_module)
            {
                delete n_mg_module;
                n_mg_module = 0;
            }
        }   // ~map_grid()
        
        void set_width(const size_t& new_w){ n_mg_width = new_w; }
        void set_height(const size_t& new_h){ n_mg_height = new_h; }
        void set_x_zoom(const size_t& new_x_zoom){ n_mg_x_zoom = new_x_zoom; }
        void set_y_zoom(const size_t& new_y_zoom){ n_mg_y_zoom = new_y_zoom; }
        
        size_t get_width(){ return n_mg_last_width; }
        size_t get_height(){ return n_mg_last_height; }
        
        float* get_data(){ return n_mg_data; }
        
        void set_module(base_mod* new_module)
        {
            if(n_mg_module)
            {
                delete n_mg_module;
                n_mg_module = 0;
            }
            n_mg_module = new_module;
        }   // void set_module(base_mod*)
        
        int generate(const int& start_x, const int& start_y)
        {
            if(!n_mg_module) return -1;
            if(n_mg_data && (n_mg_width != n_mg_last_width || n_mg_height != n_mg_last_height))
            {
                if(n_mg_width == 0 || n_mg_height == 0) return -1;
                delete [] n_mg_data;
                n_mg_data = new float[n_mg_width * n_mg_height];
                n_mg_last_width = n_mg_width;
                n_mg_last_height = n_mg_height;
            }
            if(!n_mg_data)
            {
                if(n_mg_width == 0 || n_mg_height == 0) return -1;
                n_mg_data = new float[n_mg_width * n_mg_height];
                n_mg_last_width = n_mg_width;
                n_mg_last_height = n_mg_height;
            }
            
            
            float x_change = n_mg_x_zoom / n_mg_width;
            float y_change = n_mg_y_zoom / n_mg_height;
            float x_current = (float)start_x;
            float y_current = (float)start_y;
            
            for(size_t row = 0; row < n_mg_height; ++row)
            {
                x_current = (float)start_x;
                for(size_t col = 0; col < n_mg_width; ++col)
                {
                    n_mg_data[(row * n_mg_width) + col] = noise::clamp(n_mg_module->get_val(x_current, y_current), -1.0f, 1.0f);
                    x_current += x_change;
                }
                y_current += y_change;
            }
            return 0;
        }   // int generate(int,int)
        
        int output_to_file(const char* filename)
        {
            if(!n_mg_data && !n_mg_module) return -1;
            if(!n_mg_data) generate(0,0);
            
            unsigned char* tmp_data = new unsigned char[n_mg_last_width * n_mg_last_height];
            
            int tmp_int = 0;
            for(size_t i = 0; i < n_mg_last_width * n_mg_last_height; ++i)
            {
                tmp_int = (128 + 128 * n_mg_data[i]);
                tmp_data[i] = (tmp_int < 0) ? 0 : (tmp_int > 255) ? 255 : (128 + 128 * n_mg_data[i]);
            }
            
            int ret_val = stbi_write_bmp(filename, (int)n_mg_last_width, (int)n_mg_last_height, 1, (void*)tmp_data);
            
            delete [] tmp_data;
            return ret_val;
        }   // int output_to_file(char*)
      private:
        /* n_mg_width/height represent the currently set width and height to be used in the next generate() call */
        /* n_mg_last_width/height represent the values used in the last generate() call (for printing and access if n_mg_width/height have changed since the last generate() call) */
        /* n_mg_x/y_zoom represents the level of zoom applied (i.e. the size of the frame we look at) */
        /* n_mg_data points to the data generated int he last call to generate(), ALL DATA IS IN THE RANGE (-1.0f, 1.0f)*/
        /* n_mg_module points to the module to be used in the next generate() call */
        size_t n_mg_width, n_mg_height;
        float n_mg_x_zoom, n_mg_y_zoom;
        size_t n_mg_last_width, n_mg_last_height;
        float* n_mg_data;
        base_mod* n_mg_module;
    };  // map_grid
}   // namspace noise

#endif  // _MAP_GRID_H_