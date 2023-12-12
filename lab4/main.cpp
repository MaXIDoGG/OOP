#include "test.cpp"

int main() {
    int j = 0, n = 0, interv = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    Standart *func1, *func2;
    Mixture<Standart, Standart> *mix1, *mix2;
    Mixture<Mixture<Standart, Standart>, Standart> *dmix;
    Mixture<Mixture<Standart, Standart>, Mixture<Standart, Standart>> *tmix;
    ofstream out;
    ifstream in;
    string choose;
    Empirical *emp;
    char i = '0', k = '0', t = '0';
    do {
        cout << "1: Pearson type II distribution(R-distribution)\n2: Distribution as a mixture of two distributions\n3: Running tests\nq: Exit\n";
        cin >> i;
        switch (i)
        {
        case '1':
            k = '0';
            while(k != '1' && k != '2') {
                try {
                    cout << "1: Enter from keyboeard\n2: Enter from file\n";
                    cin >> k;
                    cin.clear();
                    cin.ignore(100000, '\n');
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
                        func1 = new Standart(v, lam, u);
                    } else if(k == '2') {
                        func1 = new Standart(in);
                    }
                    cout << "Enter the sample size: ";
                    cin >> n;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    cout << "Enter the count of intervals: ";
                    cin >> interv;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    emp = new Empirical(func1, n, interv);
                } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    if(error == 3) cout << "Exception raised: false param of mix\n";
                    if(error == 4) cout << "Exception raised: false param of size\n";
                    if(error == 5) cout << "Exception raised: false count of interals\n";
                    k = '0';
                }
                if(k != '1' && k !='2') {
                    k = '0';
                    cout << "Try again\n";
                }
            }
            cout << "\nRESULTS:\n";
            x = func1->rand_num();
            cout << "Density function at a random point = " << func1->density(x) << "\n";
            cout << "Density function at 0 point = " << func1->density(0) << "\n";
            cout << "Dispersion = " << func1->varience() << "\n";
            cout << "Excess = " << func1->kurtosis() << "\n";
            cout << "Mathematical expectation = " << func1->expexted_value() << "\n";
            cout << "Asymmetry = " << func1->asymmetry() << "\n";
            cout << "\n==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << emp->density(x) << "\n";
            cout << "Dispersion = " << emp->varience() << "\n";
            cout << "Excess = " << emp->kurtosis() << "\n";
            cout << "Mathematical expectation = " << emp->expexted_value() << "\n";
            cout << "Asymmetry = " << emp->asymmetry() << "\n";
            try {
                start:
                cout << "Do you want save results?(yes/no): ";
                cin >> choose;
                cin.clear();
                cin.ignore(100000, '\n');
                if(choose == "yes" || choose == "y") {
                func1->save(out);
                emp->save(out);
                } else if(choose == "no" || choose == "n") {
                    goto end;
                } else {
                    cout << "try again.\n";
                    goto start;
                }
            } catch(int error) {
                    if(error == 0) cout << "Exception raised: fstream I/O error\n";
                    if(error == 1) cout << "Exception raised: false scale\n";
                    if(error == 2) cout << "Exception raised: false form\n";
                    if(error == 3) cout << "Exception raised: false param of mix\n";
                    if(error == 4) cout << "Exception raised: false param of size\n";
                    if(error == 5) cout << "Exception raised: false count of interals\n";
            }
            end:
            emp->~Empirical();
            emp = new Empirical(func1, 1000, 500);
            emp->save(out);
            break;
        case '2':
            k = '0';
            t = '0';
            cout << "1: Mixture of Standart and Standart\n2: Mixture of Mixture and Standart\n3: Mixture of Mixture and Mixture\n";
            cin >> t;
            if(t == '1') {
                while(k != '1' && k != '2') {
                    try {
                        cout << "1: Enter from keyboeard\n2: Enter from file\n";
                        cin >> k;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        if(k == '1') {
                            cout << "Enter form parameter v1: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter form parameter u1: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter shift parameter lambda1: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func1 = new Standart(v, u, lam);
                            cout << "Enter shift parameter v2: ";
                            cin >> v2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter u2: ";
                            cin >> u2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda2: ";
                            cin >> lam2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func2 = new Standart(v2, u2, lam2);
                            cout << "Enter the mix parameter p: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            mix1 = new Mixture(func1, func2, p);
                        } else if(k == '2') {
                            mix1->load(in);
                        }
                        cout << "Enter the sample size: ";
                        cin >> n;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the count of intervals: ";
                        cin >> interv;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        emp = new Empirical(mix1, n, interv);
                    } catch(int error) {
                        if(error == 0) cout << "Exception raised: fstream I/O error\n";
                        if(error == 1) cout << "Exception raised: false scale\n";
                        if(error == 2) cout << "Exception raised: false form\n";
                        if(error == 3) cout << "Exception raised: false param of mix\n";
                        if(error == 4) cout << "Exception raised: false param of size\n";
                        if(error == 5) cout << "Exception raised: false count of interals\n";
                        k = '0';
                    }
                    if(k != '1' && k !='2') {
                        k = '0';
                        cout << "Try again\n";
                    }
                }
                cout << "\nRESULTS:\n";
                x = mix1->rand_num();
                cout << "Density function at a random point = " << mix1->density(x) << "\n";
                cout << "Density function at 0 point = " << mix1->density(0) << "\n";
                cout << "Dispersion = " << mix1->varience() << "\n";
                cout << "Excess = " << mix1->kurtosis() << "\n";
                cout << "Mathematical expectation = " << mix1->expexted_value() << "\n";
                cout << "Asymmetry = " << mix1->asymmetry() << "\n";
                cout << "\n==Empirical characteristics==\n";
                cout << "Density function at x=0 = " << emp->density(x) << "\n";
                cout << "Dispersion = " << emp->varience() << "\n";
                cout << "Excess = " << emp->kurtosis() << "\n";
                cout << "Mathematical expectation = " << emp->expexted_value() << "\n";
                cout << "Asymmetry = " << emp->asymmetry() << "\n";
                try {
                    start1:
                    cout << "Do you want save results?(yes/no): ";
                    cin >> choose;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(choose == "yes" || choose == "y") {
                    mix1->save(out);
                    emp->save(out);
                    } else if(choose == "no" || choose == "n") {
                        goto end1;
                    } else {
                        cout << "try again.\n";
                        goto start1;
                    }
                } catch(int error) {
                        if(error == 0) cout << "Exception raised: fstream I/O error\n";
                        if(error == 1) cout << "Exception raised: false scale\n";
                        if(error == 2) cout << "Exception raised: false form\n";
                        if(error == 3) cout << "Exception raised: false param of mix\n";
                        if(error == 4) cout << "Exception raised: false param of size\n";
                        if(error == 5) cout << "Exception raised: false count of interals\n";
                }
                end1:
                emp->~Empirical();
                break;
            } else if(t == '2') {
                while(k != '1' && k != '2' && k != '3') {
                    try {
                        cout << "1: Enter from keyboeard\n2: Enter from file\n";
                        cin >> k;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        if(k == '1') {
                            cout << "MIXTURE:\n\nEnter form parameter v1: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter form parameter u1: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter shift parameter lam1: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func1 = new Standart(v, u, lam);
                            cout << "Enter shift parameter v2: ";
                            cin >> v2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter u2: ";
                            cin >> u2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda2: ";
                            cin >> lam2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func2 = new Standart(v2, u2, lam2);
                            cout << "Enter the mix parameter p: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            mix1 = new Mixture(func1, func2, p);
                            cout << "\nStandart:\n\nEnter shift parameter v: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter u: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func1 = new Standart(v, u, lam);
                            cout << "Enter the mix parameter p: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            dmix = new Mixture(mix1, func2, p);
                        } else if(k == '2') {
                            dmix->load(in);
                        }
                        cout << "Enter the sample size: ";
                        cin >> n;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the count of intervals: ";
                        cin >> interv;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        emp = new Empirical(dmix, n, interv);
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
                cout << "\nRESULTS:\n";
                x = dmix->rand_num();
                cout << "Density function at a random point = " << dmix->density(x) << "\n";
                cout << "Density function at 0 point = " << dmix->density(0) << "\n";
                cout << "Dispersion = " << dmix->varience() << "\n";
                cout << "Excess = " << dmix->kurtosis() << "\n";
                cout << "Mathematical expectation = " << dmix->expexted_value() << "\n";
                cout << "Asymmetry = " << dmix->asymmetry() << "\n";
                cout << "\n==Empirical characteristics==\n";
                cout << "Density function at x=0 = " << emp->density(x) << "\n";
                cout << "Dispersion = " << emp->varience() << "\n";
                cout << "Excess = " << emp->kurtosis() << "\n";
                cout << "Mathematical expectation = " << emp->expexted_value() << "\n";
                cout << "Asymmetry = " << emp->asymmetry() << "\n";
                try {
                    start2:
                    cout << "Do you want save results?(yes/no): ";
                    cin >> choose;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(choose == "yes" || choose == "y") {
                    dmix->save(out);
                    emp->save(out);
                    } else if(choose == "no" || choose == "n") {
                        goto end2;
                    } else {
                        cout << "try again.\n";
                        goto start2;
                    }
                } catch(int error) {
                        if(error == 0) cout << "Exception raised: fstream I/O error\n";
                        if(error == 1) cout << "Exception raised: false scale\n";
                        if(error == 2) cout << "Exception raised: false form\n";
                        if(error == 3) cout << "Exception raised: false param of mix\n";
                        if(error == 4) cout << "Exception raised: false param of size\n";
                        if(error == 5) cout << "Exception raised: false count of interals\n";
                }
                end2:
                emp->~Empirical();
            } else if(t == '3') {
                while(k != '1' && k != '2' && k != '3') {
                    try {
                        cout << "1: Enter from keyboeard\n2: Enter from file\n";
                        cin >> k;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        if(k == '1') {
                            cout << "MIXTURE1:\n\nEnter form parameter v1: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter form parameter u1: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter shift parameter lambda1: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func1 = new Standart(v, u, lam);
                            cout << "Enter shift parameter v2: ";
                            cin >> v2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter u2: ";
                            cin >> u2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda2: ";
                            cin >> lam2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func2 = new Standart(v2, u2, lam2);
                            cout << "Enter the mix parameter p: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            mix1 = new Mixture(func1, func2, p);
                            cout << "MIXTURE2:\n\nEnter form parameter v1: ";
                            cin >> v;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter form parameter u1: ";
                            cin >> u;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter shift parameter lambda1: ";
                            cin >> lam;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func1 = new Standart(v, u, lam);
                            cout << "Enter shift parameter v2: ";
                            cin >> v2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter u2: ";
                            cin >> u2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cout << "Enter scale parameter lambda2: ";
                            cin >> lam2;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            func2 = new Standart(v2, u2, lam2);
                            cout << "Enter the mix parameter p: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            mix2 = new Mixture(func1, func2, p);
                            cout << "Enter the mix parameter p for result Mixture: ";
                            cin >> p;
                            cin.clear();
                            cin.ignore(100000, '\n');
                            tmix = new Mixture(mix1, mix2, p);
                        } else if(k == '2') {
                            tmix->load(in);
                        }
                        cout << "Enter the sample size: ";
                        cin >> n;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        cout << "Enter the count of intervals: ";
                        cin >> interv;
                        cin.clear();
                        cin.ignore(100000, '\n');
                        emp = new Empirical(tmix, n, interv);
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
                cout << "\nRESULTS:\n";
                x = tmix->rand_num();
                cout << "Density function at a random point = " << tmix->density(x) << "\n";
                cout << "Density function at 0 point = " << tmix->density(0) << "\n";
                cout << "Dispersion = " << tmix->varience() << "\n";
                cout << "Excess = " << tmix->kurtosis() << "\n";
                cout << "Mathematical expectation = " << tmix->expexted_value() << "\n";
                cout << "Asymmetry = " << tmix->asymmetry() << "\n";
                cout << "\n==Empirical characteristics==\n";
                cout << "Density function at x=0 = " << emp->density(x) << "\n";
                cout << "Dispersion = " << emp->varience() << "\n";
                cout << "Excess = " << emp->kurtosis() << "\n";
                cout << "Mathematical expectation = " << emp->expexted_value() << "\n";
                cout << "Asymmetry = " << emp->asymmetry() << "\n";
                try {
                    start3:
                    cout << "Do you want save results?(yes/no): ";
                    cin >> choose;
                    cin.clear();
                    cin.ignore(100000, '\n');
                    if(choose == "yes" || choose == "y") {
                    tmix->save(out);
                    emp->save(out);
                    } else if(choose == "no" || choose == "n") {
                        goto end3;
                    } else {
                        cout << "try again.\n";
                        goto start3;
                    }
                } catch(int error) {
                        if(error == 0) cout << "Exception raised: fstream I/O error\n";
                        if(error == 1) cout << "Exception raised: false scale\n";
                        if(error == 2) cout << "Exception raised: false form\n";
                        if(error == 3) cout << "Exception raised: false param of mix\n";
                        if(error == 4) cout << "Exception raised: false param of size\n";
                        if(error == 5) cout << "Exception raised: false count of interals\n";
                }
                end3:
                emp->~Empirical();
            }
            break;
        case '3':
            testStandart();
            testMix();
            testEmpirical();
            cout << "All test are complete\n\n";
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
