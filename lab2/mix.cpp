#include "Header.h"

//Генерация выборки для смеси распределений
vector<double> random_sample_mix(Standart Func, double p, int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix(Func, p));
    }
    return sample;
}

//Вывод результата ф-ии плотности для смеси распределений в файл
void  result_to_file_mix(Standart Func1, Standart Func2, vector<double> sample, double p) {
    ofstream out, out2;
    out.open("txts/Mix.txt");
    out2.open("txts/MixX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << densityMix(Func1, Func2, sample[i], p) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

//Функция плотости
double densityMix(Standart Func1, Standart Func2, double x, double p) {
    double density1 = Func1.density(x);
    double density2 = Func2.density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

//Математическое ожидание
double mathexpMix(Standart Func1, Standart Func2, double p) {
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//Дисперсия
double dispersionMix(Standart Func1, Standart Func2, double p) {
    double mathExpMix = mathexpMix(Func1, Func2, p);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double dispersion1 = Func1.dispersion();
    double dispersion2 = Func2.dispersion();
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2); 
    return result;
}

//Асимметрия
double asymmetryMix(Standart Func1, Standart Func2, double p) {
    double mathExpMix = mathexpMix(Func1,  Func2, p);
    double mathExp1 = Func1.mathexp();
    double mathExp2 = Func2.mathexp();
    double dispersion1 = Func1.dispersion();
    double dispersion2 = Func2.dispersion();
    double dispersionMixx = dispersionMix(Func1, Func2, p);
    double assymetry1 = Func1.asymmetry();
    double assymetry2 = Func2.asymmetry();
    double result = 1 / pow(dispersionMixx, 3 / 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 3) + 3 * (mathExp1 - mathExpMix) * dispersion1 + pow(dispersion1, 3/2)*assymetry1) + 
        p * (pow(mathExp2 - mathExpMix, 3) + 3 * (mathExp2 - mathExpMix) * dispersion2 + pow(dispersion2, 3 / 2) * assymetry2)
        );
    return result;
}

//Эксцесс
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
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) * 
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * (exces1 + 3)) + 
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

//Моделирование случайной величины
double generateMix(Standart Func, double p) {
    double r = Rgenerate();
    double res;
    if (r > p)
        res = Func.Xgenerate();
    else
        res = Func.Xgenerate();
    return res;
}

void testMix() {
    cout << "Testing a mixture of distributions\n";
    cout << "x = 0, p = 0.5, v1 = 0.5, u1 = 1, lambda1 = 1, v2 = 0.5, u2 = 1, lambda2 = 2\n";
    Standart Func1;
    Standart Func2;
    Func1 = Standart(0.5, 2, 1);
    Func2 = Standart(0.5, 2, 1);
    double d = densityMix(Func1, Func2, 0, 0.5);
    assert(fabs(d - 0.63662 < 0.001));
    cout << "f(x, v) = " << d << "\n";
    double m = mathexpMix(Func1, Func2, 0.5);
    assert(fabs(m - 1 < 0.001));
    cout << "M(X) = " << m << "\n";
    double dis = dispersionMix(Func1, Func2, 0.5);
    assert(fabs(dis - 1 < 0.001));
    cout << "D(X) = " << dis << "\n";
    double a = asymmetryMix(Func1, Func2, 0.5);
    double e = excesMix(Func1, Func2, 0.5);
    cout << e;
    assert(fabs(e - (-1) < 0.001));
    cout << "Y1 = " << a << "\n";
    assert(fabs(a - 0.014282 < 0.001));
    cout << "Y2 = " << e << "\n";

    cout << "All tests are complete\n" << endl;
}