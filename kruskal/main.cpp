#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int start;
    int end;
    int value;
};
const int MAXN = 100, MAXM = 100;

int n, m, answer = 0, edgeNum = 0, father[MAXN];
Edge edge[MAXM];

void init() {
    char s, e;
    int temp;

    // 并查集根结点，初始为-1，合并之后为-num,num表示集合中的个数
    memset(father, -1, MAXN);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> s >> e >> temp;
        edge[i].start = s - 'A';
        edge[i].end = e - 'A';
        edge[i].value = temp;
    }
}

bool compare(const Edge &a, const Edge &b) {
    return a.value < b.value;
}

int findFather(int s) {
    int root = s, temp;
    // 查找s的最顶层根
    while (father[root] >= 0) {
        root = father[root];
    }
    // 路径压缩，提高后续查找效率
    while (s != root) {
        temp = father[s];
        father[s] = root;
        s = temp;
    }
    return root;
}

void unionSet(int s, int e) {

    int rootS = findFather(s);
    int rootE = findFather(e);

    int weight = father[rootS] + father[rootE];
    // 将结点数少的集合作为结点数多的集合的儿子节点
    if (father[rootS] > father[rootE]) {
        father[rootS] = rootE;
        father[rootE] = weight;
    } else {
        father[rootE] = rootS;
        father[rootS] = weight;
    }
}


int main() {

    freopen("../a.in", "r", stdin);

    init();
    sort(edge, edge + m, compare);

    for (int i = 0; i < m; i++) {
        if (findFather(edge[i].start) != findFather(edge[i].end)) {
            unionSet(edge[i].start, edge[i].end);
            answer += edge[i].value;
            edgeNum++;
            if (edgeNum == n - 1) {
                break;
            }
        }
    }

    cout << answer << endl;
    return 0;
}