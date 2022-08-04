#include <iostream>
#include "queue.h"

using namespace std;


int main() {
    Cqueue<int> my_queue(10);

    for (int i = 0; i < 8; ++i) {
        my_queue.Push(i);
    }

    for (int i = 0; i < 7; ++i) {
        printf("pop=%d\n", my_queue.Pop());
    }

    for (int i = 0; i < 5; ++i) {
        my_queue.Push(i);
    }

    printf("size=%d\n", my_queue.Size());

    while (my_queue.IsNotEmpty()) {
        printf("pop=%d\n", my_queue.Pop());
    }
    return 0;
}
