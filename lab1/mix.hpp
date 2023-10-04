#include "spec_func.hpp"
#include <iostream>
#include "vector"
#include <cassert>
#include <math.h>
#include <time.h>

using namespace std;

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