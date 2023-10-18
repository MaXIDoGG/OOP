#define _USE_MATH_DEFINES 

<<<<<<< HEAD
#include <iostream>
#include <random>
#include "vector"
#include <math.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>
#include "spec_func.hpp"

using namespace std;


=======
#include "StandartClass.h"

using namespace std;

>>>>>>> evohox
//emperical
double delta_calc(const double n, const double min, const double max);
vector<double> create_intervals(const double delta, const double min, const double max);
int get_interval_index(const vector<double>& intervals, const double x);
double empirical_density(double x, const vector<double>& sample);
double math_expectation(const vector<double>& sample);
double dispersion(const vector<double>& sample);
double asymmetry(const vector<double>& sample);
double EmpExcess(const vector<double>& sample);
vector<double> random_sample_simulation(int n);
double random_var_simulation(const vector<double>& sample);
void result_to_file_empirical(vector<double> sample, int mod);
int empirical_test();

//mix
<<<<<<< HEAD
double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double excesMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double generateMix(double p, double v1, double v2);
void testMix();
vector<double> random_sample_mix(double p, double v1, double v2, int N);
void  result_to_file_mix(vector<double> sample, double p, double v1, double u1, double lam1, double v2, double u2, double lam2);

//standart
double excess(double v);
double Rgenerate();
double Xgenerate(double v);
double dispersion(double v, double lam, double u);
double density(double x, double v, double u, double lam);
double mathexp(double u);
double asymmetry(double v, double u, double lam);
void testStandart();
vector<double> random_sample_standart(int N, double v);
void result_to_file_standart(vector<double> sample, double v, double u, double lam);
=======
double densityMix(Standart Func1, Standart Func2, double x, double p);
double mathexpMix(Standart Func1, Standart Func2, double p);
double dispersionMix(Standart Func1, Standart Func2, double p);
double asymmetryMix(Standart Func1, Standart Func2, double p);
double excesMix(Standart Func1, Standart Func2, double p) ;
double generateMix(Standart Func, double p);
void testMix();
vector<double> random_sample_mix(Standart Func, double p, int N);
void  result_to_file_mix(Standart Func1, Standart Func2, vector<double> sample, double p);

//standart
void testStandart();
void testClass();
>>>>>>> evohox
