#include "pirsonII.hpp"

using namespace std;

int main() {
    int i = 0, j = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0;
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
            cout << "Функция плотности = " << density(x, u, v, lam) << "\n";
            cout << "Функция плотности при x=0 = " << density(0, u, v, lam) << "\n";
            cout << "Дисперсия = " << dispersion(v, lam) << "\n";
            cout << "Эксцесс = " << exces(v) << "\n";
            cout << "Математическое ожидание = " << mathexp(v, u, lam, 1) << "\n";
            cout << "Асимметрия = " << asymmetry(v, u, lam) << "\n";
            break;
        case 2:
            cout << "Введите параметр сдвига v: ";
            break;
        case 3:
            cout << "Введите параметр сдвига v: ";
            break;
        case 4:
            cout << "Введите параметр сдвига v: ";
            break;
        default:
            break;
        }
    } while(i != 0);
    return 0;
}