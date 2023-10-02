#include "pirsonII.hpp"
#include "mix.hpp"
#include "empirical.h"

int main() {
    int i = 0, j = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    do {
        cout << "1: Распределение Пирсона типа II(R-распределение)\n2: Распеределение в виде смеси двух распределений\n3: Эмпирическое распределение\n4: Запуск тестов\n0: Выход\n";
        cin >> i;
        switch (i)
        {
        case 1:
            cout << "Введите параметр формы v: ";
            cin >> v;
            x = Xgenerate(v);
            cout << "Введите параметр сдвига u: ";
            cin >> u;
            cout << "Введите параметр масштаба lambda: ";
            cin >> lam;
            cout << "Функция плотности = " << density(x, v, u, lam) << "\n";
            cout << "Функция плотности при x=0 = " << density(0, v, u, lam) << "\n";
            cout << "Дисперсия = " << dispersion(v, lam, u) << "\n";
            cout << "Эксцесс = " << excess(v) << "\n";
            cout << "Математическое ожидание = " << mathexp(v, u, lam, 1) << "\n";
            cout << "Асимметрия = " << asymmetry(v, u, lam) << "\n";
            break;
        case 2:
            cout << "Введите параметр формы v1: ";
            cin >> v;
            cout << "Введите параметр формы v2: ";
            cin >> v;
            cout << "Введите параметр сдвига u1: ";
            cin >> u;
            cout << "Введите параметр сдвига u2: ";
            cin >> u2;
            cout << "Введите параметр масштаба lambda1: ";
            cin >> lam;
            cout << "Введите параметр масштаба lambda2: ";
            cin >> lam2;
            cout << "Введите параметр смеси p: ";
            cin >> p;
            x = generateMix(p, v, u, lam, v2, u2, lam2);
            cout << "Функция плотности = " << densityMix(x, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Функция плотности при x=0 = " << densityMix(0, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Дисперсия = " << dispersionMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Эксцесс = " << excesMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Математическое ожидание = " << mathexpMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Асимметрия = " << asymmetryMix(p, v, u, lam, v2, u2, lam2) << "\n";
            break;
        case 3:
            cout << "Введите параметр сдвига v: ";
            break;
        case 4:
            testStandart();
            testMix();
            empirical_test();
            break;
        default:
            break;
        }
    } while(i != 0);
    return 0;
}