#include <iostream>

using namespace std;

#define MAX_M 200
#define MAX_N 200
bool map[MAX_N][MAX_M], visit[MAX_M];
int n, m, y[MAX_N], ans = 0;

bool hungary(int u) {
    for (int i = 0; i < m; ++i) {
        if (!visit[i] && map[u][i]) {
            visit[i] = true;
            if (y[i] == -1 || hungary(y[i])) {
                y[i] = u;
                return true;
            }
        }
    }
    return false;
}

void init() {
    memset(y, 0xff, sizeof y);
    memset(map, false, sizeof map);

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
        memset(visit, false, sizeof visit);
        ans += hungary(i);
    }
    cout << ans << endl;
    return 0;
}