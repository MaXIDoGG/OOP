#pragma once
#include "Distributions.h"

class Standart : public IDistribution, public IPersistent
{
private:
    double u; 
    double lambda;
    double v;

    static double betafunc(double x, double y) {
        return (gamma(x) * gamma(y) / gamma(x + y));
    }

public:
    Standart(double v0=1, double lambda0=1, double u0=0);
    Standart(ifstream &file);
    void setShift(double newU);
    void setScale(double newLambda);
    void setForm(double newV);
    double getShift() const;
    double getScale() const;
    double getForm() const;
    double density(double x) const;
    double expexted_value() const;
    double varience() const;
    double asymmetry() const;
    double kurtosis() const;
    double Rgenerate() const;
    double Xgenerate() const;
    void save(ofstream &file) const;
    void load(ifstream &file);
    vector<double> random_sample(int N) const;
    void result_to_file(vector<double> sample)const ;
};
