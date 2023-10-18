#include "Header.h"

void testMix() {
    cout << "Testing a mixture of distributions\n";
    cout << "x = 0, p = 0.5, v1 = 0.5, u1 = 1, lambda1 = 1, v2 = 0.5, u2 = 1, lambda2 = 2\n";
    Standart Func1;
    Standart Func2;
    Func1 = Standart(0.5, 2, 1);
    Func2 = Standart(0.5, 2, 1);
    double d = densityMix(Func1, Func2, 0, 0.5);
    assert(fabs(d - 0.63662 < 0.001));
    cout << "f(x, v) = " << d << "\n";
    double m = mathexpMix(Func1, Func2, 0.5);
    assert(fabs(m - 1 < 0.001));
    cout << "M(X) = " << m << "\n";
    double dis = dispersionMix(Func1, Func2, 0.5);
    assert(fabs(dis - 1 < 0.001));
    cout << "D(X) = " << dis << "\n";
    double a = asymmetryMix(Func1, Func2, 0.5);
    double e = excesMix(Func1, Func2, 0.5);
    cout << e;
    assert(fabs(e - (-1) < 0.001));
    cout << "Y1 = " << a << "\n";
    assert(fabs(a - 0.014282 < 0.001));
    cout << "Y2 = " << e << "\n";

    cout << "All tests are complete\n" << endl;
}

void testStandart() {
    double x = 0, u = 0, lam = 1;
    Standart Func = Standart(0, 1, 0);
    cout << "Testing a standard distribution with parameters x = 0, u = 0, lambda = 1\n";
    double d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess();
    float a = Func.asymmetry();
    assert(fabs(d - 0.5) < 0.01);
    assert(fabs(m - Func.getShift()) < 0.01);
    assert(fabs(dis - 0.333333) < 0.01);
    assert(fabs(exc - (-1.2)) < 0.01);
    assert(fabs(a - 2.77778e-05) < 0.01);
    cout << "v = 0\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    Func.setForm(6); Func.setScale(1); Func.setShift(0);
    d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess(), a = Func.asymmetry();
    assert(fabs(d - 1.466) < 0.01);
    assert(fabs(m - Func.getShift()) < 0.01);
    assert(fabs(dis - 0.0666) < 0.01);
    assert(fabs(exc - (-0.3529)) < 0.01);
    assert(fabs(a - 5.803e-17) < 0.01);
    cout << "v = 6\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    cout << "Testing of a shift-scale distribution with parameters x = 0, u - arbitrary, lambda = 2\n";
    Func.setForm(1); Func.setShift(3); Func.setScale(2);
    d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess(), a = Func.asymmetry();
    assert(fabs(d - 0.75) < 0.01);
    assert(fabs(m - Func.getShift()) < 0.01);
    assert(fabs(dis - 0.8) < 0.1);
    assert(fabs(exc - (-0.85714)) < 0.01);
    assert(fabs(a - 37.5) < 0.01);
    cout << "v = 1, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n\n";
    Func.setForm(4); Func.setShift(3); Func.setScale(2);
    d = Func.density(x), m = Func.mathexp(), dis = Func.dispersion(), exc = Func.excess(), a = Func.asymmetry();
    assert(fabs(d - 1.23047) < 0.01);
    assert(fabs(m - Func.getShift()) < 0.01);
    assert(fabs(dis - 0.363636) < 0.01);
    assert(fabs(exc - (-0.461538)) < 0.01);
    assert(fabs(a - 82.5) < 0.01);
    cout << "v = 4, u = 3\nf(x,v) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY2 = " << exc << "\nY1 = " << a << "\n";
}

int empirical_test() {
    cout << "Testing the empirical distribution\n";
    vector<double> sample = {1.123, 1.123, 2.345, 2.345, 3.1, 5.1, 7.8, 9.9, 1.2};
    double d = empirical_density(5, sample);
    double m = math_expectation(sample);
    double dis = dispersion(sample);
    double y1 = asymmetry(sample);
    double y2 = EmpExcess(sample);
    assert(fabs(d - 17.316) < 0.01);
    assert(fabs(m - 3.78178) < 0.01);
    assert(fabs(dis - 8.96819) < 0.01);
    assert(fabs(y1 - 0.972817) < 0.01);
    assert(fabs(y2 - (-0.488406)) < 0.01);

    cout << "f(x) = " << d << "\nM(X) = " << m << "\nD(X) = " << dis << "\nY1 = " << y1 << "\nY2 = " << y2 << "\n";
    cout << "All tests are complete\n\n";
    return 0;
}

void testClass() {
    Standart Func;
    double d, dis, m, e, a, u = 1, v = 0.5, lam = 2;
    Func = Standart(v, lam, u);
    cout << "\nTest of Standart Constructor\nV = " << Func.getForm() << endl << "Lambda = " << Func.getScale() << endl << "U = " << Func.getShift() << endl;
    assert(fabs(Func.getForm() - 0.5) < 0.01);
    assert(fabs(Func.getShift() - 1) < 0.01);
    assert(fabs(Func.getScale() - 2) < 0.01);
    Func = Standart("txts/test1.txt");
    cout << "\nTest of Standart file constructor\nV = " <<  Func.getForm() << endl << "Lambda = " << Func.getScale() << endl << "U = " << Func.getShift() << endl;
    assert(fabs(Func.getForm() - 2) < 0.01);
    assert(fabs(Func.getShift() - 1) < 0.01);
    assert(fabs(Func.getScale() - 2) < 0.01);
    Func.setForm(3); Func.setScale(4); Func.setShift(5);
    cout << "\nTest of save/load\nName of tets file: txts/test.txt\nnew V = " << Func.getForm() << endl << "new Lambda = " << Func.getScale() << endl << "new U = " << Func.getShift() << endl;
    try{
        Func.save("txts/test2.txt");
        Func.load("txts/test2.txt");
    } catch(int error) {
        if(error == 0) cout << "Exception raised: fstream I/O error\n";
        if(error == 1) cout << "Exception raised: false scale\n";
        if(error == 2) cout << "Exception raised: false form\n";
        exit(-1);
    }
    cout << "Save and load complete\n";
    cout << "All tests are complete\n\n";
}