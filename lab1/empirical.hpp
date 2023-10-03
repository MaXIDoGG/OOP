#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include <cassert>
#include <fstream>
using namespace std;

double empirical_density(double x, const vector<double>& sample);
double math_expectation(const vector<double>& sample);
double dispersion(const vector<double>& sample);
double asymmetry(const vector<double>& sample);
double EmpExcess(const vector<double>& sample);
vector<double> random_sample_simulation(int n);
double random_var_simulation(const vector<double>& sample);
void result_to_file_empirical(vector<double> sample, int mod);
int empirical_test();