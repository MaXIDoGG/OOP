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
    vector<double> random_sample_mix(Standart Func, int N);

    //Вывод результата ф-ии плотности для смеси распределений в файл
    void  result_to_file_mix(Standart Func1, Standart Func2, vector<double> sample);

    //Функция плотости
    double densityMix(Standart Func1, Standart Func2, double x);

    //Математическое ожидание
    double mathexpMix(Standart Func1, Standart Func2);

    //Дисперсия
    double dispersionMix(Standart Func1, Standart Func2);
    //Асимметрия
    double asymmetryMix(Standart Func1, Standart Func2);

    //Эксцесс
    double excesMix(Standart Func1, Standart Func2);

    //Моделирование случайной величины
    double generateMix(Standart Func);

    // Сохранение атрибутов в файл
    void save(string filename);
    // Загрузить атрибуты из файла
    void load(string filename);
};
