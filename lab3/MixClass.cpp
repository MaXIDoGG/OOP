#include "Header.h"

Mixture::Mixture() : p(0.5) {
    s1 = *(new Standart(1, 1, 0));
    s2 = *(new Standart(1, 1, 0));
}

Mixture::Mixture(Standart& d1, Standart& d2, double p0):
    s1(d1), s2(d2), p(p0 > 0 && p0 < 1 ? p0 : throw 3) {};

Mixture::Mixture(string filename) {
    load(filename);
}

Standart& Mixture::get_comp1() {
    return s1;
}

Standart& Mixture::get_comp2() {
    return s2;
}

//Генерация выборки для смеси распределений
vector<double> Mixture::random_sample_mix(int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix());
    }
    return sample;
}

//Вывод результата ф-ии плотности для смеси распределений в файл
void  Mixture::result_to_file_mix(vector<double> sample) {
    ofstream out, out2;
    out.open("txts/Mix.txt");
    out2.open("txts/MixX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << densityMix(sample[i]) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

double Mixture::getP() {
    return p;
}

void Mixture::setP(double newP){
    if(p > 1 || p < 0)
        throw 3;
    p = newP;
}

//Функция плотости
double Mixture::densityMix(double x) {
    double density1 = s1.density(x);
    double density2 = s2.density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

//Математическое ожидание
double Mixture::mathexpMix() {
    double mathExp1 = s1.mathexp();
    double mathExp2 = s2.mathexp();
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//Дисперсия
double Mixture::dispersionMix() {
    double mathExpMix = mathexpMix();
    double mathExp1 = s1.mathexp();
    double mathExp2 = s2.mathexp();
    double dispersion1 = s1.dispersion();
    double dispersion2 = s2.dispersion();
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2);
    return result;
}

//Асимметрия
double Mixture::asymmetryMix() {
    double mathExpMix = mathexpMix();
    double mathExp1 = s1.mathexp();
    double mathExp2 = s2.mathexp();
    double dispersion1 = s1.dispersion();
    double dispersion2 = s2.dispersion();
    double dispersionMixx = dispersionMix();
    double assymetry1 = s1.asymmetry();
    double assymetry2 = s2.asymmetry();
    double result = 1 / pow(dispersionMixx, 3 / 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 3) + 3 * (mathExp1 - mathExpMix) * dispersion1 + pow(dispersion1, 3/2)*assymetry1) +
        p * (pow(mathExp2 - mathExpMix, 3) + 3 * (mathExp2 - mathExpMix) * dispersion2 + pow(dispersion2, 3 / 2) * assymetry2)
        );
    return result;
}

//Эксцесс
double Mixture::excesMix() {
    double mathExpMix = mathexpMix();
    double mathExp1 = s1.mathexp();
    double mathExp2 = s2.mathexp();
    double dispersion1 = s1.dispersion();
    double dispersion2 = s2.dispersion();
    double dispersionMixx = dispersionMix();
    double assymetry1 = s1.asymmetry();
    double assymetry2 = s2.asymmetry();
    double exces1 = s1.excess();
    double exces2 = s2.excess();
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) *
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * (exces1 + 3)) +
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

//Моделирование случайной величины
double Mixture::generateMix() {
    double r = s1.Rgenerate();
    double res;
    if (r > p)
        res = s1.Xgenerate();
    else
        res = s2.Xgenerate();
    return res;
}

// Сохранение атрибутов в файл
void Mixture::save(string filename) {
    ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        out << s1.getShift() << "\n";
        out << s1.getScale() << "\n";
        out << s1.getShift() << "\n";
        out << s2.getShift() << "\n";
        out << s2.getScale() << "\n";
        out << s2.getShift() << "\n";
        out << p << endl;
    } else throw 0;
    out.close();
}
// Загрузить атрибуты из файла
void Mixture::load(string filename) {
    ifstream in;
    double newU = 0, newLam = 0, newV = 0;
    in.open(filename);
    if (in.is_open())
    {
        in >> newU;
        s1.setShift(newU);
        in >> newLam;
        s1.setScale(newLam);
        in >> newV;
        s1.setForm(newV);
        in >> newU;
        s2.setShift(newU);
        in >> newLam;
        s2.setScale(newLam);
        in >> newV;
        s2.setForm(newV);
        in >> p;
        if (p > 1 || p < 0) throw 3;
    } else throw 0;
    in.close();
}
