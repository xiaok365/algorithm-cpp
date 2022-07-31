#include <iostream>

using namespace std;

#define MAXN 100
int n, m, temp, ans = 0, map[MAXN][MAXN], length[MAXN];
char s, t;
bool flag[MAXN];

void init() {

    cin >> n >> m;
    memset(map, -1, MAXN * MAXN);
    for (int i = 0; i < n; ++i) {
        map[i][i] = 0;
        flag[i] = false;
        length[i] = 0x7fffffff;
    }

    for (int i = 0; i < m; ++i) {
        cin >> s >> t >> temp;
        map[s - 'A'][t - 'A'] = temp;
        map[t - 'A'][s - 'A'] = temp;
    }

}

int main() {

    freopen("../a.in", "r", stdin);
    init();

    // 将0作为起点加入集合S
    flag[0] = true;
    for (int i = 0; i < n; ++i) {
        if (map[0][i] >= 0) {
            length[i] = map[0][i];
        }
    }

    // 选择N-1条边
    for (int i = 0; i < n - 1; ++i) {

        int min = 0x7fffffff;
        int k = 0;
        // 枚举非S所有点，选择最小的边
        for (int j = 1; j < n; ++j) {
            if (!flag[j] && length[j] < min) {
                min = length[j];
                k = j;
            }
        }

        ans += min;
        cout << "k=" << k << " ,min=" << min << endl;
        // 将新的点k加入集合S,并通过k更新非S中点的距离
        flag[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!flag[j] && map[k][j] >= 0 && map[k][j] < length[j]) {
                length[j] = map[k][j];
            }
        }
    }

    cout << "ans=" << ans << endl;
    return 0;
}
