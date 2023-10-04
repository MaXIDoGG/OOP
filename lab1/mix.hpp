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
double generateMix(double p, double v1, double v2);
void testMix();
vector<double> random_sample_mix(double p, double v1, double v2, int n);
