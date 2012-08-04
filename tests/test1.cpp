#include "../src/map_grid.h"
#include "../src/modules/base_mod.h"
#include <iostream>

using namespace noise;
using namespace std;

int main()
{
    cout << "test1 begin" << endl;
    map_grid mg(128,128);
    base_mod* bm = new base_mod;
    
    mg.set_module(bm);
    
    mg.generate(0,0);
    
    cout << "output_to_file : " << mg.output_to_file("./t1.bmp") << endl;
}