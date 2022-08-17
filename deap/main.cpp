#include <iostream>
#include <random>
#include "deap.h"

using namespace std;

int main() {

    Deap<int> deap(10);

    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> distr(1, 1000);

    for (int i = 0; i < 10; ++i) {
        int k = distr(eng);
        deap.Insert(k);
    }

    printf("min=%d, max=%d\n", deap.Min(), deap.Max());

    printf("popmin\n");
    int i = 0;
    for (; deap.Size() > 5;) {
        printf("i=%d, v=%d\n", ++i, deap.PopMin());
    }

    printf("popmax\n");
    for (; deap.Size() > 0;) {
        printf("i=%d, v=%d\n", ++i, deap.PopMax());
    }

    return 0;
}
