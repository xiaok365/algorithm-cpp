#include<iostream>
#include "rb_tree.h"

using namespace std;

int main() {

    freopen("../a.in", "r", stdin);

    TreeMap<int, int> mymap;
    RBNode<int, int> *p, *p1;

    int n, t;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        mymap.Insert(t, t);
    }

    cout << "min=" << mymap.FindMin() << endl;
    cout << "max=" << mymap.FindMax() << endl;

    cout << "height=" << mymap.Height() << endl;
    mymap.PrintTree();

    cout << "i=" << 6 << " " << mymap.FindNextMin(6) << endl;

    for (int i = 0; i < 20; ++i) {
        p = mymap.FindNextMin(i);
        p1 = mymap.FindNextMax(i);
        printf("i=%d, front=%d, end=%d\n", i, p->key, p1->key);
    }

    mymap.Insert(1, 1);
    cout << mymap.Find(1) << ", size=" << mymap.Size() << endl;

    mymap.ClearAll();
    cout << mymap.Find(1) << ", size=" << mymap.Size() << endl;

    mymap.Insert(2, 2);
    cout << mymap.Find(2) << ", size=" << mymap.Size() << endl;

    mymap.Remove(2);
    cout << mymap.Find(2) << ", size=" << mymap.Size() << endl;

    mymap.Insert(3, 3);
    cout << mymap.Find(3) << ", size=" << mymap.Size() << endl;


    return 0;
}