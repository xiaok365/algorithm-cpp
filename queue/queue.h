#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template<typename T>
class Cqueue {
public:
    explicit Cqueue(int capacity);

    void Push(T &node);

    T Pop();

    bool IsNotEmpty();

    bool IsEmpty();

    bool IsFull();

    int Size();

private:
    int capacity_, head_, tail_;
    T *data_;
};

template<typename T>
Cqueue<T>::Cqueue(int capacity) {
    capacity_ = capacity;
    head_ = tail_ = 0;
    data_ = new T[capacity_];
}

template<typename T>
bool Cqueue<T>::IsNotEmpty() {
    return head_ != tail_;
}

template<typename T>
bool Cqueue<T>::IsEmpty() {
    return head_ == tail_;
}

template<typename T>
bool Cqueue<T>::IsFull() {
    return (tail_ + 1) % capacity_ == head_;
}

template<typename T>
void Cqueue<T>::Push(T &node) {
    if (IsFull()) {
        std::__throw_logic_error("queue is full");
    }
    data_[tail_] = node;
    tail_ = (tail_ + 1) % capacity_;
}

template<typename T>
T Cqueue<T>::Pop() {
    if (IsEmpty()) {
        std::__throw_logic_error("queue is empty");
    }
    T tmp = data_[head_];
    head_ = (head_ + 1) % capacity_;
    return tmp;
}

template<typename T>
int Cqueue<T>::Size() {
    if (head_ <= tail_) {
        return tail_ - head_;
    } else {
        return tail_ + (capacity_ - head_);
    }
}

#endif //QUEUE_H
