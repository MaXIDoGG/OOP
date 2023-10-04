#include "pirsonII.hpp"
#include "mix.hpp"
#include "empirical.hpp"

int main() {
    setlocale(LC_ALL, "Ru");
    int i = 0, j = 0, n = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    vector<double> sample, sample2;
    vector<vector<double> > samplemix;
    string filename;
    do {
        cout << "1: Распределение Пирсона типа II(R-распределение)\n2: Распеределение в виде смеси двух распределений\n3: Запуск тестов\n4: Подготовить файлы с результатами\n0: Выход\n";
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
            cout << "Введите размер выборки: ";
            cin >> n;
            sample = random_sample_standart(n, v);
            cout << "Функция плотности в случайной точке = " << density(x, v, u, lam) << "\n";
            cout << "Функция плотности при x=0 = " << density(0, v, u, lam) << "\n";
            cout << "Дисперсия = " << dispersion(v, lam, u) << "\n";
            cout << "Эксцесс = " << excess(v) << "\n";
            cout << "Математическое ожидание = " << mathexp(v, u, lam, 1) << "\n";
            cout << "Асимметрия = " << asymmetry(v, u, lam) << "\n";
            cout << "==Эмпирические характеристики==\n";
            cout << "Функция плотности при x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Дисперсия = " << dispersion(sample) << "\n";
            cout << "Эксцесс = " << EmpExcess(sample) << "\n";
            cout << "Математическое ожидание = " << math_expectation(sample) << "\n";
            cout << "Асимметрия = " << asymmetry(sample) << "\n";
            sample.clear();
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
            cout << "Введите размер выборки: ";
            cin >> n;
            cout << "Функция плотноcти в случайной точке = " << densityMix(samplemix[0][0], p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Функция плотности при x=0 = " << densityMix(0, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Дисперсия = " << dispersionMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Эксцесс = " << excesMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Математическое ожидание = " << mathexpMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Асимметрия = " << asymmetryMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "==Эмпирические характеристики==\n";
            cout << "Функция плотности при x=0 = " << empirical_density(0, sample2) << "\n";
            cout << "Дисперсия = " << dispersion(sample2) << "\n";
            cout << "Эксцесс = " << EmpExcess(sample2) << "\n";
            cout << "Математическое ожидание = " << math_expectation(sample2) << "\n";
            cout << "Асимметрия = " << asymmetry(sample2) << "\n";
            sample2.clear(); samplemix.clear();
            break;
        case 3:
            testStandart();
            testMix();
            empirical_test();
            break;
        case 4:
            cout << "Введите параметр формы v1: ";
            cin >> v;
            cout << "Введите параметр формы v2: ";
            cin >> v2;
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
            cout << "Введите размер выборки: ";
            cin >> n;
            sample = random_sample_standart(n, v);
            result_to_file_standart(sample, v, u, lam);
            result_to_file_empirical(sample, 0);
            break;
        default:
            cout << "Повторите попытку\n";
            break;
        }
    } while(i != 0);
    return 0;
}
