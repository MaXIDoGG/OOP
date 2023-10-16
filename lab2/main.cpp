#include "Header.h"
#include "StandartClass.h"

int main() {
    int i = 0, j = 0, n = 0;
    double v = 0, u = 0, lam = 0, p = 0, x = 0, v2 = 0, u2 = 0, lam2 = 0;
    vector<double> sample, sample2;
    Standart Func;
    do {
        cout << "1: Pearson type II distribution(R-distribution)\n2: Distribution as a mixture of two distributions\n3: Running tests\n4: Prepare files with results\n0: Exit\n";
        cin >> i;
        switch (i)
        {
        case 1:
//            cout << "Enter form parameter v: ";
//            cin >> v;
//            cout << "Enter shift parameter u: ";
//            cin >> u;
//            cout << "Enter scale parameter lambda: ";
//            cin >> lam;
            cout << "Enter the sample size: ";
            cin >> n;


                Func = Standart("data.txt");
//            Func.save("data.txt");
                sample = random_sample_standart(n, Func.getForm());

            cout << "Density function at a random point = " << Func.density(x) << "\n";
            cout << "Dispersion = " << Func.dispersion() << "\n";
            cout << "Excess = " << Func.excess() << "\n";
            cout << "Mathematical expectation = " << Func.mathexp() << "\n";
            cout << "Asymmetry = " << Func.asymmetry() << "\n";
            cout << "==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Dispersion = " << dispersion(sample) << "\n";
            cout << "Excess = " << EmpExcess(sample) << "\n";
            cout << "Mathematical expectation = " << math_expectation(sample) << "\n";
            cout << "Asymmetry = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case 2:
            cout << "Enter form parameter v1: ";
            cin >> v;
            cout << "Enter form parameter v2: ";
            cin >> v2;
            cout << "Enter shift parameter u1: ";
            cin >> u;
            cout << "Enter shift parameter u2: ";
            cin >> u2;
            cout << "Enter scale parameter lambda1: ";
            cin >> lam;
            cout << "Enter scale parameter lambda2: ";
            cin >> lam2;
            cout << "Enter the mix parameter p: ";
            cin >> p;
            cout << "Enter the sample size: ";
            cin >> n;
            x = generateMix(p, v, v2);
            sample = random_sample_mix(p, v, v2, n);
            cout << "Density function at a random point = " << densityMix(x, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Density function at x=0 = " << densityMix(0, p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Dispersion = " << dispersionMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Excess = " << excesMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Mathematical expectation = " << mathexpMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "Asymmetry = " << asymmetryMix(p, v, u, lam, v2, u2, lam2) << "\n";
            cout << "==Empirical characteristics==\n";
            cout << "Density function at x=0 = " << empirical_density(0, sample) << "\n";
            cout << "Dispersion = " << dispersion(sample) << "\n";
            cout << "Excess = " << EmpExcess(sample) << "\n";
            cout << "Mathematical expectation = " << math_expectation(sample) << "\n";
            cout << "Asymmetry = " << asymmetry(sample) << "\n";
            sample.clear();
            break;
        case 3:
//            testStandart();
            testMix();
            empirical_test();
            break;
//        case 4:
//            cout << "Enter form parameter v1: ";
//            cin >> v;
//            cout << "Enter form parameter v2: ";
//            cin >> v2;
//            cout << "Enter shift parameter u1: ";
//            cin >> u;
//            cout << "Enter shift parameter u2: ";
//            cin >> u2;
//            cout << "Enter scale parameter lambda1: ";
//            cin >> lam;
//            cout << "Enter scale parameter lambda2: ";
//            cin >> lam2;
//            cout << "Enter the mix parameter p: ";
//            cin >> p;
//            cout << "Enter the sample size: ";
//            cin >> n;
//            sample.clear();
//            sample = random_sample_standart(n, v);
//            sample2 = random_sample_standart(n, v);
//            result_to_file_standart(sample, v, u, lam);
//            result_to_file_empirical(sample, 0);
//            result_to_file_empirical(sample2, 2);
//            sample.clear(), sample2.clear();
//            sample = random_sample_mix(p, v, v2, n);
//            result_to_file_mix(sample, p, v, u, lam, v2, u2, lam2);
//            result_to_file_empirical(sample, 1);
//            sample.clear();
//            break;
        default:
            if (i != 0) cout << "Try again\n";
            break;
        }
    } while(i != 0);
    return 0;
}