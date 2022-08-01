#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

bool is_equal(double a, double b) {
    return abs(a - b) <= 1e-15;
}

// 函数f(x)
double f(double x, double n) {
    return x * x - n;
}

// 导数f'(x)
double fd(double x) {
    return 2 * x;
}

double newton(double n) {
    double x0 = 0, x1 = n;
    while (!is_equal(x1, x0)) {
        x0 = x1;
        x1 = x0 - f(x0, n) / fd(x0);
        cout << "x0=" << x0 << ", x1=" << x1 << endl;
    }
    return x1;
}

double search(double n) {
    double left = 0, right = 1;
    if (n > 1) {
        right = n;
    }

    double mid = (left + right) / 2;
    while (!is_equal(mid * mid, n)) {
        if (mid * mid > n) {
            right = mid;
        } else {
            left = mid;
        }
        mid = (left + right) / 2;

    }
    return mid;
}

int main() {

    double n;
    n = 9;
    cout << setiosflags(ios::fixed) << setprecision(16) << newton(n) << endl;
    printf("%.16f\n", search(n));
    printf("%.16f\n", sqrt(n));

    return 0;
}