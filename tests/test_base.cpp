#include "../src/map_grid.h"
#include "../src/modules/base_mod.h"
#include <iostream>

using namespace noise;
using namespace std;

int main()
{
    cout << "test_base begin" << endl;
    map_grid mg(128,128);
    base_mod* bm = new base_mod;
    
    mg.set_module(bm);
    
    mg.generate(0,0);
    
    cout << "output_to_file : " << mg.output_to_file("./t_base.bmp") << endl;
}