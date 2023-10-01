#include <iostream>
#include <vector>
using namespace std;

double empirical_density(double x, const vector<double>& sample);
double math_expectation(const vector<double>& sample);
double dispersion(const vector<double>& sample);
double asymmetry(const vector<double>& sample);
double excess(const vector<double>& sample);
vector<double> random_sample_simulation();
double random_var_simulation(const vector<double>& sample);