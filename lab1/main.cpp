#include "pirsonII.hpp"

using namespace std;

int main() {
    double x = 0, v = 7, u = 1, lam = 4;
    cout << v << "\n" << dispersion(v, lam) << "\n" << exces(v) << "\n" << density(x, v, u, lam);
    return 0;
}