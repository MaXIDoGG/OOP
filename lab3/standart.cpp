#include "Header.h"


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

// Реализация случайной величины r, равномерно распределенной на интервале (0, 1)
double Standart::Rgenerate() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    return dis(gen);
}


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
    } else throw 0;
    in.close();
}

// Генерация выборки для стандартного распределения
vector<double> Standart::random_sample_standart(int N) {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(Xgenerate());
    }
    return sample;
}

// Вывод значений ф-ии плотности по выборке в файл
void Standart::result_to_file_standart(vector<double> sample) {
    ofstream out, out2;
    out.open("txts/Standart.txt");
    out2.open("txts/StandartX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << density(sample[i]) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "File is ready\n";
}
