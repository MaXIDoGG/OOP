#include "spec_func.hpp"
#include <iostream>
#include "vector"
#include <math.h>
#include <time.h>

double densityMix(double u1, double v1, double lam1, double u2, double v2, double lam2, double x, double p); //+
double mathexpMix(double p, double a, double b, double v1, double u1, double lam1, double v2, double u2, double lam2); //+
double dispersionMix(double p, double a, double b, double v1, double u1, double lam1, double v2, double u2, double lam2); //+
double asymmetryMix(double p, double a, double b, double v1, double u1, double lam1, double v2, double u2, double lam2); //+
double excesMix(double p, double a, double b, double v1, double u1, double lam1, double v2, double u2, double lam2); //++