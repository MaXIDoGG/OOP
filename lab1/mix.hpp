#include "spec_func.hpp"
#include <iostream>
#include "vector"
#include <math.h>
#include <time.h>

double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
double excesMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2);
void testMix();