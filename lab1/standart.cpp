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
    if (lam != 1 && u != 0) result = (densityM((x - u) / lam, v) / lam);
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
double excess(double v) {
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
    if(u != 0 && lam != 1) result *= u;
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
    double x = 0, u = 0, lam = 1;
    cout << "Тестирование стандартного распределения с параметрами x = 0, u = 0, lambda = 1\n";
    double d = density(x, 0, u, lam), m = mathexp(0, u, lam, 1), dis = dispersion(0, lam), exc = excess(0), a = asymmetry(0, u, lam);
    assert(fabs(d - 0.5) < 0.01);
    assert(fabs(m - 0.5) < 0.01);
    assert(fabs(dis - 0.5) < 0.01);
    assert(fabs(exc - 0.5) < 0.01);
    assert(fabs(a - 0.5) < 0.01);
    cout << "v = 0, f(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
    d = density(x, 6, u, lam), m = mathexp(6, u, lam, 1), dis = dispersion(6, lam), exc = excess(6), a = asymmetry(6, u, lam);
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - 0.5) < 0.01);
    assert(fabs(dis - 0.5) < 0.01);
    assert(fabs(exc - 0.5) < 0.01);
    assert(fabs(a - 0.5) < 0.01);
    cout << "v = 6, f(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
    cout << "Тестирование сдвиг-масштабного распределения с параметрами x = 0, u - произольное, lambda = 2\n";
    u = 3; d = density(x, 1, u, lam), m = mathexp(1, u, lam, 1), dispersion(1, lam), exc = excess(1), a = asymmetry(1, u, lam);
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - 0.5) < 0.01);
    assert(fabs(dis - 0.5) < 0.01);
    assert(fabs(exc - 0.5) < 0.01);
    assert(fabs(a - 0.5) < 0.01);
    cout << "v = 1, u = 3, f(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
    u = 3; d = density(x, 6, u, lam), m = mathexp(6, u, lam, 1), dispersion(6, lam), exc = excess(6), a = asymmetry(6, u, lam);
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - 0.5) < 0.01);
    assert(fabs(dis - 0.5) < 0.01);
    assert(fabs(exc - 0.5) < 0.01);
    assert(fabs(a - 0.5) < 0.01);
    cout << "v = 6, u = 3, f(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
    cout << "All tests are completed";
}
