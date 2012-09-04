#include "../src/map_grid.h"
#include "../src/modules/include_all_modules.h"

#include <iostream>
#include <sstream>
#include <time.h>

using namespace noise;
using namespace std;

void test_constant(const size_t& test_num);
void test_perlin(  const size_t& test_num);

void test_abs(     const size_t& test_num);
void test_shift(   const size_t& test_num);
void test_scale(   const size_t& test_num);
void test_invert(  const size_t& test_num);

void test_avg(     const size_t& test_num);
void test_min(     const size_t& test_num);
void test_max(     const size_t& test_num);
void test_add(     const size_t& test_num);
void test_subt(    const size_t& test_num);

void test_interp(  const size_t& test_num);

string i_to_s(const size_t& i)
{
    string s;
    stringstream out;
    out << i;
    s = out.str();
    return s;
}

int main()
{
    cout << "Begin tests" << endl;
    int start_time = clock();
    
    test_constant(0);
    test_perlin(  1);

    test_abs(     2);
    test_shift(   3);
    test_scale(   4);
    test_invert(  5);

    test_avg(     6);
    test_min(     7);
    test_max(     8);
    test_add(     9);
    test_subt(    10);

    test_interp(  11);
    
    int end_time = clock();
    cout << "Tests completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds." << endl;
}

void test_constant(const size_t& test_num);
{
    cout << "\tBegin test_constant" << endl;
    map_grid mg(128,128);
    const_mod* bm = new const_mod;
    
    mg.set_module(bm);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    cout << "\t\toutput_to_file : " << mg.output_to_file("./t_" + i_to_s(test_num) + "const.bmp") << endl;
    cout << "test_constant completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds." << endl;
}

void test_perlin(  const size_t& test_num)
{
    cout << "\tBegin test_constant" << endl;
    map_grid mg(128,128);
    perlin_mod* bm = new perlin_mod;
    
    mg.set_module(bm);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    cout << "\t\toutput_to_file : " << mg.output_to_file("./t_" + i_to_s(test_num) + "perlin.bmp") << endl;
    cout << "test_constant completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds." << endl;
}

void test_abs(     const size_t& test_num);
void test_shift(   const size_t& test_num);
void test_scale(   const size_t& test_num);
void test_invert(  const size_t& test_num);

void test_avg(     const size_t& test_num);
void test_min(     const size_t& test_num);
void test_max(     const size_t& test_num);
void test_add(     const size_t& test_num);
void test_subt(    const size_t& test_num);

void test_interp(  const size_t& test_num);
