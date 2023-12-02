#pragma once
#include "Distributions.h"


template<class Distribution1, class Distribution2>
class Mixture : public IDistribution, public IPersistent
{
private:
    double p;
    Distribution1 *d1;
    Distribution2 *d2;
public:
    Mixture(Distribution1 *d1, Distribution2 *d2, double p0) : d1(d1), d2(d2), p(p0 > 0 && p0 < 1 ? p0 : throw 3) {};
    Mixture(ifstream &file);
    Distribution1* get_comp1();
    Distribution2* get_comp2();
    double getP() const;
    void setP(double newP);
    vector<double> random_sample(int N) const;
    void  result_to_file(vector<double> sample) const;
    double density(double x) const;
    double expexted_value() const;
    double varience() const;
    double asymmetry() const;
    double kurtosis() const;
    double generate() const;
    void save(ofstream &file) const;
    void load(ifstream &file);
};

template<class Distribution1, class Distribution2>
Mixture<Distribution1, Distribution2>::Mixture(ifstream &file) {
    load(file);
}

template<class Distribution1, class Distribution2>
Distribution1 * Mixture<Distribution1, Distribution2>::get_comp1() {
    return s1;
}

template<class Distribution1, class Distribution2>
Distribution2 * Mixture<Distribution1, Distribution2>::get_comp2() {
    return s2;
}

template<class Distribution1, class Distribution2>
vector<double> Mixture<Distribution1, Distribution2>::random_sample(int N) const{
    vector<double> sample;
    for(int i = 0; i < N; i++) {
        sample.push_back(generateMix());
    }
    return sample;
}

template<class Distribution1, class Distribution2>
void  Mixture<Distribution1, Distribution2>::result_to_file(vector<double> sample) const{
    ofstream out, out2;
    out.open("txts/Mix.txt");
    out2.open("txts/MixX.txt");
    int i = 0;
    sort(sample.begin(), sample.end());
    while(sample[i]) {
        out << densityMix(sample[i]) << endl;
        out2 << sample[i] << endl;
        i++;
    }
    out.close();
    cout << "Файл подготовлен\n";
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
    double density1 = s1.density(x);
    double density2 = s2.density(x);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::expexted_value() const{
    double expexted_value1 = s1.expexted_value();
    double expexted_value2 = s2.expexted_value();
    double result = (1 - p) * expexted_value1 + p * expexted_value2;
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::varience() const{
    double expexted_value = expexted_value();
    double expexted_value1 = s1.expexted_value();
    double expexted_value2 = s2.expexted_value();
    double varience1 = s1.varience();
    double varience2 = s2.varience();
    double result = (1 - p) * (pow(expexted_value1, 2) + varience1) + p * (pow(expexted_value2, 2) + varience2) - pow(expexted_value, 2);
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::asymmetry() const{
    double expexted_value = expexted_value();
    double expexted_value1 = s1.expexted_value();
    double expexted_value2 = s2.expexted_value();
    double varience1 = s1.varience();
    double varience2 = s2.varience();
    double varienceMixx = varienceMix();
    double assymetry1 = s1.asymmetry();
    double assymetry2 = s2.asymmetry();
    double result = 1 / pow(varienceMixx, 3 / 2) * (
        (1 - p) * (pow(expexted_value1 - expexted_value, 3) + 3 * (expexted_value1 - expexted_value) * varience1 + pow(varience1, 3/2)*assymetry1) +
        p * (pow(expexted_value2 - expexted_value, 3) + 3 * (expexted_value2 - expexted_value) * varience2 + pow(varience2, 3 / 2) * assymetry2)
        );
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::kurtosis() const{
    double expexted_value = expexted_value();
    double expexted_value1 = s1.expexted_value();
    double expexted_value2 = s2.expexted_value();
    double varience1 = s1.varience();
    double varience2 = s2.varience();
    double varienceMixx = varienceMix();
    double assymetry1 = s1.asymmetry();
    double assymetry2 = s2.asymmetry();
    double exces1 = s1.kurtosis();
    double exces2 = s2.kurtosis();
    double result = 1 / pow(varienceMixx, 2) * (
        (1 - p) * (pow(expexted_value1 - expexted_value, 4) + 6 * pow(expexted_value1 - expexted_value, 2) * varience1 + 4 * (expexted_value1 - expexted_value) *
            pow(varience1, 3 / 2) * assymetry1 + pow(varience1, 2) * (exces1 + 3)) +
        p * (pow(expexted_value2 - expexted_value, 4) + 6 * pow(expexted_value2 - expexted_value, 2) * varience2 + 4 * (expexted_value2 - expexted_value) *
            pow(varience2, 3 / 2) * assymetry2 + pow(varience2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

template<class Distribution1, class Distribution2>
double Mixture<Distribution1, Distribution2>::generate() const{
    double r = s1.Rgenerate();
    double res;
    if (r > p)
        res = s1.Xgenerate();
    else
        res = s2.Xgenerate();
    return res;
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::save(ofstream &file) const{
    //Переделать
}

template<class Distribution1, class Distribution2>
void Mixture<Distribution1, Distribution2>::load(ifstream &file) {
    //Переделать
}
