#include "Header.h"
<<<<<<< HEAD
#include "StandartClass.h"
=======
>>>>>>> evohox


// -- Реализация класса Standart --

double Standart::density(double x) {
    double result = 0;
    result = (pow((1 - x * x) / 4, v) / (2 * betafunc(v + 1, v + 1)));
    return result;
}

void Standart::setShift(double newU) {
    u = newU;
}
// Изменяет параметр масштаба
void Standart::setScale(double newLambda) {
    lambda = newLambda != 0 ? newLambda : throw 1;
}
// Изменяет параметр формы
void Standart::setForm(double newV) {
    v = newV >= 0 ? newV : throw 2;
}

// Возвращает параметр сдвига
double Standart::getShift() {
    return u;
}
// Возвращает параметр масштаба
double Standart::getScale() {
    return lambda;
}
// Возвращает параметр формы
double Standart::getForm() {
    return v;
}

// Мат. ожидание
double Standart::mathexp() {
    if (u != 0) return u;
    return 0;
}
// Ф-ия Дисперсии
double Standart::dispersion() {
    double result = 0;
    result = (1 / (2 * v + 3));
    if (lambda != 1 || u != 0) result *= lambda * lambda;
    return result;
}
// Коэф. асимметрии
double Standart::asymmetry() {
    double result = 0;
    result = mathexp() - 3 * mathexp() * mathexp() + 2 * pow(mathexp(), 3);
    result /= pow(dispersion(), 3 / 2);
    return result;
}
// Ф-ия эксцесса
double Standart::excess() {
    return (-6 / (2 * v + 5));
}

<<<<<<< HEAD
=======
// Реализация случайной величины r, равномерно распределенной на интервале (0, 1)
double Standart::Rgenerate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    return dis(gen);
}


>>>>>>> evohox
// Моделирование случайной величины
double Standart::Xgenerate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    if(dis(gen) >= 0.5)
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * sin(2 * M_PI * Rgenerate()));
    else
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * cos(2 * M_PI * Rgenerate()));
}

// Сохранение атрибутов в файл
void Standart::save(string filename) const {
    ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        out << u << "\n";
        out << lambda << "\n";
        out << v << "\n";
    } else throw 0;
    out.close();
}
// Загрузить атрибуты из файла
void Standart::load(string filename) {
    ifstream in;
<<<<<<< HEAD
    in.open(filename);
    if (in.is_open())
    {
        in >> u;
        in >> lambda;
        in >> v;
=======
    double newU = 0, newLam = 0, newV = 0;
    in.open(filename);
    if (in.is_open())
    {
        in >> newU;
        setShift(newU);
        in >> newLam;
        setScale(newLam);
        in >> newV;
        setForm(newV);
>>>>>>> evohox
    } else throw 0;
    in.close();
}

// Генерация выборки для стандартного распределения
<<<<<<< HEAD
vector<double> random_sample_standart(int N, Standart Func) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(Func.Xgenerate());
=======
vector<double> Standart::random_sample_standart(int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(Xgenerate());
>>>>>>> evohox
    }
    return sample;
}

// Вывод значений ф-ии плотности по выборке в файл
<<<<<<< HEAD
void result_to_file_standart(vector<double> sample, Standart Func) {
=======
void Standart::result_to_file_standart(vector<double> sample) {
>>>>>>> evohox
    ofstream out, out2;
    out.open("txts/Standart.txt");
    out2.open("txts/StandartX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
<<<<<<< HEAD
        out << Func.density(sample[i]) << endl;
=======
        out << density(sample[i]) << endl;
>>>>>>> evohox
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "File is ready\n";
<<<<<<< HEAD
}

// Реализация случайной величины r, равномерно распределенной на интервале (0, 1)
double Rgenerate() {
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_real_distribution<double> dis(0, 1);
    // return dis(gen);
    double r;
    do r = (double)rand() / RAND_MAX; while (r == 0 || r == 1);
    return r;
}

void testStandart() {
    double x = 0, u = 0, lam = 1;
    Standart Func = Standart(0, 1, 0);
    cout << "Testing a standard distribution with parameters x = 0, u = 0, lambda = 1\n";
    double d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess();
    float a = Func.asymmetry();
    assert(fabs(d - 0.5) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.333333) < 0.01);
    assert(fabs(exc - (-1.2)) < 0.01);
    assert(fabs(a - 2.77778e-05) < 0.01);
    cout << "v = 0\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    Func = Standart(6, 1, 0);
    d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess(), a = Func.asymmetry();
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - u) < 0.01);
    assert(fabs(dis - 0.0666) < 0.01);
    assert(fabs(exc - (-0.3529)) < 0.01);
    assert(fabs(a - 5.803e-17) < 0.01);
    cout << "v = 6\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
//    cout << "Testing of a shift-scale distribution with parameters x = 0, u - arbitrary, lambda = 2\n";
//    u = 3, lam = 2;
//    d = density(x, 1, u, lam), m = mathexp(u), dis = dispersion(1, lam, u), exc = excess(1), a = asymmetry(1, u, lam);
//    assert(fabs(d - 0.75) < 0.01);
//    assert(fabs(m - u) < 0.01);
//    assert(fabs(dis - 0.8) < 0.1);
//    assert(fabs(exc - (-0.85714)) < 0.01);
//    assert(fabs(a - 37.5) < 0.01);
//    cout << "v = 1, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
//    d = density(x, 4, u, lam), m = mathexp(u), dis = dispersion(4, lam, u), exc = excess(4), a = asymmetry(4, u, lam);
//    assert(fabs(d - 1.23047) < 0.01);
//    assert(fabs(m - u) < 0.01);
//    assert(fabs(dis - 0.363636) < 0.01);
//    assert(fabs(exc - (-0.461538)) < 0.01);
//    assert(fabs(a - 82.5) < 0.01);
//    cout << "v = 4, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
//    cout << "All tests are complete\n\n";
=======
>>>>>>> evohox
}