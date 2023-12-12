#pragma once
#define interface struct
#include "Header.h"

interface IDistribution
{
public:
    double virtual density(const double x) const = 0;
    double virtual expexted_value() const = 0;
    double virtual varience() const = 0;
    double virtual asymmetry() const = 0;
    double virtual kurtosis() const = 0;
    double virtual rand_num() const = 0;
    vector<double> virtual generate_sample(const int n) const = 0;
};

interface IPersistent {
public:
    void virtual load(ifstream &file) = 0;
    void virtual save(ofstream &file) = 0;
};