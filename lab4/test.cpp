#include "empClass.h"
#include "MixClass.cpp"
#include "stdClass.h"

void testMix() {
    cout << "Testing a mixture of distributions\n";
    Standart *f1, *f2;
    Mixture<Standart, Standart> *mix1, *mix2;
    Mixture<Mixture<Standart, Standart>, Standart> *dmix;
    Mixture<Mixture<Standart, Standart>, Mixture<Standart, Standart>> *tmix;
    cout << "Testing of Constructor\n";
    try{
        f1 = new Standart(1, 1, 1);
        f2 = new Standart(2, 2, 2);
        mix1 = new Mixture(f1, f2, 0.5);
        mix2 = new Mixture(f1, f2, 0.7);
        dmix = new Mixture(mix1, f1, 0.3);
        tmix = new Mixture(mix1, mix2, 0.1);
    } catch(int error) {
        if(error == 0) cout << "Exception raised: fstream I/O error\n";
        if(error == 1) cout << "Exception raised: false scale\n";
        if(error == 2) cout << "Exception raised: false form\n";
        if(error == 3) cout << "Exception raised: false param of mix\n";
        if(error == 4) cout << "Exception raised: false param of size\n";
        if(error == 5) cout << "Exception raised: false count of interals\n";
        exit(-1);
    }
    cout << "Complete\n";
    cout << "Testing of Functions\n";
    f1 = new Standart(0.5, 2, 1);
    f2 = new Standart(0.5, 2, 1);
    mix1 = new Mixture(f1, f2, 0.5);
    double d = mix1->density(0);
    assert(fabs(d - 0.63662 < 0.001));
    double m = mix1->expexted_value();
    assert(fabs(m - 1 < 0.001));
    double dis = mix1->varience();
    assert(fabs(dis - 1 < 0.001));
    double a = mix1->asymmetry();
    double e = mix1->kurtosis();
    assert(fabs(e - (-1) < 0.001));
    assert(fabs(a - 0.014282 < 0.001));
    cout << "Complete\n";
}

void testStandart() {
    cout << "Testing a standard distribution\n";
    Standart *f1;
    cout << "Testing of Constructor\n";
    try{
        f1 = new Standart(0, 1, 0);
    } catch(int error) {
        if(error == 0) cout << "Exception raised: fstream I/O error\n";
        if(error == 1) cout << "Exception raised: false scale\n";
        if(error == 2) cout << "Exception raised: false form\n";
        if(error == 3) cout << "Exception raised: false param of mix\n";
        if(error == 4) cout << "Exception raised: false param of size\n";
        if(error == 5) cout << "Exception raised: false count of interals\n";
        exit(-1);
    }
    cout << "Complete\n";
    cout << "Testing of Functions\n";
    double d = f1->density(0), m = f1->expexted_value(), dis = f1->varience(), exc = f1->kurtosis();
    float a = f1->asymmetry();
    assert(fabs(d - 0.5) < 0.01);
    assert(fabs(m - f1->getShift()) < 0.01);
    assert(fabs(dis - 0.333333) < 0.01);
    assert(fabs(exc - (-1.2)) < 0.01);
    assert(fabs(a - 2.77778e-05) < 0.01);
    cout << "Complete\n";
}

void testEmpirical() {
    cout << "Testing the empirical distribution\n";
    cout << "Testing of Constructor\n";
    Standart *f1, *f2;
    Mixture<Standart, Standart> *mix1, *mix2;
    Mixture<Mixture<Standart, Standart>, Standart> *dmix;
    Mixture<Mixture<Standart, Standart>, Mixture<Standart, Standart>> *tmix;
    Empirical *emp;
    try {
        f1 = new Standart(1, 1, 1);
        emp = new Empirical(f1, 1000, 500);
        emp->~Empirical();
        f2 = new Standart(2, 2, 2);
        mix1 = new Mixture(f1, f2, 0.5);
        emp = new Empirical(mix1, 1000, 500);
        emp->~Empirical();
        mix2 = new Mixture(f1, f2, 0.7);
        dmix = new Mixture(mix1, f1, 0.3);
        emp = new Empirical(dmix, 1000, 500);
        emp->~Empirical();
        tmix = new Mixture(mix1, mix2, 0.1);
        emp = new Empirical(tmix, 1000, 500);
        emp->~Empirical();
    } catch(int error) {
        if(error == 0) cout << "Exception raised: fstream I/O error\n";
        if(error == 1) cout << "Exception raised: false scale\n";
        if(error == 2) cout << "Exception raised: false form\n";
        if(error == 3) cout << "Exception raised: false param of mix\n";
        if(error == 4) cout << "Exception raised: false param of size\n";
        if(error == 5) cout << "Exception raised: false count of interals\n";
        exit(-1);
    }
    cout << "Complete\n";
    cout << "Testing of Functions\n";
    vector<double> sample = {1.123, 1.123, 2.345, 2.345, 3.1, 5.1, 7.8, 9.9, 1.2};
    emp = new Empirical(sample);
    double d = emp->density(5);
    double m = emp->expexted_value();
    double dis = emp->varience();
    double y1 = emp->asymmetry();
    double y2 = emp->kurtosis();
    assert(fabs(d - 17.316) < 0.01);
    assert(fabs(m - 3.78178) < 0.01);
    assert(fabs(dis - 8.96819) < 0.01);
    assert(fabs(y1 - 0.972817) < 0.01);
    assert(fabs(y2 - (-0.488406)) < 0.01);
    cout << "Complete\n";
}
