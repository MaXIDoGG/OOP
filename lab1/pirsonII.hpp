#include "spec_func.hpp"
#include <iostream>
#include "vector"
#include <math.h>
#include <time.h>

double exces(double v);
double Rgenerate();
double Xgenerate(double v);
double dispersion(double v, double lam);
double densityM(double x, double v);
double density(double x, double v, double u, double lam);
double mathexp(double a, double b, double v, double u, double lam);
double asymmetry(double v, double u, double lam);