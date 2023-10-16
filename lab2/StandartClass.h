#include "Header.h"

// класс основного распределения
class Standart{
private:
    double u; // Параметр сдвига
    double lambda; // Параметр масштаба
    double v; // Параметр формы

    // Бета-функция по формуле из методички
    static double betafunc(double x, double y) {
        return (gamma(x) * gamma(y) / gamma(x + y));
    }

public:
    Standart(double v0=1, double lambda0=1, double u0=0) {
        v = v0, lambda = lambda0, u = u0;
    }

    Standart(string filename) {
        load(filename);
    }

    // Изменяет параметр сдвига
    void setShift(double newU);

    // Изменяет параметр масштаба
    void setScale(double newLambda);

    // Изменяет параметр формы
    void setForm(double newV);


    // Возвращает параметр сдвига
    double getShift();

    // Возвращает параметр масштаба
    double getScale();

    // Возвращает параметр формы
    double getForm();

    // Ф-ия плотности f(x, v)
    double density(double x);

    // Мат. ожидание
    double mathexp();

    // Ф-ия Дисперсии
    double dispersion();

    // Коэф. асимметрии
    double asymmetry();

    // Ф-ия эксцесса
    double excess();

    // Моделирование случайной величины
    double Xgenerate();

    // Сохранение атрибутов в файл
    void save(string filename) const;

    // Загрузить атрибуты из файла
    void load(string filename);
};