#include <iostream>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
#include "stack.h"


using namespace std;

long f[10000], g_count;
bool visit[5000];

long recursion(long step) {
    g_count++;
    if (visit[step]) {
        return f[step];
    }
    if (step == 0 || step == 1) {
        f[step] = 1;
        return f[step];
    }
    visit[step] = true;
    f[step] = recursion(step - 1) + recursion(step - 2);
    return f[step];
}

struct Element {
    long level;
    Element *parent;

    Element() = default;

    Element(long l, Element *p) : level(l), parent(p) {
    }
};

long process_stack(long n) {
    if (n < 2) { return 1; }
    Cstack<Element> cstack(10000);
    Element head = {n, nullptr};
    cstack.push(head);
    while (cstack.is_not_mpty()) {
        g_count++;
        Element *top = cstack.top();

        if (visit[top->level]) {
            if (top->parent) {
                f[top->parent->level] += f[top->level];
            }

            cstack.pop();
            continue;
        }

        if (top->level == 0 || top->level == 1) {
            if (top->parent) {
                f[top->parent->level] += 1;
                f[top->level] = 1;
            }
            cstack.pop();
            continue;
        }

        visit[top->level] = true;
        cstack.push(Element{top->level - 1, top});
        cstack.push(Element{top->level - 2, top});
    }
    return f[n];
}

void process(const function<long(long)> &func, long args) {

    memset(f, 0, sizeof(f));
    memset(visit, false, sizeof(visit));
    g_count = 0;

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    long ans = func(args - 1);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end - start);
    cout << setiosflags(ios::fixed) << "ans: " << ans << ", time: " << time_span.count() << ", count: " << g_count
         << endl;

//    for (long i = 0; i < args; ++i) {
//        cout << f[i] << " ";
//    }
//    cout << endl;
}

int main() {
    process(recursion, 1000);
    process(process_stack, 1000);
    return 0;
}
