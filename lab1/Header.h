#define _USE_MATH_DEFINES 
#include "spec_func.hpp"
#include <iostream>
#include <random>
#include "vector"
#include <math.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;


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
double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double excesMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
vector<double> generateMix(double p, double v1, double v2);
void testMix();
vector<vector<double> > random_sample_mix(double p, double v1, double v2, int N);
vector<double> random_sample_for_empmix(vector<vector<double> > sample, double u, double lam, double p, double u2, double lam2, int N);
void  result_to_file_mix(vector<double> sample, double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
vector<double> help(vector<vector<double> > sample, int n);

//standart
double excess(double v);
double Rgenerate();
double Xgenerate(double v);
double dispersion(double v, double lam, double u);
double densityM(double x, double v);
double density(double x, double v, double u, double lam);
double mathexp(double u);
double asymmetry(double v, double u, double lam);
void testStandart();
vector<double> random_sample_standart(int N, double v);
void result_to_file_standart(vector<double> sample, double v, double u, double lam);
vector<double> random_sample_for_empstd(vector<double> sample, double u, double lam);