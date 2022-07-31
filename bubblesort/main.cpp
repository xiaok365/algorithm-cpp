#include <iostream>

using namespace std;

void swap(int &s, int &t) {
    int temp = s;
    s = t;
    t = temp;
}

int main() {

    freopen("../a.in", "r", stdin);

    int n, a[100], len, position = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    len = n - 1;
    for (int i = 0; i < n - 1; ++i) {
        cout << "Round " << i << ", len=" << len << endl;
        // flag标记是否有交换
        bool flag = true;
        for (int j = 0; j < len; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                flag = false;
                position = j;
            }
            cout << "j=" << j << ": ";
            for (int k = 0; k < n; ++k) {
                cout << a[k] << " ";
            }
            cout << endl;
        }
        len = position;
        if (flag) {
            break;
        }
    }

    cout << "finished!" << endl;
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }

    return 0;
}