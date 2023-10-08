#include "Header.h"

//Генерация выборки для стандартного распределения
vector<double> random_sample_standart(int N, double v) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(Xgenerate(v));
    }
    return sample;
}

//Вывод значений ф-ии плотности по выборке в файл
void result_to_file_standart(vector<double> sample, double v, double u, double lam) {
    ofstream out, out2;
    out.open("txts/Standart.txt");
    out2.open("txts/StandartX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << density(sample[i], v, u, lam) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

//Бета-функция по формуле из методички
double betafunc(double x, double y) {
    return (gamma(x) * gamma(y) / gamma(x + y));
}

//Ф-ия плотности f(x, v)
double density(double x, double v, double u, double lam) {
    double result = 0;
    result = (pow((1 - x * x) / 4, v) / (2 * betafunc(v + 1, v + 1)));
    return result;
}

//Ф-ия Дисперсии
double dispersion(double v, double lam, double u) {
    double result = 0;
    result = (1 / (2 * v + 3));
    if (lam != 1 || u != 0) result *= lam * lam;
    return result;
}

//Ф-ия эксцесса
double excess(double v) {
    return (-6 / (2 * v + 5));
}

//реализации случайной величины r, равномерно распределенной на интервале (0, 1)
double Rgenerate() {
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_real_distribution<double> dis(0, 1);
    // return dis(gen);
    double r; 
    do r = (double)rand() / RAND_MAX; while (r == 0 || r == 1); 
    return r; 
}

//Моделирование случайной величины
double Xgenerate(double v) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    if(dis(gen) >= 0.5)
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * sin(2 * M_PI * Rgenerate()));
    else
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * cos(2 * M_PI * Rgenerate()));
}

//Мат. ожидание
double mathexp(double u) {
    if (u != 0) return u;
    return 0;
}   

//Коэф. асимметрии
double asymmetry(double v, double u, double lam) {
    double result = 0;
    result = mathexp(u) - 3 * mathexp(u) * mathexp(u) + 2 * pow(mathexp(u), 3);
    result /= pow(dispersion(v, lam, u), 3 / 2);
    return result;
}

void testStandart() {
    double x = 0, u = 0, lam = 1;
    cout << "Тестирование стандартного распределения с параметрами x = 0, u = 0, lambda = 1\n";
    double d = density(x, 0, u, lam), m = mathexp(u), dis = dispersion(0, lam, u), exc = excess(0);
    float a = asymmetry(0, u, lam);
    assert(fabs(d - 0.5) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.333333) < 0.01);
    assert(fabs(exc - (-1.2)) < 0.01);
    assert(fabs(a - 2.77778e-05) < 0.01);
    cout << "v = 0\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    d = density(x, 6, u, lam), m = mathexp(u), dis = dispersion(6, lam, u), exc = excess(6), a = asymmetry(6, u, lam);
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.0666) < 0.01);
    assert(fabs(exc - (-0.3529)) < 0.01);
    assert(fabs(a - 5.803e-17) < 0.01);
    cout << "v = 6\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    cout << "Тестирование сдвиг-масштабного распределения с параметрами x = 0, u - произольное, lambda = 2\n";
    u = 3, lam = 2;
    d = density(x, 1, u, lam), m = mathexp(u), dis = dispersion(1, lam, u), exc = excess(1), a = asymmetry(1, u, lam);
    assert(fabs(d - 0.75) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.8) < 0.1);
    assert(fabs(exc - (-0.85714)) < 0.01);
    assert(fabs(a - 37.5) < 0.01);
    cout << "v = 1, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    d = density(x, 4, u, lam), m = mathexp(u), dis = dispersion(4, lam, u), exc = excess(4), a = asymmetry(4, u, lam);
    assert(fabs(d - 1.23047) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.363636) < 0.01);
    assert(fabs(exc - (-0.461538)) < 0.01);
    assert(fabs(a - 82.5) < 0.01); 
    cout << "v = 4, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
    cout << "All tests are complete\n\n";
}
