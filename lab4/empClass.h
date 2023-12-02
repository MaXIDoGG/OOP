#pragma once
#include "Distributions.h"

class Empirical : public IDistribution, public IPersistent
{
private:
	vector<double> x_s;
	vector<double> f_s;
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
    void result_to_file(int mod);
    double delta_calc(const double min, const double max) const;
    vector<double> create_intervals(const double delta, const double min, const double max) const;
    int get_interval_index(const vector<double>& intervals, const double x) const;
    double density(const double x) const;
    double math_expectation() const;
    double varience() const; 
    double asymmetry() const;  
    double kurtosis() const;
    vector<double> random_sample_simulation() const;
    double random_var_simulation() const;
    void save(ofstream &file);
    void load(ifstream &file);
};