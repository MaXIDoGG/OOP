#include "empirical.h"
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

int absolute_frequency(const vector<double>& sample, double min, double max) //абсолютная частота
{
    int n = 0;
    for (int i = 0; i < sample.size(); i++) {
        if (sample[i] >= min && sample[i] < max) { // если попадает в промежуток
            n++;
        }
    }
    return n;
}

double empirical_density(double x, const vector<double>& sample) { // эмпирическое распределение
    int N = int(sample.size());
    double Xmin = *min_element(sample.begin(), sample.end()); // мин. элем. выборки
    double Xmax = *max_element(sample.begin(), sample.end()); // макс. элем. выборки
    double range = Xmax - Xmin; // диапазон
    int k = int(ceil((1 + 3.222*log(N)))); // формула Стерджесса
    double h = range/k; // шаг
    double X0 = Xmin - (h/2); // начало выборки
    double Xn = Xmax + (h/2); // конец выборки

    double rangeMin = X0;
    double rangeMax = Xn;

    double fx = 0;

    for (int i = 0; i < k+1; i++) {
        if (x >= rangeMin && x < rangeMax) {
            fx = absolute_frequency(sample, rangeMin, rangeMax)/N; // относительная частота
            break;
        }
        rangeMin = rangeMax;
        rangeMax += h;

    }
    return fx;
}

