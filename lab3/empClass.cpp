#include "empClass.h"

Empirical::Empirical(Standart &std, int n0, int k0)  : n(n0 > 1 ? n0: throw 4), k(k0 > 2 ? k0 : (int)floor(log2(n0)) + 1) {
    x_s = std.random_sample_standart(n0);
    f_s = generate_f_s();
}

Empirical::Empirical(Mixture &mix, int n0, int k0)  : n(n0 > 1 ? n0: throw 4), k(k0 > 2 ? k0 : (int)floor(log2(n0)) + 1) {
    x_s = mix.random_sample_mix(n0);
    f_s = generate_f_s();
}

Empirical::Empirical(Empirical& emp)  : n(emp.n > 1 ? emp.n: throw 4), k(emp.k > 2 ? emp.k : (int)floor(log2(emp.n)) + 1), x_s(emp.x_s), f_s(emp.f_s) {
    f_s = generate_f_s();
}

Empirical::Empirical(int n0, int k0)  : n(n0 > 1 ? n0: throw 4), k(k0 > 2 ? k0 : (int)floor(log2(n0)) + 1) {
    x_s = random_sample_simulation();
    f_s = generate_f_s();
}

Empirical::Empirical(vector<double> x_s)  : n(x_s.size()), k((int)floor(log2(x_s.size())) + 1) {
    this->x_s = x_s;
    f_s = generate_f_s();
}

Empirical::~Empirical() {
    x_s.clear();
    f_s.clear();
}

Empirical& Empirical::operator=(const Empirical& emp)
{
	if (this == &emp)
		return *this;

	x_s = emp.x_s;
	f_s = emp.f_s;
	n = emp.n;
	k = emp.k;
	return *this;
}

vector<double> Empirical::generate_f_s() {
    vector<double> result;

	for (const double& x: x_s)
		result.push_back(empirical_density(x));

	return result;
}

void Empirical::set_n(int newN) {
    n = newN > 1 ? newN : throw 4;
}

void Empirical::set_k(int newK) {
    k = newK > 2 ? newK : (int)floor(log2(n)) + 1;
}

int Empirical::get_n() {
    return n;
}

int Empirical::get_k() {
    return k;
}

vector<double> Empirical::get_x_s() {
    return x_s;
}

vector<double> Empirical::get_f_s() {
    return f_s;
}

//ВЫвод результата ф-ии плотности эмпирического распределения в файл
void Empirical::result_to_file_empirical(int mod) {
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
    sort(x_s.begin(), x_s.end());
    while(x_s[i]) {
        out << empirical_density(x_s[i]) << endl;
        out2 << x_s[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
}

// Коэффициент Стерджесса
double Empirical::delta_calc(const double min, const double max) {
	return (max - min) / ((int)log2(n) + 1);
}

// Создание интервалов для выборки
vector<double> Empirical::create_intervals(const double delta, const double min, const double max) {
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
int Empirical::get_interval_index(const vector<double>& intervals, const double x) {
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
double Empirical::empirical_density(const double x) {
	double delta = delta_calc(x_s[0], x_s[x_s.size() - 1]);
	auto intervals = create_intervals(delta, x_s[0], x_s[x_s.size() - 1]);
	int indx = get_interval_index(intervals, x);
	int left = 0;
	int right = x_s.size() - 1;
	if (indx == 0) {
		right = 0;
		while (x_s[right] < intervals[1]) {
			++right;
		}
	}
	else if (indx == intervals.size() - 2) {
		left = x_s.size() - 1;
		while (x_s[left] > intervals[intervals.size() - 2]) {
			--left;
		}
	}
	else {
		while (x_s[left] < intervals[indx]) {
			++left;
		}
		right = left;
		while (x_s[right] < intervals[indx + 1]) {
			++right;
		}
	}
	return (right - left + 1) / (x_s.size() * delta);
}

// Мат. ожидание
double Empirical::math_expectation() {
    int n = int(x_s.size());
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += x_s[i];
    }
    return sum/n;
}

// Дисперсия
double Empirical::dispersion() {
    int n = int(x_s.size());
    double M = math_expectation();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 2);
    }
    return sum/n;
}

// Коэффициент асимметрии
double Empirical::asymmetry() {
    int n = int(x_s.size());
    double M = math_expectation();
    double D = dispersion();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 3);
    }
    sum = sum/(n * pow(D, 1.5));
    return sum;
}

// Коэффициент эксцесса
double Empirical::EmpExcess() {
    int n = int(x_s.size());
    double M = math_expectation();
    double D = dispersion();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 4);
    }
    sum = (sum/(n * pow(D, 2 ))) - 3;
    return sum;
}

// Моделирование выборки
vector<double> Empirical::random_sample_simulation() {
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
double Empirical::random_var_simulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);

    double min_x = *min_element(x_s.begin(), x_s.end());
    double max_x = *max_element(x_s.begin(), x_s.end());
    double x = min_x + (max_x - min_x) * dis(gen);
    return x;
}

void Empirical::save(string filename) {
    ofstream out;
    out.open(filename);
    if (out.is_open())
    {
        out << n << "\n";
        out << k << "\n";
    } else throw 0;
    out.close();
}

void Empirical::load(string filename) {
    ifstream in;
    int newN = 0, newK = 0;
    in.open(filename);
    if (in.is_open())
    {
        in >> newN;
        set_k(newN);
        in >> newK;
        set_n(newK);
    } else throw 0;
    in.close();
}
