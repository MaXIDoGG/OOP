#include "Header.h"
#include "StandartClass.h"

//Генерация выборки для смеси распределений
vector<double> random_sample_mix(double p, double v1, double v2, int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix(p, v1, v2));
    }
    return sample;
}

//Вывод результата ф-ии плотности для смеси распределений в файл
void  result_to_file_mix(vector<double> sample, double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    ofstream out, out2;
    out.open("txts/Mix.txt");
    out2.open("txts/MixX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << densityMix(sample[i], p, v1, u1, lam1, v2, u2, lam2) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

//Функция плотости
double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    Standart Func1 = Standart(v1, lam1, u1);
    Standart Func2 = Standart(v2, lam2, u2);
    double density1 = Func1.density(x);
    double density2 = Func2.density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

//Математическое ожидание
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    Standart Func1 = Standart(v1, lam1, u1);
    Standart Func2 = Standart(v2, lam2, u2);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//Дисперсия
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(u1);
    double mathExp2 = mathexp(u2);
    double dispersion1 = dispersion(v1, lam1, u1);
    double dispersion2 = dispersion(v2, lam2, u2);
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2); 
    return result;
}

//Асимметрия
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(u1);
    double mathExp2 = mathexp(u2);
    double dispersion1 = dispersion(v1, lam1, u1);
    double dispersion2 = dispersion(v2, lam2, u2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
    double result = 1 / pow(dispersionMixx, 3 / 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 3) + 3 * (mathExp1 - mathExpMix) * dispersion1 + pow(dispersion1, 3/2)*assymetry1) + 
        p * (pow(mathExp2 - mathExpMix, 3) + 3 * (mathExp2 - mathExpMix) * dispersion2 + pow(dispersion2, 3 / 2) * assymetry2)
        );
    return result;
}

//Эксцесс
double excesMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(u1);
    double mathExp2 = mathexp(u2);
    double dispersion1 = dispersion(v1, lam1, u1);
    double dispersion2 = dispersion(v2, lam2, u2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
    double exces1 = excess(v1);
    double exces2 = excess(v2);
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) * 
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * (exces1 + 3)) + 
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

//Моделирование случайной величины
double generateMix(double p, double v1, double v2) {
    double r = Rgenerate();
    double res;
    if (r > p)
        res = Xgenerate(v1);
    else
        res = Xgenerate(v2);
    return res;
}

void testMix() {
    cout << "Testing a mixture of distributions\n";
    cout << "x = 0, p = 0.5, v1 = 0.5, u1 = 1, lambda1 = 1, v2 = 0.5, u2 = 1, lambda2 = 2\n";
    double d = densityMix(0, 0.5, 0.5, 1, 2, 0.5, 1, 2);
    assert(fabs(d - 0.63662 < 0.001));
    cout << "f(x, v) = " << d << "\n";
    double m = mathexpMix(0.5, 0.5, 1, 2, 0.5, 1, 2);
    assert(fabs(m - 1 < 0.001));
    cout << "M(X) = " << m << "\n";
    double dis = dispersionMix(0.5, 0.5, 1, 2, 0.5, 1, 2);
    assert(fabs(dis - 1 < 0.001));
    cout << "D(X) = " << dis << "\n";
    double a = asymmetryMix(0.5, 0.5, 1, 2, 0.5, 1, 2);
    double e = excesMix(0.5, 0.5, 1, 2, 0.5, 1, 2);
    assert(fabs(e - (-1) < 0.001));
    cout << "Y1 = " << a << "\n";
    assert(fabs(a - 0.014282 < 0.001));
    cout << "Y2 = " << e << "\n";

    cout << "All tests are complete\n" << endl;
}