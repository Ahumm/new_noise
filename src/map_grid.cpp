#include "map_grid.h"
#include "utils/noise_utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "utils/stb_image_write.h"

using namespace noise;

map_grid::map_grid() :
    n_mg_width(0), n_mg_height(0),
    n_mg_last_width(0), n_mg_last_height(0),
    n_mg_data(0), n_mg_module(0)
{}

map_grid::map_grid(const size_t& new_w, const size_t& new_h)
    : n_mg_width(new_w), n_mg_height(new_h),n_mg_data(0), n_mg_module(0)
{}

map_grid::~map_grid()
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
}

void map_grid::set_width(const size_t& new_w){ n_mg_width = new_w; }
void map_grid::set_height(const size_t& new_h){ n_mg_height = new_h; }

size_t map_grid::get_width(){ return n_mg_last_width; }
size_t map_grid::get_height(){ return n_mg_last_height; }

float* map_grid::get_data(){ return n_mg_data; }

void map_grid::set_module(base_mod* new_module)
{
    if(n_mg_module)
    {
        delete n_mg_module;
        n_mg_module = 0;
    }
    n_mg_module = new_module;
}

int map_grid::generate(const int& start_x, const int& start_y)
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
    
    for(size_t row = 0; row < n_mg_height; ++row)
    {
        for(size_t col = 0; col < n_mg_width; ++col)
        {
            n_mg_data[(row * n_mg_width) + col] = clamp(n_mg_module->get_val(col + start_x, row + start_y), -1.0f, 1.0f);
        }
    }
    return 0;
}

int map_grid::output_to_file(const char* filename)
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
}