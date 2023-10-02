#include "pirsonII.hpp"
#include "mix.hpp"

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
    double mathExp1 = mathexp(v1, u1, lam1, 1);
    double mathExp2 = mathexp(v2, u2, lam2, 1);
    double result = (1 - p) * mathExp1 + p * mathExp2;
    return result;
}

//�-�� ���������
double dispersionMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(v1, u1, lam1, 1);
    double mathExp2 = mathexp(v2, u2, lam2, 1);
    double dispersion1 = dispersion(v1, lam1);
    double dispersion2 = dispersion(v2, lam2);
    double result = (1 - p) * (pow(mathExp1, 2) + dispersion1) + p * (pow(mathExp2, 2) + dispersion2) - pow(mathExpMix, 2); 
    return result;
}

//����. ����������
double asymmetryMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double mathExpMix = mathexpMix(p, v1, u1, lam1, v2, u2, lam2);
    double mathExp1 = mathexp(v1, u1, lam1, 1);
    double mathExp2 = mathexp(v2, u2, lam2, 1);
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
    double mathExp1 = mathexp(v1, u1, lam1, 1);
    double mathExp2 = mathexp(v2, u2, lam2, 1);
    double dispersion1 = dispersion(v1, lam1);
    double dispersion2 = dispersion(v2, lam2);
    double dispersionMixx = dispersionMix(p, v1, u1, lam1, v2, u2, lam2);
    double assymetry1 = asymmetry(v1, u1, lam1);
    double assymetry2 = asymmetry(v2, u2, lam2);
    double exces1 = exces(v1);
    double exces2 = exces(v2);
    double result = 1 / pow(dispersionMixx, 2) * (
        (1 - p) * (pow(mathExp1 - mathExpMix, 4) + 6 * pow(mathExp1 - mathExpMix, 2) * dispersion1 + 4 * (mathExp1 - mathExpMix) * 
            pow(dispersion1, 3 / 2) * assymetry1 + pow(dispersion1, 2) * (exces1 + 3)) + 
        p * (pow(mathExp2 - mathExpMix, 4) + 6 * pow(mathExp2 - mathExpMix, 2) * dispersion2 + 4 * (mathExp2 - mathExpMix) *
            pow(dispersion2, 3 / 2) * assymetry2 + pow(dispersion2, 2) * (exces2 + 3))
        ) - 3;
    return result;
}

//������������� ��������� ��������
double generateMix(double p, double v1, double u1, double lam1, double v2, double u2, double lam2) {
    double r = Rgenerate();
    if (r > p) return Xgenerate(v1);
    else return Xgenerate(v2);
}

void testMix() {
    cout << "x = 0, p = 0.5, v1 = 0.5, u1 = 1, lambda1 = 1, v2 = 0.5, u2 = 1, lambda2 = 2\n";
    double d = (densityMix(0, 0.5, 0.5, 1, 2, 0.5, 1, 2) - 0.275668);
    assert(fabs(d < 0.001));
    cout << "Функция плотности = " << d << "\n";
    double m = (mathexpMix(0.5, 0.5, 1, 2, 0.5, 1, 2) - 0.075588);
    assert(fabs(m < 0.001));
    cout << "Математическое ожидание = " << m << "\n";
    double dis = (dispersionMix(0.5, 0.5, 1, 2, 0.5, 1, 2) - 1);
    assert(fabs(dis < 0.001));
    cout << "Дисперсия = " << dis << "\n";
    double a = (asymmetryMix(0.5, 0.5, 1, 2, 0.5, 1, 2) - 0.014282);
    assert(fabs(a < 0.001));
    cout << "Асимметрия = " << a << "\n";
    double e = excesMix(0.5, 0.5, 1, 2, 0.5, 1, 2) - (-1);
    assert(fabs(e < 0.001));
    cout << "Эксцесс = " << e << "\n";

    cout << "All tests done" << endl;
}


