#include<iostream>
#include "rb_tree.h"

using namespace std;

void printValue(RBNode<int, string> *p) {
    if (p) cout << "found value=" << p->value << endl; else cout << "not found" << endl;
}

int main() {

    freopen("../a.in", "r", stdin);

    TreeMap<int, int> mymap;
    RBNode<int, int> *p,*p1;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        mymap.Insert(t, t);
    }

    cout << mymap.Height() << endl;

    mymap.PrintTree();

//    p = mymap.FindNextMin(6);
//    cout << "i=" << 6 << " " << p->key << " " << p->value << endl;

    for (int i = 0; i < 20; ++i) {
        p = mymap.FindNextMin(i);
        p1 = mymap.FindNextMax(i);
        printf("i=%d, front=%d, end=%d\n",i,p->key,p1->key);
    }

//    mymap.Insert(1, "1");
//    p = mymap.Find(1);
//    printValue(p);
//    cout << "size=" << mymap.Size() << endl;
//
//    mymap.ClearAll();
//
//    p = mymap.Find(1);
//    printValue(p);
//    cout << "size=" << mymap.Size() << endl;
//
//    mymap.Remove(1);
//    p = mymap.Find(1);
//    printValue(p);
//    cout << "size=" << mymap.Size() << endl;
//
//    mymap.Insert(2, "2");
//    p = mymap.Find(2);
//    printValue(p);
//    cout << "size=" << mymap.Size() << endl;
//
//    mymap.Insert(3, "3");
//    p = mymap.Find(3);
//    printValue(p);
//    cout << "size=" << mymap.Size() << endl;

    return 0;
}