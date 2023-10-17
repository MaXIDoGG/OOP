#define _USE_MATH_DEFINES 

#include "StandartClass.h"

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
double Rgenerate();
void testStandart();
void testClass();