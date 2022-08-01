#include <iostream>

using namespace std;

int f[101][1001], w[101], v[101];
int n, m;

int main() {

    freopen("../a.in", "r", stdin);

    cin >> m >> n;

    for (int i = 1; i <= m; ++i) {
        cin >> w[i] >> v[i];
    }

    f[0][0] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {

            f[i][j] = f[i - 1][j];
            if (j >= w[i]) {
                f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);
            }
        }
    }

    cout << f[m][n] << endl;

    return 0;
}
