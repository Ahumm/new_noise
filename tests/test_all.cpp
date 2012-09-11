#include "../src/map_grid.h"
#include "../src/modules/include_all_modules.h"

#include <iostream>
#include <sstream>
#include <time.h>

#define CLAMP_VALUES 0

using namespace noise;
using namespace std;

void test_constant(const size_t& test_num, const float& val);
void test_perlin(  const size_t& test_num,  const int& seed);

void test_abs(     const size_t& test_num                  );
void test_shift(   const size_t& test_num                  );
void test_scale(   const size_t& test_num                  );
void test_invert(  const size_t& test_num                  );

void test_avg(     const size_t& test_num                  );
void test_min(     const size_t& test_num                  );
void test_max(     const size_t& test_num                  );
void test_add(     const size_t& test_num                  );
void test_subt(    const size_t& test_num                  );

void test_interp(  const size_t& test_num);

string i_to_s(const size_t& i)
{
    string s;
    stringstream out;
    out << i;
    s = out.str();
    return s;
}
string f_to_s(const float& i)
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
    
    test_constant(0,-1.0f);
    test_constant(1,-0.5f);
    test_constant(2,0.0f);
    test_constant(3,0.5f);
    test_constant(4,1.0f);
    test_perlin(  5, 0  );
    test_perlin(  6, 1  );

    test_abs(     7);
    test_shift(   8);
    test_scale(   9);
    test_invert( 10);

    test_avg(    11);
    test_min(    12);
    test_max(    13);
    test_add(    14);
    test_subt(   15);

    test_interp(  16);
    
    int end_time = clock();
    cout << "Tests completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_constant(const size_t& test_num, const float& val)
{
    cout << "\tBegin test_constant " << val << endl;
    map_grid mg(128,128);
    const_mod* bm = new const_mod(val);
    
    mg.set_module(bm);
    
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_" + f_to_s(val) + "_const.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_constant completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_perlin(  const size_t& test_num,  const int& seed)
{
    cout << "\tBegin test_perlin" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m = new perlin_mod(0.5f, 6, seed);
    
    mg.set_module(p_m);
    
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif

    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_perlin.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_perlin completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_abs(     const size_t& test_num)
{
    cout << "\tBegin test_abs" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    abs_m->set_mod(0, p_m);
    
    mg.set_module(abs_m);
    
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_abs.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_abs completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_shift(   const size_t& test_num)
{
    cout << "\tBegin test_shift" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    shift_mod* sh_m = new shift_mod;
    
    abs_m->set_mod(0, p_m);
    
    sh_m->set_mod(0,abs_m);
    sh_m->set_factor(-0.5f);
    
    mg.set_module(sh_m);
    
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_shift.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_shift completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_scale(   const size_t& test_num)
{
    cout << "\tBegin test_scale" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    shift_mod* sh_m = new shift_mod;
    scale_mod* sc_m = new scale_mod;
    
    abs_m->set_mod(0, p_m);
    
    sh_m->set_mod(0,abs_m);
    sh_m->set_factor(-0.5f);
    
    sc_m->set_mod(0,sh_m);
    sc_m->set_factor(2.0f);
    
    mg.set_module(sc_m);

#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_scale.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_scale completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_invert(  const size_t& test_num)
{
    cout << "\tBegin test_invert" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    shift_mod* sh_m = new shift_mod;
    scale_mod* sc_m = new scale_mod;
    invert_mod* i_m = new invert_mod;
    
    abs_m->set_mod(0, p_m);
    
    sh_m->set_mod(0,abs_m);
    sh_m->set_factor(-0.5f);
    
    sc_m->set_mod(0,sh_m);
    sc_m->set_factor(2.0f);
    
    i_m->set_mod(0,sc_m);
    
    mg.set_module(i_m);

#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_invert.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_invert completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}


void test_avg(     const size_t& test_num)
{
    cout << "\tBegin test_avg" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    avg_mod* avg_m = new avg_mod;
    
    avg_m->set_mod(0, p_m0);
    avg_m->set_mod(1, p_m1);
    
    mg.set_module(avg_m);

#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_avg.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_avg completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_min(     const size_t& test_num)
{
    cout << "\tBegin test_min" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    min_mod* min_m = new min_mod;
    
    min_m->set_mod(0, p_m0);
    min_m->set_mod(1, p_m1);
    
    mg.set_module(min_m);

#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_min.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_min completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_max(     const size_t& test_num)
{
    cout << "\tBegin test_max" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    max_mod* max_m = new max_mod;
    
    max_m->set_mod(0, p_m0);
    max_m->set_mod(1, p_m1);
    
    mg.set_module(max_m);

#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_max.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_max completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_add(     const size_t& test_num)
{
    cout << "\tBegin test_add" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    add_mod* add_m = new add_mod;
    
    add_m->set_mod(0, p_m0);
    add_m->set_mod(1, p_m1);
    
    mg.set_module(add_m);
mg.set_auto_scale(false);
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_add.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_add completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_subt(    const size_t& test_num)
{
    cout << "\tBegin test_subt" << endl;
    map_grid mg(128,128);
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    subt_mod* subt_m = new subt_mod;
    
    subt_m->set_mod(0, p_m0);
    subt_m->set_mod(1, p_m1);
    
    mg.set_module(subt_m);
mg.set_auto_scale(false);
#if CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_subt.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_subt completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_interp(  const size_t& test_num){}
