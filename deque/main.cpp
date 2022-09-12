#include <iostream>
#include "deque.h"

using namespace std;

int main() {

    Deque<int> deq(10);

    deq.PushBack(2);
    deq.PushFront(1);
    deq.PushFront(0);
    deq.PushBack(3);

    printf("head=%d tail=%d size=%d back=%d\n", deq.Head(), deq.Tail(), deq.Size(), deq.Back());

    while (deq.Size() > 2) {
        printf("%d\n", deq.PopBack());
    }

    deq.PushBack(2);
    deq.PushFront(1);
    deq.PushFront(0);
    deq.PushBack(3);

    printf("head=%d tail=%d size=%d front=%d\n", deq.Head(), deq.Tail(), deq.Size(), deq.Front());

    while (deq.IsNotEmpty()) {
        printf("%d\n", deq.PopFront());
    }

    return 0;
}
