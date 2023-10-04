#include "spec_func.hpp"
#include <iostream>
#include "vector"
#include <random>
#include <math.h>
#include <cassert>
#include <algorithm>
#include <fstream>

using namespace std;

double excess(double v);
double Rgenerate();
double Xgenerate(double v);
double dispersion(double v, double lam, double u);
double densityM(double x, double v);
double density(double x, double v, double u, double lam);
double mathexp(double v, double u, double lam, int n);
double asymmetry(double v, double u, double lam);
void testStandart();
vector<double> random_sample_standart(int N, double v);
void result_to_file_standart(vector<double> sample, double v, double u, double lam);
