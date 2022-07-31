#include <iostream>

using namespace std;


#define MAX_NUM 100

int sum[MAX_NUM] = {0}, n;

int lowbit(int x) {
    return x & -x;
}

void add(int index, int x) {

    while (index <= n) {
        sum[index] += x;
        index += lowbit(index);
    }
}

int query(int index) {

    int ret = 0;
    while (index > 0) {
        ret += sum[index];
        index -= lowbit(index);
    }

    return ret;
}


int main() {

    freopen("../a.in", "r", stdin);
    freopen("../a.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        add(i, x);
    }

    for (int i = 1; i <= n; ++i) {
        cout << query(i) << " ";
    }

    return 0;
}
