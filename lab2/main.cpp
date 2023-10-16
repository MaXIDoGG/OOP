#include "Header.h"

int main() {
    int j = 0, n = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    vector<double> sample, sample2;
    Standart Func, Func2;
    string filename, filename2;
    char i = '0', k = '0';
    do {
        cout << "1: Pearson type II distribution(R-distribution)\n2: Distribution as a mixture of two distributions\n3: Running tests\n4: Prepare files with results\n5: Save/load\nq: Exit\n";
        cin >> i;
        switch (i)
        {
        case '1':
            k = '0';
            while(k != '1' && k != '2' && k != '3') {
                cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                cin >> k;
                cin.clear();
                cin.ignore(100000, '\n');
                try {
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
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    k = '0';
                } 
                if(k == '1' || k =='2' || k == '3') {
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(n <= 0) {
                        cout << "Exception raised: false size\n";
                        k = '0';
                    }
                } else{
                    k = '0';
                    cout << "Try again\n";
                }
            }
            sample = random_sample_standart(n, Func.getForm());
            cout << "Density function at a random point = " << Func.density(Func.Xgenerate()) << "\n";
            cout << "Density function at 0 point = " << Func.density(0) << "\n";
            cout << "Dispersion = " << Func.dispersion() << "\n";
            cout << "Excess = " << Func.excess() << "\n";
            cout << "Mathematical expectation = " << Func.mathexp() << "\n";
            cout << "Asymmetry = " << Func.asymmetry() << "\n";
            cout << "\n==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Dispersion = " << dispersion(sample) << "\n";
            cout << "Excess = " << EmpExcess(sample) << "\n";
            cout << "Mathematical expectation = " << math_expectation(sample) << "\n";
            cout << "Asymmetry = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case '2':
            k = '0';
            while(k != '1' && k != '2' && k != '3') {
                cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                cin >> k;
                cin.clear();
                cin.ignore(100000, '\n');
                try {
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
                        Func2 = Standart(filename2);
                    }
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    k = '0';
                } 
                if(k == '1' || k =='2' || k == '3') {
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(n <= 0) {
                        cout << "Exception raised: false size\n";
                        k = '0';
                    }
                }
                else{
                    k = '0';
                    cout << "Try again\n";
                }
                
            }
            x = generateMix(Func, p);
            sample = random_sample_mix(Func, p, n);
            cout << "Density function at a random point = " << densityMix(Func, Func2, Func.Xgenerate(), p) << "\n";
            cout << "Density function at x=0 = " << densityMix(Func, Func2, 0, p) << "\n";
            cout << "Dispersion = " << dispersionMix(Func, Func2, p) << "\n";
            cout << "Excess = " << excesMix(Func, Func2, p) << "\n";
            cout << "Mathematical expectation = " << mathexpMix(Func, Func2, p) << "\n";
            cout << "Asymmetry = " << asymmetryMix(Func, Func2, p) << "\n";
            cout << "==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Dispersion = " << dispersion(sample) << "\n";
            cout << "Excess = " << EmpExcess(sample) << "\n";
            cout << "Mathematical expectation = " << math_expectation(sample) << "\n";
            cout << "Asymmetry = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case '3':
            testStandart();
            testMix();
            empirical_test();
            break;
       case '4':
            k = 0;
            while(k != '1' && k != '2' && k != '3') {
                cout << "1: Enter from keyboeard\n2: Enter from file\n3: Skip\n";
                cin >> k;
                cin.clear();
                cin.ignore(100000, '\n');
                try {
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
                    }
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    k = '0';
                }
                if(k == '1' || k == '2' || k == '3') {
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(n <= 0) {
                        cout << "Exception raised: false size\n";
                        k = '0';
                    }
                }
                else {
                    k = '0';
                    cout << "Try again\n";
                }
            }
            sample = random_sample_standart(n, v);
            result_to_file_standart(sample, Func);
            result_to_file_empirical(sample, 0);
            sample.clear();
            sample = random_sample_mix(Func, p, n);
            result_to_file_mix(Func, Func2, sample, p);
            result_to_file_empirical(sample, 1);
            sample.clear();
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