#ifndef RECURSION_CSTACK_H
#define RECURSION_CSTACK_H

#include <stdexcept>

using namespace std;

template<typename T>
class Cstack {
public:
    explicit Cstack(int size);

    ~Cstack();

    int size() const;

    T push(const T &node);

    T pop();

    T *top();

    bool is_not_mpty() const;

private:
    int capacity = 0;
    int total = 0;
    T *data;
};

template<class T>
Cstack<T>::Cstack(int size) {
    this->capacity = size;
    this->total = 0;
    this->data = new T[this->capacity];
}

template<class T>
int Cstack<T>::size() const {
    return this->total;
}

template<class T>
Cstack<T>::~Cstack() {
    delete[]this->data;
}

template<class T>
T Cstack<T>::push(const T &node) {
    if (this->total == this->capacity) {
        __throw_out_of_range("stack is full");
    }
    this->data[this->total++] = node;
    return this->data[this->total - 1];
}

template<class T>
T Cstack<T>::pop() {
    if (this->total == 0) {
        __throw_out_of_range("stack is empty");
    }
    this->total--;
    return this->data[this->total];
}

template<class T>
T *Cstack<T>::top() {
    if (this->total == 0) {
        __throw_out_of_range("stack is empty");
    }
    return &this->data[this->total - 1];
}

template<class T>
bool Cstack<T>::is_not_mpty() const {
    return this->total > 0;
}

#endif //RECURSION_CSTACK_H
