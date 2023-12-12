#include "Distributions.h"

template<class Distribution1, class Distribution2>
class Mixture : public IDistribution, public IPersistent
{
private:
    double p;
    Distribution1 *d1;
    Distribution2 *d2;
public:
    Mixture(Distribution1 *d1, Distribution2 *d2, double p0) : d1(d1), d2(d2), p(p0) {};
    // Mixture(ifstream &file) {load(file);};
    Distribution1* get_comp1();
    Distribution2* get_comp2();
    double getP() const;
    void setP(double newP);
    vector<double> generate_sample(const int n) const override;
    double density(const double x) const override;
    double expexted_value() const override;
    double varience() const override;
    double asymmetry() const override;
    double kurtosis() const override;
    double rand_num() const override;
    void save(ofstream &file) override;
    void load(ifstream &file) override;
};

template<class Distribution1, class Distribution2>
Distribution1 * Mixture<Distribution1, Distribution2>::get_comp1() {
    return d1;
}

template<class Distribution1, class Distribution2>
Distribution2 * Mixture<Distribution1, Distribution2>::get_comp2() {
    return d2;
}

template<class Distribution1, class Distribution2>
vector<double> Mixture<Distribution1, Distribution2>::generate_sample(int N) const{
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(rand_num());
    }
    return sample;
}

//Моделирование случайной величины
template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::rand_num() const {
    double r = d1->rand_num();
    double res;
    if (r > p)
        res = d1->rand_num();
    else
        res = d2->rand_num();
    return res;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::getP() const{
    return p;
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::setP(double newP){
    if(p > 1 || p < 0)
        throw 3;
    p = newP;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::density(double x) const{
    double density1 = d1->density(x);
    double density2 = d2->density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::expexted_value() const{
    double expexted_value1 = d1->expexted_value();
    double expexted_value2 = d2->expexted_value();
    double result = (1 - p) * expexted_value1 + p * expexted_value2;
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::varience() const{
    double expexted_value = Mixture<Distribution1, Distribution2>::expexted_value();
    double expexted_value1 = d1->expexted_value();
    double expexted_value2 = d2->expexted_value();
    double varience1 = d1->varience();
    double varience2 = d2->varience();
    double result = (1 - p) * (pow(expexted_value1, 2) + varience1) + p * (pow(expexted_value2, 2) + varience2) - pow(expexted_value, 2);
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::asymmetry() const{
    double expexted_value = Mixture<Distribution1, Distribution2>::expexted_value();
    double expexted_value1 = d1->expexted_value();
    double expexted_value2 = d2->expexted_value();
    double varience1 = d1->varience();
    double varience2 = d2->varience();
    double varienceMix = Mixture<Distribution1, Distribution2>::varience();
    double assymetry1 = d1->asymmetry();
    double assymetry2 = d2->asymmetry();
    double result = 1 / pow(varienceMix, 3 / 2) * (
        (1 - p) * (pow(expexted_value1 - expexted_value, 3) + 3 * (expexted_value1 - expexted_value) * varience1 + pow(varience1, 3/2)*assymetry1) +
        p * (pow(expexted_value2 - expexted_value, 3) + 3 * (expexted_value2 - expexted_value) * varience2 + pow(varience2, 3 / 2) * assymetry2)
        );
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::kurtosis() const{
    double expexted_value = Mixture<Distribution1, Distribution2>::expexted_value();
    double expexted_value1 = d1->expexted_value();
    double expexted_value2 = d2->expexted_value();
    double varience1 = d1->varience();
    double varience2 = d2->varience();
    double varienceMixx = Mixture<Distribution1, Distribution2>::varience();
    double assymetry1 = d1->asymmetry();
    double assymetry2 = d2->asymmetry();
    double exced1 = d1->kurtosis();
    double exced2 = d2->kurtosis();
    double result = 1 / pow(varienceMixx, 2) * (
        (1 - p) * (pow(expexted_value1 - expexted_value, 4) + 6 * pow(expexted_value1 - expexted_value, 2) * varience1 + 4 * (expexted_value1 - expexted_value) *
            pow(varience1, 3 / 2) * assymetry1 + pow(varience1, 2) * (exced1 + 3)) +
        p * (pow(expexted_value2 - expexted_value, 4) + 6 * pow(expexted_value2 - expexted_value, 2) * varience2 + 4 * (expexted_value2 - expexted_value) *
            pow(varience2, 3 / 2) * assymetry2 + pow(varience2, 2) * (exced2 + 3))
        ) - 3;
    return result;
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::save(ofstream &file) {
    ofstream file_d1;
    ofstream file_d2;
    string filename;
    cout << "Enter a filename for mix params: ";
    cin >> filename;
    file.open("txts/" + filename);
    file << p;
    get_comp1()->save(file_d1);
    get_comp2()->save(file_d2);
    file.close();
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::load(ifstream &file) {
    string filename;
	ifstream file1;
	ifstream file2;
    double newP = 0;

	cout << "Enter a filename with parametr p: ";
	cin >> filename;

	file.open("txts/" + filename);
	if (!file)
		throw 0;

	file >> newP;
    setP(newP);
	get_comp1()->load(file1);
	get_comp2()->load(file2);

	file.close();
}
