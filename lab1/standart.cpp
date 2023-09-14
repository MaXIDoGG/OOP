#include "pirsonII.hpp"

//Бета-функция по формуле из методички
double betafunc(double x, double y) {
    return (gamma(x) * gamma(y) / gamma(x + y));
}

//Ф-ия плотности f(x, v) без параметров сдвига и масштаба
double densityM(double x, double v) {
   return (pow((1 - x * x) / 4, v) / (2 * betafunc(v + 1, v + 1)));
}

//Ф-ия плотности f(x, v)
double density(double x, double v, double u, double lam) {
    double result = 0;
    if (lam != 0) result = (densityM((x - u) / lam, v) / lam);
    else result = densityM(x, v);
    return result;
}

//Ф-ия Дисперсии
double dispersion(double v, double lam) {
    double result = 0;
    result = (1 / (2 * v + 3));
    if (lam != 0) result *= lam;
    return result;
}

//Ф-ия эксцесса
double exces(double v) {
    return (-6 / (2 * v + 5));
}

//реализации случайной величины r, равномерно распределенной на интервале (0, 1)
double Rgenerate() {
    double a = 0, b = 1;
    srand((unsigned)time(0));
    double r = rand() % (int)pow(10, 4);
    r = a + (r / pow(10, 4)) * (b - a);
    return r;
}

//Моделирование случайной величины
double Xgenerate(double v) {
    return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * sin(2 * M_PI * Rgenerate()));
}