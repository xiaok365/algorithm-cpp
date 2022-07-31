#include <iostream>
#include <cstdio>
#include <iomanip>
#include <chrono>
#include <random>

using namespace std;

const int N = 1000000;

struct read_function {
    function<void()> engine;
    string name;
};

void data() {
//    freopen("a.in", "w", stdout);
//    srand((int) time(0));
//    for (int i = 0; i < N; ++i) {
//        fout << rand() << endl;
//    }

    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(0, 10);
    for (int i = 0; i < 10; ++i) {
        cout << distr(eng) << endl;
    }


}

#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)

char buf[1 << 20], *p1 = buf, *p2 = buf;

template<typename T>
inline void fread_int(T &x) {
    x = 0;
    char c = 0;
    bool minus = false;
    while (c < '0' || c > '9') minus |= c == '-', c = gc();
    while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
    if (minus > 0) x = -x;
}

void read4() {
    int t;
    for (int i = 0; i < N; ++i) {
        fread_int(t);
    }
}

inline int fast_read() {
    int x = 0;
    char ch = 0;
    bool minus = false;
    while (ch < '0' || ch > '9') minus |= ch == '-', ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return minus ? -x : x;
}

void read3() {
    int t;
    for (int i = 0; i < N; ++i) {
        t = fast_read();
    }
}

void read2() {
    int t;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &t);
    }
}

void read1() {
    ios::sync_with_stdio();
    int t;
    for (int i = 0; i < N; ++i) {
        cin >> t;
    }
}

void process(const read_function &func) {
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    func.engine();
    steady_clock::time_point end = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);
    cout << setw(7) << func.name << " time: " << setiosflags(ios::fixed) << time_span.count() << endl;

}

int main(int argc, char *argv[]) {

//    data();

    read_function fun_list[10];
    fun_list[0] = {read4, "fread"};
    fun_list[1] = {read3, "getchar"};
    fun_list[2] = {read2, "scanf"};
    fun_list[3] = {read1, "cin"};

    for (int i = 0; i < 4; ++i) {
        freopen("a.in", "r", stdin);
        process(fun_list[i]);
        fclose(stdin);
    }

    // 测试输出格式
    double t = 0.065107;
    cin >> t;
    printf("t=%010.2lf\n", t);
    cout << "t=" << setiosflags(ios::fixed) << setprecision(2)
         << setw(10) << setfill('0') << t << endl;

    return 0;
}
