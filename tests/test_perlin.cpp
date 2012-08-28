#include "../src/map_grid.h"
#include "../src/modules/perlin_mod.h"
#include <iostream>

using namespace noise;
using namespace std;

int main()
{
    cout << "test_perlin begin" << endl;
    map_grid mg(128,128);
    perlin_mod* pm = new perlin_mod(0.5f, 6, 0);
    
    mg.set_module(pm);
    
    mg.generate(0,0);
    
    cout << "output_to_file : " << mg.output_to_file("./t_perlin.bmp") << endl;
}