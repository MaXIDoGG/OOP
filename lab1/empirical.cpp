#include "empirical.h"
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <fstream>
using namespace std;

// ������᪠� ���⭮���
double empirical_density(double x, const vector<double>& sample) {
    int n = sample.size();
    int k = static_cast<int>(ceil(1 + 3.222 * log(n)));
    double min_x = *min_element(sample.begin(), sample.end());
    double max_x = *max_element(sample.begin(), sample.end());
    double range = max_x - min_x;
    double h = range / k;
    vector<int> counts(k, 0);

    for (double xi : sample) {
        if (xi >= min_x && xi <= max_x) {
            int group = static_cast<int>((xi - min_x) / h);
            counts[group]++;
        }
    }

    int count = 0;
    for (int i = 0; i < k; i++) {
        if (min_x + (i + 1) * h <= x) {
            count += counts[i];
        }
    }

    double density = static_cast<double>(count) / (n * h);
    return density;
}


// ���. ��������
double math_expectation(const vector<double>& sample) {
    int n = int(sample.size());
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += sample[i];
    }
    return sum/n;
}

// ��ᯥ���
double dispersion(const vector<double>& sample) {
    int n = int(sample.size());
    double M = math_expectation(sample);
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((sample[i] - M), 2);
    }
    return sum/n;
}

// �����樥�� �ᨬ���ਨ
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

// �����樥�� ������
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

// ������஢���� �롮ન
vector<double> random_sample_simulation(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);

    vector<double> sample;
    for (int i = 0; i < n; ++i) {
        sample.push_back(dis(gen));
    }
    return sample;
}

// ������஢���� ��砩��� ����稭�
double random_var_simulation(const vector<double>& sample) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);

    double min_x = *min_element(sample.begin(), sample.end());
    double max_x = *max_element(sample.begin(), sample.end());
    double x = min_x + (max_x - min_x) * dis(gen);
    return x;
}

// ������᪠� ���⭮��� � �롮મ� �� 䠩��
double empirical_density_file(const string& filename, double x) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "The file could not be opened." << endl;
        return 1;
    }

    vector<double> sample;
    double number;
    while (inputFile >> number) {
        sample.push_back(number);
    }
    inputFile.close();
    double density = empirical_density(x, sample);
    return density;
}


int empirical_test() {
    cout << "����஢���� ������᪮�� ��।������\n";
    vector<double> sample = {1.123, 1.123, 2.345, 2.345, 3.1, 5.1, 7.8, 9.9, 1.2};
    double d = empirical_density(5, sample);
    double m = math_expectation(sample);
    double dis = dispersion(sample);
    double y1 = asymmetry(sample);
    double y2 = excess(sample);
    assert(fabs(d - 0.683605) < 0.01);
    assert(fabs(m - 3.78178) < 0.01);
    assert(fabs(dis - 8.96819) < 0.01);
    assert(fabs(y1 - 0.972817) < 0.01);
    assert(fabs(y2 - (-0.488406)) < 0.01);

    cout << "f(x) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << y2 << "\nY1 = " << y1 << "\n";
    cout << "All tests are completed";
    return 0;
}