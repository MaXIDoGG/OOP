#include "empirical.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

// Эмпирическое распределение
double empirical_density(double x, const vector<double>& sample) {
    int n = sample.size();
    int k = int(ceil((1 + 3.222*log(n)))); // формула Стерджесса
    double min_x = *min_element(sample.begin(), sample.end());
    double max_x = *max_element(sample.begin(), sample.end());
    double range = max_x - min_x;
    double h = range / k;
    vector<int> counts(k, 0);
    for (double xi : sample) {
        if (xi >= min_x && xi <= max_x) {
            int group = (xi - min_x) / h;
            counts[group]++;
        }
    }
    int count = 0;
    for (int i = 0; i < k; i++) {
        if (min_x + (i + 1) * h <= x) {
            count += counts[i];
        }
    }
    return static_cast<double>(count) / n;
}


// Мат. ожидание
double math_expectation(const vector<double>& sample) {
    int n = int(sample.size());
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += sample[i];
    }
    return sum/n;
}

// Дисперсия
double dispersion(const vector<double>& sample) {
    int n = int(sample.size());
    double M = math_expectation(sample);
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((sample[i] - M), 2);
    }
    return sum/n;
}

// Коэффициент асимметрии
double asymmetry(const vector<double>& sample) {
    int n = int(sample.size());
    double M = math_expectation(sample);
    double D = dispersion(sample);
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((sample[i] - M), 3);
    }
    sum = sum/(n * pow(D, 1.5));
    return sum;
}

// Коэффициент эксцесса
double excess(const vector<double>& sample) {
    int n = int(sample.size());
    double M = math_expectation(sample);
    double D = dispersion(sample);
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((sample[i] - M), 4);
    }
    sum = (sum/(n * pow(D, 2 ))) - 3;
    return sum;
}

// Моделирование выборки
vector<double> random_sample_simulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);

    // Создание выборки
    vector<double> sample;
    for (int i = 0; i < 1000; ++i) {
        sample.push_back(dis(gen));
    }
    return sample;
}

// Моделирование случайной величины
double random_var_simulation(const vector<double>& sample) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);

    double min_x = *min_element(sample.begin(), sample.end());
    double max_x = *max_element(sample.begin(), sample.end());
    double x = min_x + (max_x - min_x) * dis(gen);
    return x;
}

