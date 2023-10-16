#include <iostream>
#include <random>
#include "vector"
#include <math.h>
#include <cassert>
#include <algorithm>
#include <vector>
#include <fstream>
#include <time.h>
#include "spec_func.hpp"

using namespace std;

// ����� ��������� �������������
class Standart{
private:
    double u; // �������� ������
    double lambda; // �������� ��������
    double v; // �������� �����

    // ����-������� �� ������� �� ���������
    static double betafunc(double x, double y) {
        return (gamma(x) * gamma(y) / gamma(x + y));
    }

public:
    Standart(double v0=1, double lambda0=1, double u0=0) {
        setForm(v0); setScale(lambda0); setShift(u0);
    }

    Standart(string filename) {
        load(filename);
    }

    // �������� �������� ������
    void setShift(double newU);

    // �������� �������� ��������
    void setScale(double newLambda);

    // �������� �������� �����
    void setForm(double newV);


    // ���������� �������� ������
    double getShift();

    // ���������� �������� ��������
    double getScale();

    // ���������� �������� �����
    double getForm();

    // �-�� ��������� f(x, v)
    double density(double x);

    // ���. ��������
    double mathexp();

    // �-�� ���������
    double dispersion();

    // ����. ����������
    double asymmetry();

    // �-�� ��������
    double excess();

    // ������������� ��������� ��������
    double Xgenerate();

    // ���������� ��������� � ����
    void save(string filename) const;

    // ��������� �������� �� �����
    void load(string filename);
};