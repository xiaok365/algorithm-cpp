#include <iostream>
#include <fstream>

using namespace std;

const int direction[4][2] = {{0,  1},
                             {-1, 0},
                             {0,  -1},
                             {1,  0}};

const int MAXM = 100, MAXN = 100, QUEUE_LENGTH = 5;

struct Node {
    int x, y, distance;

    Node() {}

    Node(int xx, int yy, int d) : x(xx), y(yy), distance(d) {}
};

int n, m, step = 0, map[MAXM][MAXN], visit[MAXM][MAXN];
Node start, target;

void bfs() {
    Node queue[QUEUE_LENGTH];
    int head = 0, tail = 1;
    queue[0] = Node(start.x, start.y, 0);
    visit[start.x][start.y] = 0;

    while (head != tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        int distance = queue[head].distance;
        head = (head + 1) % QUEUE_LENGTH;
        for (int i = 0; i < 4; ++i) {
            int dx = x + direction[i][0];
            int dy = y + direction[i][1];
            if (dx >= 0 && dx < m && dy >= 0 && dy < n && visit[dx][dy] == -1 && map[dx][dy] >= 0) {
                // 表示从i方向走过来的，方便后续回溯路径
                visit[dx][dy] = i;

                if (dx == target.x && dy == target.y) {
                    cout << "已到目标点，最短距离为" << distance + 1 << endl;
                    step = distance + 1;
                    return;
                }

                if ((tail + 1) % QUEUE_LENGTH == head) {
                    cout << "队列满" << endl;
                    return;
                }
                // 新坐标入队
                queue[tail] = Node(dx, dy, distance + 1);
                tail = (tail + 1) % (QUEUE_LENGTH);
            }
        }
    }
}

void printPath() {

    int x, y, d, path[MAXM][MAXN] = {0};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            path[i][j] = -1;
        }
    }

    x = target.x;
    y = target.y;
    path[start.x][start.y] = 0;

    while (!(x == start.x && y == start.y)) {
        path[x][y] = step--;
        d = visit[x][y];
        x -= direction[d][0];
        y -= direction[d][1];
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (path[i][j] >= 0) {
                cout << path[i][j];
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }
}

int main() {

    freopen("../a.in","r",stdin);
    freopen("../a.out","w",stdout);

    cin >> m >> n;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
            visit[i][j] = -1;
        }
    }

    cin >> start.x >> start.y >> target.x >> target.y;

    bfs();

    if (step > 0) printPath();

    return 0;
}
