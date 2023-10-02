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
    if (lam != 0) result *= lam * lam;
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

//Вспомогательная ф-ия для мат ожидания
double helpforinteg(double x, double v, double u, double lam, int m) {
    double result = 0;
    if (lam != 0) result = (densityM((x - u) / lam, v) / lam);
    else result = densityM(x, v);
    return (result * pow(x, m));
}

//Мат. ожидание
double mathexp(double v, double u, double lam, int m) {
    int i;
    double result, h = 0.1, n = 0;
    n = 2 / h;
    result = h * (helpforinteg(-1, v, u, lam, n) + helpforinteg(1, v, u, lam, m)) / 6.0;
    for(i = 1; i <= n; i++)
	    result = result + 4.0 / 6.0 * h * helpforinteg(-1 + h * (i - 0.5), v, u, lam, m);
    for(i = 1; i <= n-1; i++)
	    result = result + 2.0 / 6.0 * h * helpforinteg(-1 + h * i, v, u, lam, m);
    return result;
}

//Коэф. асимметрии
double asymmetry(double v, double u, double lam) {
    double result = 0;
    result = mathexp(v, u, lam, 3) - 3 * mathexp(v, u, lam, 2) * mathexp(v, u, lam, 1) + 2 * pow(mathexp(v, u, lam, 1), 3);
    result /= pow(dispersion(v, lam), 3 / 2);
    return result;
}

void testStandart() {
    
}
