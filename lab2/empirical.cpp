#include "Header.h"

using namespace std;

//ВЫвод результата ф-ии плотности эмпирического распределения в файл
void result_to_file_empirical(vector<double> sample, int mod) {
    ofstream out;
    ofstream out2;
    if(mod == 0) {
        out.open("txts/EmpiricalStd.txt");
        out2.open("txts/EmpiricalStdX.txt");
    }
    else if(mod == 1) {
        out.open("txts/EmpiricalMIX.txt");
        out2.open("txts/EmpiricalMIXX.txt");
    }
    else if(mod == 2) {
        out.open("txts/EmpEmpirical.txt");
        out2.open("txts/EmpEmpiricalX.txt");
    }
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << empirical_density(sample[i], sample) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

// Коэффициент Стерджесса
double delta_calc(const double n, const double min, const double max) {
	return (max - min) / ((int)log2(n) + 1);
}

// Создание интервалов для выборки
vector<double> create_intervals(const double delta, const double min, const double max) {
	vector<double> intervals;
	double slider = min;
	intervals.push_back(slider);
	while (slider < max) {
		intervals.push_back(slider + delta);
		slider += delta;
	}
	return intervals;
}

// Получение индекса интервала
int get_interval_index(const vector<double>& intervals, const double x) {
	if (intervals.size() < 2) {
		return 0;
	}
	if (x >= intervals[intervals.size() - 2] && x <= intervals[intervals.size() - 1]) {
		return intervals.size() - 2;
	}
	for (int i = 0; i < intervals.size() - 1; ++i) {
		if (x >= intervals[i] && x < intervals[i + 1]) {
			return i;
		}
	}
    return 0;
}

// Эмпирическая плотность
double empirical_density(const double x, const vector<double>& sample) {
	double delta = delta_calc(sample.size(), sample[0], sample[sample.size() - 1]);
	auto intervals = create_intervals(delta, sample[0], sample[sample.size() - 1]);
	int indx = get_interval_index(intervals, x);
	int left = 0;
	int right = sample.size() - 1;
	if (indx == 0) {
		right = 0;
		while (sample[right] < intervals[1]) {
			++right;
		}
	}
	else if (indx == intervals.size() - 2) {
		left = sample.size() - 1;
		while (sample[left] > intervals[intervals.size() - 2]) {
			--left;
		}
	}
	else {
		while (sample[left] < intervals[indx]) {
			++left;
		}
		right = left;
		while (sample[right] < intervals[indx + 1]) {
			++right;
		}
	}
	return (right - left + 1) / (sample.size() * delta);
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
double EmpExcess(const vector<double>& sample) {
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

int empirical_test() {
    cout << "Testing the empirical distribution\n";
    vector<double> sample = {1.123, 1.123, 2.345, 2.345, 3.1, 5.1, 7.8, 9.9, 1.2};
    double d = empirical_density(5, sample);
    double m = math_expectation(sample);
    double dis = dispersion(sample);
    double y1 = asymmetry(sample);
    double y2 = EmpExcess(sample);
    assert(fabs(d - 17.316) < 0.01);
    assert(fabs(m - 3.78178) < 0.01);
    assert(fabs(dis - 8.96819) < 0.01);
    assert(fabs(y1 - 0.972817) < 0.01);
    assert(fabs(y2 - (-0.488406)) < 0.01);

    cout << "f(x) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY1 = " << y1 << "\nY2 = " << y2 << "\n";
    cout << "All tests are complete\n\n";
    return 0;
}