#include <iostream>
#include <vector>
using namespace std;

int absolute_frequency(const vector<double>& sample, double min, double max);
double empirical_density(double x, const vector<double>& sample);
double math_expectation(const vector<double>& sample);
double dispersion(const vector<double>& sample);
double asymmetry(const vector<double>& sample);
double excess(const vector<double>& sample);