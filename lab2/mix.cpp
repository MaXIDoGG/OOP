#include "Header.h"
<<<<<<< HEAD
#include "StandartClass.h"

//Генерация выборки для смеси распределений
vector<double> random_sample_mix(double p, double v1, double v2, int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix(p, v1, v2));
=======

//Генерация выборки для смеси распределений
vector<double> random_sample_mix(Standart Func, double p, int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix(Func, p));
>>>>>>> evohox
    }
    return sample;
}

//Вывод результата ф-ии плотности для смеси распределений в файл
<<<<<<< HEAD
void  result_to_file_mix(vector<double> sample, double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
=======
void  result_to_file_mix(Standart Func1, Standart Func2, vector<double> sample, double p) {
>>>>>>> evohox
    ofstream out, out2;
    out.open("txts/Mix.txt");
    out2.open("txts/MixX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
<<<<<<< HEAD
        out << densityMix(sample[i], p, v1, u1, lam1, v2, u2, lam2) << endl;
=======
        out << densityMix(Func1, Func2, sample[i], p) << endl;
>>>>>>> evohox
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

//Функция плотости
<<<<<<< HEAD
double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    Standart Func1 = Standart(v1, lam1, u1);
    Standart Func2 = Standart(v2, lam2, u2);
=======
double densityMix(Standart Func1, Standart Func2, double x, double p) {
>>>>>>> evohox
    double density1 = Func1.density(x);
    double density2 = Func2.density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

//Математическое ожидание
<<<<<<< HEAD
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    Standart Func1 = Standart(v1, lam1, u1);
    Standart Func2 = Standart(v2, lam2, u2);
=======
double mathexpMix(Standart Func1, Standart Func2, double p) {
>>>>>>> evohox
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//Дисперсия
<<<<<<< HEAD
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(u1);
    double mathExp2 = mathexp(u2);
    double dispersion1 = dispersion(v1, lam1, u1);
    double dispersion2 = dispersion(v2, lam2, u2);
=======
double dispersionMix(Standart Func1, Standart Func2, double p) {
    double mathExpMix = mathexpMix(Func1, Func2, p);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double dispersion1 = Func1.dispersion();
    double dispersion2 = Func2.dispersion();
>>>>>>> evohox
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2); 
    return result;
}

//Асимметрия
<<<<<<< HEAD
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(u1);
    double mathExp2 = mathexp(u2);
    double dispersion1 = dispersion(v1, lam1, u1);
    double dispersion2 = dispersion(v2, lam2, u2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
=======
double asymmetryMix(Standart Func1, Standart Func2, double p) {
    double mathExpMix = mathexpMix(Func1,  Func2, p);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double dispersion1 = Func1.dispersion();
    double dispersion2 = Func2.dispersion();
    double dispersionMixx = dispersionMix(Func1, Func2, p);
    double assymetry1 = Func1.asymmetry();
    double assymetry2 = Func2.asymmetry();
>>>>>>> evohox
    double result = 1 / pow(dispersionMixx, 3 / 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 3) + 3 * (mathExp1 - mathExpMix) * dispersion1 + pow(dispersion1, 3/2)*assymetry1) + 
        p * (pow(mathExp2 - mathExpMix, 3) + 3 * (mathExp2 - mathExpMix) * dispersion2 + pow(dispersion2, 3 / 2) * assymetry2)
        );
    return result;
}

//Эксцесс
<<<<<<< HEAD
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
=======
double excesMix(Standart Func1, Standart Func2, double p) {
    double mathExpMix = mathexpMix(Func1, Func2, p);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double dispersion1 = Func1.dispersion();
    double dispersion2 = Func2.dispersion();
    double dispersionMixx = dispersionMix(Func1, Func2, p);
    double assymetry1 = Func1.asymmetry();
    double assymetry2 = Func2.asymmetry();
    double exces1 = Func1.excess();
    double exces2 = Func2.excess();
>>>>>>> evohox
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) * 
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * (exces1 + 3)) + 
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

//Моделирование случайной величины
<<<<<<< HEAD
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
=======
double generateMix(Standart Func, double p) {
    double r = Func.Rgenerate();
    double res;
    if (r > p)
        res = Func.Xgenerate();
    else
        res = Func.Xgenerate();
    return res;
>>>>>>> evohox
}