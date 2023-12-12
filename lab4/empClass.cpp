#include "empClass.h"

Empirical::Empirical(const IDistribution *d, int n0, int k0) : n(n0 > 1 ? n0 : throw 4), k(k0 > 2 ? k0 : (int)floor(log2(n0)) + 1) {
    x_s = d->generate_sample(n0);
    sort(x_s.begin(), x_s.end());
	f_s = generate_f_s();
    for(int i = 0; i < x_s.size(); i++) {
        d_s.push_back(d->density(x_s[i]));
    }
}

Empirical::Empirical(int n0, int k0)  : n(n0 > 1 ? n0: throw 4), k(k0 > 2 ? k0 : (int)floor(log2(n0)) + 1) {
    x_s = generate_sample(n0);
    sort(x_s.begin(), x_s.end());
    f_s = generate_f_s();
    sort(f_s.begin(), f_s.end());
}

Empirical::Empirical(vector<double> x_s)  : n(x_s.size()), k((int)floor(log2(x_s.size())) + 1) {
    this->x_s = x_s;
    f_s = generate_f_s();
    sort(f_s.begin(), f_s.end());
}

Empirical::Empirical(ifstream &file) {
    load(file);
    sort(x_s.begin(), x_s.end());
    sort(f_s.begin(), f_s.end());
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

vector<double> Empirical::generate_f_s() const {
    vector<double> result;
	for (const double& x: x_s)
		result.push_back(density(x));

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

// Коэффициент Стерджесса
double Empirical::delta_calc(const double min, const double max) const {
	return (max - min) / ((int)log2(n) + 1);
}

// Создание интервалов для выборки
vector<double> Empirical::create_intervals(const double delta, const double min, const double max) const {
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
int Empirical::get_interval_index(const vector<double>& intervals, const double x) const {
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
double Empirical::density(const double x) const {
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
double Empirical::expexted_value() const {
    int n = int(x_s.size());
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += x_s[i];
    }
    return sum/n;
}

// Дисперсия
double Empirical::varience() const {
    int n = int(x_s.size());
    double M = expexted_value();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 2);
    }
    return sum/n;
}

// Коэффициент асимметрии
double Empirical::asymmetry() const {
    int n = int(x_s.size());
    double M = expexted_value();
    double D = varience();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 3);
    }
    sum = sum/(n * pow(D, 1.5));
    return sum;
}

// Коэффициент эксцесса
double Empirical::kurtosis() const {
    int n = int(x_s.size());
    double M = expexted_value();
    double D = varience();
    double sum = 0;
    for (int i=0; i < n; i++) {
        sum += pow((x_s[i] - M), 4);
    }
    sum = (sum/(n * pow(D, 2 ))) - 3;
    return sum;
}

// Моделирование выборки
vector<double> Empirical::generate_sample(const int n) const {
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
double Empirical::rand_num() const {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0, 1);
    double min_x = *min_element(x_s.begin(), x_s.end());
    double max_x = *max_element(x_s.begin(), x_s.end());
    double x = min_x + (max_x - min_x) * dis(gen);
    return x;
}

void Empirical::save(ofstream &file) {
    string filename;
    cout << "Enter a filename of x_s: ";
    cin >> filename;

    file.open("txts/" + filename);
    if(!file.is_open())
        throw 0;
    for(int i = 0; i < x_s.size(); i++) file << x_s[i] << endl;
    file.close();

    cout << "Enter a filename of f_s: ";
    cin >> filename;

    file.open("txts/" + filename);
    if(!file.is_open())
        throw 0;
    for(int i = 0; i < f_s.size(); i++) { 
        file << f_s[i] << endl; 
    }
    file.close();

    cout << "Enter a filename of d_s: ";
    cin >> filename;

    file.open("txts/" + filename);
    if(!file.is_open())
        throw 0;
    for(int i = 0; i < d_s.size(); i++)  {
        file << d_s[i] << endl;
    }
    file.close();

    file.open("txts/empParams.txt");
    if(!file.is_open())
        throw 0;
    file << n << endl << k;
    file.close();
}

void Empirical::load(ifstream &file) {
    x_s.clear();
    double x;
    string filename;
    
    file.open("txts/" + filename);
    if(!file.is_open())
        throw 0;

    while(!file.eof()) {
        file >> x;
        x_s.push_back(x);
    }
    file.close();

    n = x_s.size();
    k = (int)floor(log2(n)) + 1;
    f_s = generate_f_s();
}
