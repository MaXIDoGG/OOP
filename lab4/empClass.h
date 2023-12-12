#pragma once
#include "Distributions.h"

class Empirical : public IDistribution, public IPersistent
{
private:
	vector<double> x_s;
	vector<double> f_s;
    vector<double> d_s;
	int n = 0;
	int k = 0;
public:
    Empirical(const IDistribution *d, int n0, int k0);
    Empirical(int n0 = 2, int k0 = 3);
    Empirical(vector<double> x_s);
    Empirical(ifstream &file);
    ~Empirical();
    void set_n(int newN);
    void set_k(int newK);
    int get_n();
    int get_k();
    vector<double> get_x_s();
    vector<double> get_f_s();
    Empirical& operator=(const Empirical& emp);
    vector<double> generate_f_s() const;
    vector<double> generate_d_s() const;
    double delta_calc(const double min, const double max) const;
    vector<double> create_intervals(const double delta, const double min, const double max) const;
    int get_interval_index(const vector<double>& intervals, const double x) const;
    double density(const double x) const override;
    double expexted_value() const override;
    double varience() const override; 
    double asymmetry() const override;  
    double kurtosis() const override;
    vector<double> generate_sample(const int n) const override;
    double rand_num() const override;
    void save(ofstream &file) override;
    void load(ifstream &file) override;
};