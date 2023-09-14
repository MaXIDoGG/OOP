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
double helpforinteg(double x, double v, double u, double lam) {
    double result = 0;
    if (lam != 0) result = (densityM((x - u) / lam, v) / lam);
    else result = densityM(x, v);
    return (result * x);
}

//Мат. ожидание
double mathexp(double a, double b, double v, double u, double lam) {
    int i;
    double result, h = 0.1, n = 0;
    n = (b - a) / h;
    result = h * (helpforinteg(a, v, u, lam) + helpforinteg(b, v, u, lam)) / 6.0;
    for(i = 1; i <= n; i++)
	    result = result + 4.0 / 6.0 * h * helpforinteg(a + h * (i - 0.5), v, u, lam);
    for(i = 1; i <= n-1; i++)
	    result = result + 2.0 / 6.0 * h * helpforinteg(a + h * i, v, u, lam);
    return result;
}

//Коэф. асимметрии
double asymmetry(double v, double u, double lam) {
    double a = -1 - mathexp(-1, 1, v, u, lam);
    double b = 1 - mathexp(-1, 1, v, u, lam);
    double result = mathexp(a, b, v, u, lam);
    result /= pow(dispersion(v, lam), 3 / 2);
    return result;
}
