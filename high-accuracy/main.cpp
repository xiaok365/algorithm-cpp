#include <iostream>

using namespace std;

string add(string &a, string &b) {

    int len_a = a.size(), len_b = b.size(), len;
    if (len_a > len_b) len = len_a; else len = len_b;

    char c[1000] = {0};

    for (int i = 0; i < len; ++i) {
        if (i < len_a) {
            c[i] += a[len_a - i - 1] - '0';
        }
        if (i < len_b) {
            c[i] += b[len_b - i - 1] - '0';
        }
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    while (c[len] == 0) len--;

    string ret;
    for (int i = len; i >= 0; --i) {
        ret += c[i] + '0';
    }

    return ret;
}

int main() {

    freopen("../a.in", "r", stdin);

    string a, b;
    cin >> a >> b;

    cout << add(a, b) << endl;

    return 0;
}
