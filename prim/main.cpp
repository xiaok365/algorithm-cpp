#include <iostream>

#define MAX_N 100
int n, map[MAX_N][MAX_N];

void init() {

    memset(map, 0x3f, MAX_N * MAX_N);
    for (int i = 0; i < n; ++i) {
        map[i][i] = 0;
    }

    int m, temp;
    char s, t;

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf(" %c %c %d", &s, &t, &temp);
        map[s - 'A'][t - 'A'] = temp;
        map[t - 'A'][s - 'A'] = temp;
    }

}

int prim() {

    int ans = 0, dist[MAX_N];
    bool visit[MAX_N] = {false};
    // 将0作为起点加入集合S
    visit[0] = true;

    // dist初始化
    memset(dist, 0x3f, sizeof dist);
    for (int i = 0; i < n; ++i) dist[i] = map[0][i];

    // 选择N-1条边
    for (int i = 1; i < n; ++i) {

        int min = 0x3f3f3f3f, k = -1;
        // 枚举非S所有点，选择最小的边
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }

        if (k == -1) {
            printf("不连通\n");
            return -1;
        }

        ans += min;
        printf("k=%d, min=%d\n", k, min);
        // 将新的点k加入集合S,并通过k更新非S中点的距离
        visit[k] = true;
        for (int j = 1; j < n; ++j) {
            if (!visit[j] && map[k][j] < dist[j]) {
                dist[j] = map[k][j];
            }
        }
    }

    return ans;
}

int main() {

    freopen("../a.in", "r", stdin);

    init();
    printf("ans=%d\n", prim());

    return 0;
}
