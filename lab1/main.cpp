#include "Header.h"

int main() {
    int j = 0, n = 0, check;
    char i = '0';
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    vector<double> sample, sample2;
    do {
        cout << "1: Распределение Пирсона типа II(R-распределение)\n2: Распеределение в виде смеси двух распределений\n3: Запуск тестов\n4: Подготовить файлы с результатами\nq: Выход\n";
        cin >> i;
        cin.clear();
        cin.ignore(100000, '\n');
        switch (i)
        {
        case '1':
            while(check != 1) {
                check = 0;
                cout << "Введите параметр формы v: ";
                cin >> v;
                if(v >= 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            } check = 0;
                x = Xgenerate(v);
                cout << "Введите параметр сдвига u: ";
                cin >> u;
                if(v < 0) check++;
                cin.clear();
                cin.ignore(100000, '\n');
                cout << "Введите параметр масштаба lambda: ";
                cin >> lam;
                cin.clear();
                cin.ignore(100000, '\n');
            while(check != 1) {
                cout << "Введите размер выборки: ";
                cin >> n;
                if (n > 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
            } check = 0;
            sample = random_sample_standart(n, v);
            cout << "Функция плотности в случайной точке = " << density(x, v, u, lam) << "\n";
            cout << "Функция плотности при x=0 = " << density(0, v, u, lam) << "\n";
            cout << "Дисперсия = " << dispersion(v, lam, u) << "\n";
            cout << "Эксцесс = " << excess(v) << "\n";
            cout << "Математическое ожидание = " << mathexp(u) << "\n";
            cout << "Асимметрия = " << asymmetry(v, u, lam) << "\n";
            cout << "\n==Эмпирические характеристики==\n";
            cout << "Функция плотности при x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Дисперсия = " << dispersion(sample) << "\n";
            cout << "Эксцесс = " << EmpExcess(sample) << "\n";
            cout << "Математическое ожидание = " << math_expectation(sample) << "\n";
            cout << "Асимметрия = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case '2':
            while(check != 1) {
                check = 0;
                cout << "Enter form parameter v1: ";
                cin >> v;
                if(v >= 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
            } check = 0;
            while(check != 1) {
                check = 0;
                cout << "Enter form parameter v2: ";
                cin >> v2;
                if(v2 >= 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
            } check = 0;
            cout << "Введите параметр сдвига u1: ";
            cin >> u;
            cin.clear();
            cout << "Введите параметр сдвига u2: ";
            cin >> u2;
            cin.clear();
            cout << "Введите параметр масштаба lambda1: ";
            cin >> lam;
            cin.clear();
            cout << "Введите параметр масштаба lambda2: ";
            cin >> lam2;
            cin.clear();
            while(check != 1) {
                check = 0;
                cout << "Введите параметр смеси p: ";
                cin >> p;
                if(p > 0 && p < 1) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
            } check = 0;
            while(check != 1) {
                cout << "Введите размер выборки: ";
                cin >> n;
                if (n > 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
            } check = 0;
            cin.clear();
            cin.ignore(100000, '\n');
            x = generateMix(p, v, v2);
            sample = random_sample_mix(p, v, v2, n);
            cout << "Функция плотноcти в случайной точке = " << densityMix(x, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Функция плотности при x=0 = " << densityMix(0, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Дисперсия = " << dispersionMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Эксцесс = " << excesMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Математическое ожидание = " << mathexpMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Асимметрия = " << asymmetryMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "\n==Эмпирические характеристики==\n";
            cout << "Функция плотности при x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Дисперсия = " << dispersion(sample) << "\n";
            cout << "Эксцесс = " << EmpExcess(sample) << "\n";
            cout << "Математическое ожидание = " << math_expectation(sample) << "\n";
            cout << "Асимметрия = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case '3':
            testStandart();
            testMix();
            empirical_test();
            break;
        case '4':
            while(check != 1) {
                check = 0;
                cout << "Enter form parameter v1: ";
                cin >> v;
                if(v >= 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            } check = 0;
            while(check != 1) {
                check = 0;
                cout << "Enter form parameter v2: ";
                cin >> v2;
                if(v2 >= 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            } check = 0;
            cout << "Введите параметр сдвига u1: ";
            cin >> u;
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Введите параметр сдвига u2: ";
            cin >> u2;
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Введите параметр масштаба lambda1: ";
            cin >> lam;
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Введите параметр масштаба lambda2: ";
            cin >> lam2;
            cin.clear();
            cin.ignore(100000, '\n');
            while(check != 1) {
                check = 0;
                cout << "Введите параметр смеси p: ";
                cin >> p;
                if(p > 0 && p < 1) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            } check = 0;
            while(check != 1) {
                cout << "Введите размер выборки: ";
                cin >> n;
                if (n > 0) check++;
                else cout << "Invalid format, please try again.\n";
                cin.clear();
                cin.ignore(100000, '\n');
            } check = 0;
            sample.clear();
            sample = random_sample_standart(n, v);
            sample2 = random_sample_standart(n, v);
            result_to_file_standart(sample, v, u, lam);
            result_to_file_empirical(sample, 0);
            result_to_file_empirical(sample2, 2);
            sample.clear(), sample2.clear();
            sample = random_sample_mix(p, v, v2, n);
            result_to_file_mix(sample, p, v, u, lam, v2, u2, lam2);
            result_to_file_empirical(sample, 1);
            sample.clear();
            break;
        case 'q':
            exit(0);
            break;
        case 'Q':
            exit(0);
            break;
        default:
            cout << "Undefined command, press enter for try again.\n";
            cin.clear();
            cin.ignore(100000, '\n');
            continue;
            break;
        }
    } while(i != 'q' || i != 'Q');
    return 0;
}