#include "Header.h"

int main() {
    int j = 0, n = 0, interv = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    Standart Func, Func2;
    Mixture mix;
    string filename, filename2;
    Empirical *emp;
    char i = '0', k = '0';
    do {
        cout << "1: Pearson type II distribution(R-distribution)\n2: Distribution as a mixture of two distributions\n3: Running tests\n4: Prepare files with results\n5: Save/load\nq: Exit\n";
        cin >> i;
        switch (i)
        {
        case '1':
            k = '0';
            while(k != '1' && k != '2' && k != '3') {
                try {
                    cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                    cin >> k;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if (k != '3') {
                        if(k == '1') {
                            cout << "Enter form parameter v: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter shift parameter u: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            Func = Standart(v, lam, u);
                        } else if(k == '2') {
                            cout << "Enter filename: ";
                            cin >> filename;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            Func = Standart(filename);
                        }
                        cout << "Enter the sample size: ";
                        cin >> n;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the count of intervals: ";
                        cin >> interv;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        emp = new Empirical(Func, n, interv);
                    }
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    if(error == 3) cout << "Exception raised: false param of mix\n";
                    if(error == 4) cout << "Exception raised: false param of size\n";
                    if(error == 5) cout << "Exception raised: false count of interals\n";
                    k = '0';
                }
                if(k != '1' && k !='2' && k != '3') {
                    k = '0';
                    cout << "Try again\n";
                }
            }
            cout << "Density function at a random point = " << Func.density(Func.Xgenerate()) << "\n";
            cout << "Density function at 0 point = " << Func.density(0) << "\n";
            cout << "Dispersion = " << Func.dispersion() << "\n";
            cout << "Excess = " << Func.excess() << "\n";
            cout << "Mathematical expectation = " << Func.mathexp() << "\n";
            cout << "Asymmetry = " << Func.asymmetry() << "\n";
            cout << "\n==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << emp->empirical_density(x) << "\n";
            cout << "Dispersion = " << emp->dispersion() << "\n";
            cout << "Excess = " << emp->EmpExcess() << "\n";
            cout << "Mathematical expectation = " << emp->math_expectation() << "\n";
            cout << "Asymmetry = " << emp->asymmetry() << "\n";
            emp->~Empirical();
            break;
        case '2':
            k = '0';
            while(k != '1' && k != '2' && k != '3') {
                try {
                    cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                    cin >> k;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(k == '1') {
                        cout << "Enter form parameter v1: ";
                        cin >> v;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter form parameter v2: ";
                        cin >> v2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter shift parameter u1: ";
                        cin >> u;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter shift parameter u2: ";
                        cin >> u2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter scale parameter lambda1: ";
                        cin >> lam;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter scale parameter lambda2: ";
                        cin >> lam2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the mix parameter p: ";
                        cin >> p;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        if(p < -1 && p > 1) {
                            cout << "Exception raised: false mix parameter\n";
                            k = '0';
                        }
                        Func = Standart(v, lam, u);
                        Func2 = Standart(v2, lam2, u2);
                        mix = Mixture(Func, Func2, p);
                    } else if(k == '2') {
                        cout << "Enter filename: ";
                        cin >> filename;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        mix = Mixture(filename);
                    }
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    cout << "Enter the count of intervals: ";
                    cin >> interv;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    emp = new Empirical(mix, n, interv);
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    if(error == 3) cout << "Exception raised: false param of mix\n";
                    if(error == 4) cout << "Exception raised: false param of size\n";
                    if(error == 5) cout << "Exception raised: false count of interals\n";
                    k = '0';
                }
                if(k != '1' && k !='2' && k != '3') {
                    k = '0';
                    cout << "Try again\n";
                }
            }
            x = mix.generateMix();
            cout << "Density function at a random point = " << mix.densityMix(Func.Xgenerate()) << "\n";
            cout << "Density function at x=0 = " << mix.densityMix(0) << "\n";
            cout << "Dispersion = " << mix.dispersionMix() << "\n";
            cout << "Excess = " << mix.excesMix() << "\n";
            cout << "Mathematical expectation = " << mix.mathexpMix() << "\n";
            cout << "Asymmetry = " << mix.asymmetryMix() << "\n";
            cout << "==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << emp->empirical_density(0) << "\n";
            cout << "Dispersion = " << emp->dispersion() << "\n";
            cout << "Excess = " << emp->EmpExcess() << "\n";
            cout << "Mathematical expectation = " << emp->math_expectation() << "\n";
            cout << "Asymmetry = " << emp->asymmetry() << "\n";
            emp->~Empirical();
            break;
        case '3':
            testStandart();
            testMix();
            empirical_test();
            break;
       case '4':
            k = 0;
            while(k != '1' && k != '2' && k != '3') {
                try {
                    cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                    cin >> k;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(k == '1') {
                        cout << "Enter form parameter v1: ";
                        cin >> v;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter form parameter v2: ";
                        cin >> v2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter shift parameter u1: ";
                        cin >> u;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter shift parameter u2: ";
                        cin >> u2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter scale parameter lambda1: ";
                        cin >> lam;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter scale parameter lambda2: ";
                        cin >> lam2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the mix parameter p: ";
                        cin >> p;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        if(p < -1 && p > 1) {
                            cout << "Exception raised: false mix parameter\n";
                            k = '0';
                        }
                        Func = Standart(v, lam, u);
                        Func2 = Standart(v2, lam2, u2);
                        mix = Mixture(Func, Func2, p);
                    } else if(k == '2') {
                        cout << "Enter first filename: ";
                        cin >> filename;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        Func = Standart(filename);
                        cout << "Enter second filename: ";
                        cin >> filename2;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        Func = Standart(filename2);
                        cout << "Enter a param of mixture: ";
                        cin >> p;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        mix = Mixture(Func, Func2, p);
                    }
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    cout << "Enter the count of intervals: ";
                    cin >> interv;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    char c = 0;
                    cout << "1: Empirical of Mixture\n2:Empirical of Primary\n";
                    cin >> c;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if (c == '2') emp = new Empirical(Func, n, interv);
                    else if(c == '1') emp = new Empirical(mix, n, interv);
                    else emp = new Empirical(*emp);
                    cout << "1: Empirical of Mixture\n2:Empirical of Primary\n";
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    if(error == 3) cout << "Exception raised: false param of mix\n";
                    if(error == 4) cout << "Exception raised: false param of size\n";
                    if(error == 5) cout << "Exception raised: false count of interals\n";
                    k = '0';
                }
                if(k != '1' && k !='2' && k != '3') {
                    k = '0';
                    cout << "Try again\n";
                }
            }
            Func.result_to_file_standart(emp->get_x_s());
            mix.result_to_file_mix(emp->get_x_s());
            emp->result_to_file_empirical(0);
            emp->result_to_file_empirical(1);
            emp->result_to_file_empirical(2);
            emp->~Empirical();
            break;
        case '5':
            while(k != '1' && k != '2' && k != '3') {
                cout << "1: Save\n2: Load\n3: Skip\n";
                cin >> k;
                cin.clear();
                cin.ignore(100000, '\n');
                try {
                    if(k == '1') {
                        cout << "Enter filename: ";
                        cin >> filename;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        Func.save(filename);
                    } else if(k == '2') {
                        cout << "Enter filename: ";
                        cin >> filename;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        Func.load(filename);
                    } else if(k == '3') break;
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    k = '0';
                }
            }
            break;
        default:
            if (i != 'q' && i != 'Q') {
                        cout << "Try again\n";
                        cin.clear();
                        cin.ignore(100000, '\n');
                    }
            break;
        }
    } while(i != 'q' && i != 'Q');
    return 0;
}
