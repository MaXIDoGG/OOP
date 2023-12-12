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
    double density(const double x) const override;
    double expexted_value() const override;
    double varience() const override;
    double asymmetry() const override;
    double kurtosis() const override;
    double Rgenerate() const;
    double rand_num() const override;
    void save(ofstream &file) override;
    void load(ifstream &file) override;
    vector<double> generate_sample(const int n) const override;
};
