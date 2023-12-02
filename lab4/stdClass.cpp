#include "stdClass.h"

// -- Реализация класса Standart --

Standart::Standart(double v0=1, double lambda0=1, double u0=0) {
    setForm(v0); setScale(lambda0); setShift(u0);
}
Standart::Standart(ifstream &file) {
    load(file);
}

double Standart::density(double x) const {
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
double Standart::getShift() const {
    return u;
}
// Возвращает параметр масштаба
double Standart::getScale() const {
    return lambda;
}
// Возвращает параметр формы
double Standart::getForm() const {
    return v;
}

// Мат. ожидание
double Standart::expexted_value() const {
    if (u != 0) return u;
    return 0;
}
// Ф-ия Дисперсии
double Standart::varience() const {
    double result = 0;
    result = (1 / (2 * v + 3));
    if (lambda != 1 || u != 0) result *= lambda * lambda;
    return result;
}
// Коэф. асимметрии
double Standart::asymmetry() const {
    double result = 0;
    result = expexted_value() - 3 * expexted_value() * expexted_value() + 2 * pow(expexted_value(), 3);
    result /= pow(varience(), 3 / 2);
    return result;
}
// Ф-ия эксцесса
double Standart::kurtosis() const {
    return (-6 / (2 * v + 5));
}

// Реализация случайной величины r, равномерно распределенной на интервале (0, 1)
double Standart::Rgenerate() const {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    return dis(gen);
}


// Моделирование случайной величины
double Standart::Xgenerate() const {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    if(dis(gen) >= 0.5)
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * sin(2 * M_PI * Rgenerate()));
    else
        return (pow(1 - pow(Rgenerate(), 1 / (v + 0.5)), 0.5) * cos(2 * M_PI * Rgenerate()));
}

// Сохранение атрибутов в файл
void Standart::save(ofstream &file) const {
    //переделать
}
// Загрузить атрибуты из файла
void Standart::load(ifstream &file) {
    //переделать
}

// Генерация выборки для стандартного распределения
vector<double> Standart::random_sample(int N) const {
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(Xgenerate());
    }
    return sample;
}

// Вывод значений ф-ии плотности по выборке в файл
void Standart::result_to_file(vector<double> sample) const {
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
