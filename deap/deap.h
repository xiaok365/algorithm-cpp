#ifndef DEAP_DEAP_H
#define DEAP_DEAP_H

#include <cstdio>
#include <stdexcept>

template<typename T>
class Deap {
public:
    explicit Deap(int capacity);

    void Insert(T t);

    T PopMin();

    T PopMax();

    T Min() { return data_[1]; }

    T Max() { return data_[2]; }

    int Size() { return size_; }

    bool IsEmpty() { return size_ == 0; }

    bool IsFull() { return size_ == capacity_ - 1; }

public:
    T *data_;
    int capacity_, size_;

    void HeapUp(int k);

    void HeapDownMin(int k);

    void HeapDownMax(int k);

    bool IsRight(int u);

};

template<typename T>
Deap<T>::Deap(int capacity) {
    capacity_ = capacity + 1;
    data_ = new T[capacity_];
    size_ = 0;
}

template<typename T>
void Deap<T>::Insert(T t) {
    if (IsFull()) {
        std::__throw_logic_error("deap is full");
    }

    data_[++size_] = t;
    HeapUp(size_);
}

template<typename T>
T Deap<T>::PopMin() {
    if (IsEmpty()) {
        std::__throw_logic_error("deap is empty");
    }
    T ret = data_[1];
    data_[1] = data_[size_--];
    HeapDownMin(1);
    return ret;
}

template<typename T>
T Deap<T>::PopMax() {
    if (IsEmpty()) {
        std::__throw_logic_error("deap is empty");
    }
    if (size_ == 1) {
        return data_[size_--];
    }

    T ret = data_[2];
    data_[2] = data_[size_--];
    HeapDownMax(2);
    return ret;
}

template<typename T>
bool Deap<T>::IsRight(int u) {
    return (u & 1) == 0;
}


template<typename T>
void Deap<T>::HeapUp(int k) {
    int cur = k;
    T x = data_[k];

    while (cur > 0) {

        if (IsRight(cur) && x < data_[cur - 1]) {
            data_[cur] = data_[cur - 1];
            cur--;
        }

        int parent = (cur - 1) >> 1;
        int grand_parent = (parent - 1) >> 1;
        if (grand_parent == -1) break;

        int parent_min = (grand_parent << 1) + 1;
        int parent_max = parent_min + 1;

        if (x < data_[parent_min]) {
            data_[cur] = data_[parent_min];
            cur = parent_min;
        } else if (x > data_[parent_max]) {
            data_[cur] = data_[parent_max];
            cur = parent_max;
        } else break;
    }
    data_[cur] = x;
}

template<typename T>
void Deap<T>::HeapDownMin(int k) {

    int cur = k;
    T x = data_[k];

    while (cur < size_) {
        if (x > data_[cur + 1]) {
            T tmp = data_[cur + 1];
            data_[cur + 1] = x;
            x = tmp;
        }
        int son = (cur << 1) + 1;
        if (son > size_) break;

        if (son + 2 <= size_ && data_[son + 2] < data_[son]) son += 2;

        if (x > data_[son]) {
            data_[cur] = data_[son];
            cur = son;
        } else break;
    }
    data_[cur] = x;
}


template<typename T>
void Deap<T>::HeapDownMax(int k) {

    int cur = k;
    T x = data_[k];

    while (cur <= size_) {
        if (x < data_[cur - 1]) {
            T tmp = data_[cur - 1];
            data_[cur - 1] = x;
            x = tmp;
        }
        int son = cur << 1;
        if (son > size_) break;

        if (son + 2 <= size_ && data_[son + 2] > data_[son]) son += 2;

        if (x < data_[son]) {
            data_[cur] = data_[son];
            cur = son;
        } else break;
    }
    data_[cur] = x;
}

#endif //DEAP_DEAP_H
