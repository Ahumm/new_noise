#ifndef _MAP_GRID_H_
#define _MAP_GRID_H_

#include "modules/base_mod.h"
#include <cstring>

#include <iostream>

#include "utils/noise_utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"


namespace noise
{    
    class map_grid
    {
      public:
        // DEFAULT CONSTRUCTOR
        map_grid() :
            n_mg_width(0), n_mg_height(0),
            n_mg_x_zoom(6.0f), n_mg_y_zoom(6.0f),
            n_mg_last_width(0), n_mg_last_height(0),
            n_mg_data(0), n_mg_module(0),
            n_mg_auto_scale(true)
        {}
        // CONSTRUCTOR TAKING WIDTH AND HEIGHT 
        map_grid(const size_t& new_w, const size_t& new_h) : 
            n_mg_width(new_w), n_mg_height(new_h),
            n_mg_x_zoom(6.0f), n_mg_y_zoom(6.0f),
            n_mg_data(0), n_mg_module(0),
            n_mg_auto_scale(true)
        {}
        // DESTRUCTOR
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
        
        // ACCESSOR FUNCTIONS
        void set_width(const size_t& new_w){ n_mg_width = new_w; }
        void set_height(const size_t& new_h){ n_mg_height = new_h; }
        void set_x_zoom(const size_t& new_x_zoom){ n_mg_x_zoom = new_x_zoom; }
        void set_y_zoom(const size_t& new_y_zoom){ n_mg_y_zoom = new_y_zoom; }
        void set_auto_scale(const bool& new_as){ n_mg_auto_scale = new_as; }
        void toggle_auto_scale(){ n_mg_auto_scale = !n_mg_auto_scale;}
        
        size_t get_width(){ return n_mg_last_width; }
        size_t get_height(){ return n_mg_last_height; }
        bool get_auto_scale(){ return n_mg_auto_scale; }
        
        float* get_data(){ return n_mg_data; }
        
        float get_val(const float& x, const float& y)
        {
            if(!n_mg_data) return 0.0f;
            if(x < 0 || y < 0 || x > n_mg_last_width - 1 || y > n_mg_last_height - 1) return 0.0f;

            int i_x = (int)x;
            int i_y = (int)y;
            float f_x = x - (float)i_x;
            float f_y = y - (float)i_y;

            float i = c_interpolate(n_mg_data[(i_x * n_mg_width) + i_y], n_mg_data[((i_x + 1) * n_mg_width) + i_y], f_x);
            float j = c_interpolate(n_mg_data[(i_x * n_mg_width) + i_y + 1], n_mg_data[((i_x + 1) * n_mg_width) + i_y + 1], f_x);

            float s = c_interpolate(i, j, f_y);

            return s;
        }

        // SET A NEW MODULE TO PULL DATA FROM
        void set_module(base_mod* new_module)
        {
            if(n_mg_module)
            {
                delete n_mg_module;
                n_mg_module = 0;
            }
            n_mg_module = new_module;
        }   // void set_module(base_mod*)
        
        // GENERATE THE DATA FOR THE ARRAY
        int generate(const int& start_x, const int& start_y)
        {
            // CHECK THAT WE HAVE A MODULE
            if(!n_mg_module) return -1;
            // CHECK IF THE SPECIFIED ARRAY SIZE HAS CHANGED BETWEEN CALLS TO GENERATE
            if(n_mg_data && (n_mg_width != n_mg_last_width || n_mg_height != n_mg_last_height))
            {
                if(n_mg_width == 0 || n_mg_height == 0) return -1;
                delete [] n_mg_data;
                n_mg_data = new float[n_mg_width * n_mg_height];
                n_mg_last_width = n_mg_width;
                n_mg_last_height = n_mg_height;
            }
            // CHECK IF THE ARRAY HAS BEEN ALLOCATED
            if(!n_mg_data)
            {
                if(n_mg_width == 0 || n_mg_height == 0) return -1;
                n_mg_data = new float[n_mg_width * n_mg_height];
                n_mg_last_width = n_mg_width;
                n_mg_last_height = n_mg_height;
            }
            
            // SET UP ZOOM LEVEL AND VARIABLES TO TRACK CURRENT POSITION
            float x_change = n_mg_x_zoom / n_mg_width;
            float y_change = n_mg_y_zoom / n_mg_height;
            float x_current = (float)start_x;
            float y_current = (float)start_y;
            
            // KEEP TRACK OF THE LARGEST VALUSE FOUND (FOR AUTO_SCALING)
            float max_found_value = 0.0f;
            
            // PULL ALL THE DATA
            for(size_t row = 0; row < n_mg_height; ++row)
            {
                x_current = (float)start_x;
                for(size_t col = 0; col < n_mg_width; ++col)
                {
                    n_mg_data[(row * n_mg_width) + col] = n_mg_module->get_val(x_current, y_current);
                    float t_val = (n_mg_data[(row * n_mg_width) + col] < 0.0f) ? n_mg_data[(row * n_mg_width) + col] * -1.0f : n_mg_data[(row * n_mg_width) + col];
                    if(t_val > max_found_value) max_found_value = t_val;
                    x_current += x_change;
                }
                y_current += y_change;
            }
            
            // Shift everything to the correct range (I hope outliers don't break everything by making it shift too far)
            if(max_found_value <= 1.0f) return 0;
            
            float scale_value = 1.0f / max_found_value;

            for(size_t i = 0; i < n_mg_height * n_mg_width; i++)
            {
                if(n_mg_auto_scale) n_mg_data[i] *= scale_value;
                else n_mg_data[i] = noise::clamp(n_mg_data[i], -1.0f, 1.0f);
            }
            
            return 0;
        }   // int generate(int,int)
        
        // OUTPUT THE DATA ARRAY TO A BMP FILE
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
        /* auto_scale determines if the output should auto-scale (true) or simply clamp (false) */
        size_t n_mg_width, n_mg_height;
        float n_mg_x_zoom, n_mg_y_zoom;
        size_t n_mg_last_width, n_mg_last_height;
        float* n_mg_data;
        base_mod* n_mg_module;
        bool n_mg_auto_scale;
        bool n_mg_changes_since_last_gen;
    };  // map_grid
}   // namspace noise

#endif  // _MAP_GRID_H_
