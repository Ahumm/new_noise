#include "../src/map_grid.h"
#include "../src/modules/include_all_modules.h"

#include <iostream>
#include <sstream>
#include <time.h>

#define CLAMP_VALUES 0
#define MAP_SIZE 1024
#define ZOOM_LEVEL 8.0f

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

void test_floor_a(   const size_t& test_num);
void test_floor_b(   const size_t& test_num);
void test_ceiling_a( const size_t& test_num);
void test_ceiling_b(   const size_t& test_num);

static map_grid mg(MAP_SIZE,MAP_SIZE);

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
#if !CLAMP_VALUES
    mg.set_auto_scale(false);
#endif
    mg.set_x_zoom(ZOOM_LEVEL);
    mg.set_y_zoom(ZOOM_LEVEL);

    cout << "Begin tests" << endl;
    int start_time = clock();
    
    test_constant(0,-1.0f);
    test_constant(1,-0.5f);
    test_constant(2,0.0f);
    test_constant(3,0.5f);
    test_constant(4,1.0f);
    test_perlin(  5, 0  );
    test_perlin(  6, 1  );

    test_abs(        7);
    test_shift(      8);
    test_scale(      9);
    test_invert(    10);

    test_avg(       11);
    test_min(       12);
    test_max(       13);
    test_add(       14);
    test_subt(      15);

    test_interp(    16);
    
    test_floor_a(   17);
    test_floor_b(   18);
    test_ceiling_a( 19);
    test_ceiling_b( 20);
    
    int end_time = clock();
    cout << "Tests completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_constant(const size_t& test_num, const float& val)
{
    cout << "\tBegin test_constant " << val << endl;
    const_mod* bm = new const_mod(val);
    
    mg.set_module(bm);
    
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
    perlin_mod* p_m = new perlin_mod(0.5f, 6, seed);
    
    mg.set_module(p_m);

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
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    abs_m->set_mod(0, p_m);
    
    mg.set_module(abs_m);
    
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
    perlin_mod* p_m = new perlin_mod(0.5f, 6, 0);
    abs_mod* abs_m = new abs_mod;
    shift_mod* sh_m = new shift_mod;
    
    abs_m->set_mod(0, p_m);
    
    sh_m->set_mod(0,abs_m);
    sh_m->set_factor(-0.5f);
    
    mg.set_module(sh_m);
    
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
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    avg_mod* avg_m = new avg_mod;
    
    avg_m->set_mod(0, p_m0);
    avg_m->set_mod(1, p_m1);
    
    mg.set_module(avg_m);

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
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    min_mod* min_m = new min_mod;
    
    min_m->set_mod(0, p_m0);
    min_m->set_mod(1, p_m1);
    
    mg.set_module(min_m);

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
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    max_mod* max_m = new max_mod;
    
    max_m->set_mod(0, p_m0);
    max_m->set_mod(1, p_m1);
    
    mg.set_module(max_m);

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
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    add_mod* add_m = new add_mod;
    
    add_m->set_mod(0, p_m0);
    add_m->set_mod(1, p_m1);
    
    mg.set_module(add_m);
    
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
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    subt_mod* subt_m = new subt_mod;
    
    subt_m->set_mod(0, p_m0);
    subt_m->set_mod(1, p_m1);
    
    mg.set_module(subt_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_subt.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_subt completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_interp(  const size_t& test_num)
{
    cout << "\tBegin test_interp" << endl;
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    perlin_mod* p_m1 = new perlin_mod(0.5f, 6, 1);
    perlin_mod* p_m2 = new perlin_mod(0.5f, 6, 2);
    interp_mod* interp_m = new interp_mod;
    
    interp_m->set_mod(0, p_m0);
    interp_m->set_mod(1, p_m1);
    interp_m->set_mod(2, p_m2);
    
    mg.set_module(interp_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_interp.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_interp completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_floor_a(   const size_t& test_num)
{
    cout << "\tBegin test_floor_a" << endl;
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    floor_a_mod* floor_a_m = new floor_a_mod;
    
    floor_a_m->set_mod(0, p_m0);
    
    mg.set_module(floor_a_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_floor_a.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_floor_a completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_floor_b(   const size_t& test_num)
{
    cout << "\tBegin test_floor_b" << endl;
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    floor_b_mod* floor_b_m = new floor_b_mod;
    
    floor_b_m->set_mod(0, p_m0);
    
    mg.set_module(floor_b_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_floor_b.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_floor_b completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_ceiling_a( const size_t& test_num)
{
    cout << "\tBegin test_ceiling_a" << endl;
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    ceiling_a_mod* ceiling_a_m = new ceiling_a_mod;
    
    ceiling_a_m->set_mod(0, p_m0);
    
    mg.set_module(ceiling_a_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_ceiling_a.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_ceiling_a completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void test_ceiling_b(   const size_t& test_num)
{
    cout << "\tBegin test_ceiling_b" << endl;
    perlin_mod* p_m0 = new perlin_mod(0.5f, 6, 0);
    ceiling_b_mod* ceiling_b_m = new ceiling_b_mod;
    
    ceiling_b_m->set_mod(0, p_m0);
    
    mg.set_module(ceiling_b_m);
    
    int start_time = clock();
    mg.generate(0,0);
    int end_time = clock();
    
    string of_name = "./results/t_" + i_to_s(test_num) + "_ceiling_b.bmp";
    cout << "\t\toutput_to_file : " << mg.output_to_file(of_name.c_str()) << endl;
    cout << "\ttest_ceiling_b completed : " << (end_time - start_time) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}