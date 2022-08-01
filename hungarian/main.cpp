#include <iostream>

using namespace std;

#define MAX_M 200
#define MAX_N 200
bool map[MAX_N][MAX_M] = {false}, visit[MAX_M];
int n, m, x[MAX_M], y[MAX_N], ans = 0;

bool hungary(int u) {
    for (int i = 0; i < m; ++i) {
        if (!visit[i] && map[u][i]) {
            visit[i] = true;
            if (y[i] == -1 || hungary(y[i])) {
                x[u] = i;
                y[i] = u;
                return true;
            }
        }
    }
    return false;
}

void init() {
    memset(x, 0xff, MAX_M * 4);
    memset(y, 0xff, MAX_N * 4);
    memset(map, false, MAX_N * MAX_M);

    int num, temp;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        for (int j = 0; j < num; ++j) {
            cin >> temp;
            map[i][temp - 1] = true;
        }
    }
}

int main() {

    freopen("../a.in", "r", stdin);

    init();
    for (int i = 0; i < n; ++i) {
        if (x[i] == -1) {
            memset(visit, false, MAX_M);
            if (hungary(i)) {
                ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}