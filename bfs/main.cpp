#include <iostream>

using namespace std;


#define MAX_N 100
#define MAX_M 100
#define QUEUE_LENGTH 10

struct Node {
    int x, y, d;

    Node() : x(0), y(0), d(0) {}

    Node(int xx, int yy, int d) : x(xx), y(yy), d(d) {}
};

const int dir_x[4] = {1, -1, 0, 0};
const int dir_y[4] = {0, 0, 1, -1};

int n, m, step = 0, map[MAX_N][MAX_M], visit[MAX_N][MAX_M];


bool valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && visit[x][y] == -1 && map[x][y] >= 0;
}

void bfs(Node &start, Node &target) {
    Node queue[QUEUE_LENGTH];
    int head = 0, tail = 1;

    memset(visit, 0xff, sizeof visit);
    queue[0] = Node(start.x, start.y, 0);
    visit[start.x][start.y] = -2;

    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        int d = queue[head].d;
        head = (head + 1) % QUEUE_LENGTH;
        for (int i = 0; i < 4; ++i) {
            int dx = x + dir_x[i];
            int dy = y + dir_y[i];
            if (valid(dx, dy)) {
                // 表示从i方向走过来的，方便后续回溯路径
                visit[dx][dy] = i;
                if (dx == target.x && dy == target.y) {
                    printf("已到目标点，最短距离为%d\n", d + 1);
                    step = d + 1;
                    return;
                }
                if ((tail + 1) % QUEUE_LENGTH == head) {
                    printf("队列满\n");
                    return;
                }
                // 新坐标入队
                queue[tail] = Node(dx, dy, d + 1);
                tail = (tail + 1) % (QUEUE_LENGTH);
            }
        }
    }
}

void display(Node &start, Node &target) {
    if (step <= 0) return;

    int path[MAX_N][MAX_M] = {0};
    memset(path, 0xff, sizeof path);

    int x = target.x, y = target.y;

    while (step >= 0) {
        path[x][y] = step--;
        int d = visit[x][y];
        x -= dir_x[d];
        y -= dir_y[d];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (path[i][j] >= 0) printf("%d", path[i][j]); else printf("-");
        }
        printf("\n");
    }
}

int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    Node start, target;
    scanf("%d %d %d %d", &start.x, &start.y, &target.x, &target.y);
    bfs(start, target);
    display(start, target);

    return 0;
}
