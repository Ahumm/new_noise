#ifndef _PERLIN_MOD_H_
#define _PERLIN_MOD_H_
#include <iostream>
#include "base_mod.h"
#include "../utils/perlin_utils.h"

// PERSISTANCE - Higher => Pushes Towards the Extemes (Higher/Lower Terrain)
// OCTAVES     - Higher => Higher Detail
// FREQUENCY   - Lower => More Flowing Terrain
//             - Higher => More Islandy

namespace noise
{
    class perlin_mod : public base_mod
    {
      public:
        perlin_mod() : base_mod(0)
        {
            n_pm_persistence = 1.0f;
            n_pm_frequency = 1.0f;
            n_pm_octaves = 1;
            n_pm_seed = 0;
        }   // perlin_mod()
        
        perlin_mod(const float& new_persistence, const int& new_octaves, const int& new_seed) : base_mod(0)
        {
            n_pm_persistence = new_persistence;
            n_pm_frequency = 2.0f;
            n_pm_octaves = (new_octaves > 0) ? new_octaves : 1;
            n_pm_seed = new_seed;
        }   // perlin_mod(float,int,int)
        
        perlin_mod(const float& new_persistence, const float& new_frequency, const int& new_octaves, const int& new_seed) : base_mod(0)
        {
            n_pm_persistence = new_persistence;
            n_pm_frequency = new_frequency;
            n_pm_octaves = (new_octaves > 0) ? new_octaves : 1;
            n_pm_seed = new_seed;
        }   // perlin_mod(float,float,int,int)
        
        void set_persistence(const float& new_persistence)
        {
            n_pm_persistence = new_persistence;
        }   // void set_persistence(float)
        
        void set_frequency(const float& new_frequency)
        {
            n_pm_frequency = new_frequency;
        }   // void set_frequency(float)
        
        void set_octaves(const int& new_octaves)
        {
            n_pm_octaves = (new_octaves > 0) ? new_octaves : 1;
        }   // void set_octaves(int)
        
        void set_seed(const int& new_seed)
        {
            n_pm_seed = new_seed;
        }   // void set_seed(int)
        
        float get_val(const float& x, const float& y)
        {
            float total = 0.0f;
            float p = n_pm_persistence;
            float amplitude = p;//1.0f;
            float frequency = n_pm_frequency;
            float x_pass, y_pass, seed_pass;
            for(size_t i = 0; i < n_pm_octaves; ++i)
            {
                x_pass = (float)x * frequency;
                y_pass = (float)y * frequency;
                seed_pass = n_pm_seed + i;
                total += interpolated_noise_2d(x_pass, y_pass, seed_pass) * amplitude;
                frequency *= 2.0f;
                amplitude *= p;
            }
            return total;
        }   // float get_val(float,float)
        
      private:
        float n_pm_persistence;
        float n_pm_frequency;
        int n_pm_octaves;
        int n_pm_seed;
    };  // perlin_mod
    
}   // namespace noise

#endif  // _PERLIN_MOD_H_
