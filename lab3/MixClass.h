#include "StandartClass.h"

class Mixture {
private:
    double p;
    Standart s1, s2;
public:
    Mixture();

    Mixture(Standart& d1, Standart& d2, double p0);

    Mixture(string filename);

    Standart& get_comp1();

    Standart& get_comp2();

    double getP();

    void setP(double newP);

    //Генерация выборки для смеси распределений
    vector<double> random_sample_mix(int N);

    //Вывод результата ф-ии плотности для смеси распределений в файл
    void  result_to_file_mix(vector<double> sample);

    //Функция плотости
    double densityMix(double x);

    //Математическое ожидание
    double mathexpMix();

    //Дисперсия
    double dispersionMix();
    //Асимметрия
    double asymmetryMix();

    //Эксцесс
    double excesMix();

    //Моделирование случайной величины
    double generateMix();

    // Сохранение атрибутов в файл
    void save(string filename);
    // Загрузить атрибуты из файла
    void load(string filename);
};
