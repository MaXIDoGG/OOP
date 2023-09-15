#include "pirsonII.hpp"

//v �������� ����� �� �� ��
//u �������� ������ �� �� ��
//lam �������� �������� �� �� ������

//�-�� ��������� 
double densityMix(double x, double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double density1 = density(x, v1, u1, lam1);
    double density2 = density(x, v2, u2, lam2);
    double result = (1 - p) * density1 + p * density2;
    return result;
}

//�-�� ���. ��������
double mathexpMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExp1 = mathexp(-1, 1, v1, u1, lam1);
    double mathExp2 = mathexp(-1, 1, v2, u2, lam2);
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//�-�� ���������
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(-1, 1, v1, u1, lam1);
    double mathExp2 = mathexp(-1, 1, v2, u2, lam2);
    double dispersion1 = dispersion(v1, lam1);
    double dispersion2 = dispersion(v2, lam2);
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2); 
    return result;
}

//����. ����������
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(-1, 1, v1, u1, lam1);
    double mathExp2 = mathexp(-1, 1, v2, u2, lam2);
    double dispersion1 = dispersion(v1, lam1);
    double dispersion2 = dispersion(v2, lam2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
    double result = 1 / pow(dispersionMixx, 3 / 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 3) + 3 * (mathExp1 - mathExpMix) * dispersion1 + pow(dispersion1, 3/2)*assymetry1) + 
        p * (pow(mathExp2 - mathExpMix, 3) + 3 * (mathExp2 - mathExpMix) * dispersion2 + pow(dispersion2, 3 / 2) * assymetry2)
        );
    return result;
}

//�-�� ��������
double excesMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(-1, 1, v1, u1, lam1);
    double mathExp2 = mathexp(-1, 1, v2, u2, lam2);
    double dispersion1 = dispersion(v1, lam1);
    double dispersion2 = dispersion(v2, lam2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
    double exces1 = exces(v1);
    double exces2 = exces(v2);
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) * 
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * exces1) + 
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * exces2)
        ) - 3;
    return result;
}




