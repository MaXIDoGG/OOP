<<<<<<< HEAD
#include "Header.h"

// класс основного распределения
class Standart{
private:
    double u; // Параметр сдвига
    double lambda; // Параметр масштаба
    double v; // Параметр формы

    // Бета-функция по формуле из методички
=======
#include <iostream>
#include <random>
#include <math.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>
#include "spec_func.hpp"

using namespace std;

// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
class Standart{
private:
    double u; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
    double lambda; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double v; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ

    // пїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
>>>>>>> evohox
    static double betafunc(double x, double y) {
        return (gamma(x) * gamma(y) / gamma(x + y));
    }

public:
    Standart(double v0=1, double lambda0=1, double u0=0) {
<<<<<<< HEAD
        v = v0, lambda = lambda0, u = u0;
=======
        setForm(v0); setScale(lambda0); setShift(u0);
>>>>>>> evohox
    }

    Standart(string filename) {
        load(filename);
    }

<<<<<<< HEAD
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
=======
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
    void setShift(double newU);

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    void setScale(double newLambda);

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    void setForm(double newV);

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
    double getShift();

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double getScale();

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    double getForm();

    // пїЅ-пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ f(x, v)
    double density(double x);

    // пїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double mathexp();

    // пїЅ-пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double dispersion();

    // пїЅпїЅпїЅпїЅ. пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double asymmetry();

    // пїЅ-пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double excess();

    // Р РµР°Р»РёР·Р°С†РёСЏ СЃР»СѓС‡Р°Р№РЅРѕР№ РІРµР»РёС‡РёРЅС‹ r, СЂР°РІРЅРѕРјРµСЂРЅРѕ СЂР°СЃРїСЂРµРґРµР»РµРЅРЅРѕР№ РЅР° РёРЅС‚РµСЂРІР°Р»Рµ (0, 1)
    double Rgenerate();

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    double Xgenerate();

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ
    void save(string filename) const;

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    void load(string filename);

    // Р“РµРЅРµСЂР°С†РёСЏ РІС‹Р±РѕСЂРєРё РґР»СЏ СЃС‚Р°РЅРґР°СЂС‚РЅРѕРіРѕ СЂР°СЃРїСЂРµРґРµР»РµРЅРёСЏ
    vector<double> random_sample_standart(int N);

    // Р’С‹РІРѕРґ Р·РЅР°С‡РµРЅРёР№ С„-РёРё РїР»РѕС‚РЅРѕСЃС‚Рё РїРѕ РІС‹Р±РѕСЂРєРµ РІ С„Р°Р№Р»
    void result_to_file_standart(vector<double> sample); 
>>>>>>> evohox
};