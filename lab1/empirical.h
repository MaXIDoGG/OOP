#include <iostream>
#include <vector>
using namespace std;

double empirical_density(double x, const vector<double>& sample);
double empirical_density_file(const string& filename, double x);
double math_expectation(const vector<double>& sample);
double dispersion(const vector<double>& sample);
double asymmetry(const vector<double>& sample);
double excess(const vector<double>& sample);
vector<double> random_sample_simulation(int n);
double random_var_simulation(const vector<double>& sample);
int empirical_test();