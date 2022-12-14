#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>

template<typename T>
class Deque {
public:
    explicit Deque(int capacity);

    void PushFront(const T &node);

    void PushBack(const T &node);

    T PopFront();

    T PopBack();

    T Front() { return data_[head_]; }

    T Back() { return data_[(tail_ - 1 + capacity_) % capacity_]; }

    bool IsNotEmpty() { return head_ != tail_; };

    bool IsEmpty() { return head_ == tail_; }

    bool IsFull() { return (tail_ + 1) % capacity_ == head_; };

    int Size();

    int Head() { return head_; }

    int Tail() { return tail_; }

    ~Deque() { delete[]data_, data_ = NULL; }

public:
    int capacity_, head_, tail_;
    T *data_;
};

template<typename T>
Deque<T>::Deque(int capacity) {
    capacity_ = capacity;
    head_ = tail_ = 0;
    data_ = new T[capacity_];
}

template<typename T>
void Deque<T>::PushBack(const T &node) {
    if (IsFull()) {
        std::__throw_logic_error("queue is full");
    }
    data_[tail_] = node;
    tail_ = (tail_ + 1) % capacity_;
}

template<typename T>
void Deque<T>::PushFront(const T &node) {
    if (IsFull()) {
        std::__throw_logic_error("queue is full");
    }

    head_ = (head_ - 1 + capacity_) % capacity_;
    data_[head_] = node;
}

template<typename T>
T Deque<T>::PopBack() {
    if (IsEmpty()) {
        std::__throw_logic_error("queue is empty");
    }

    tail_ = (tail_ - 1 + capacity_) % capacity_;
    return data_[tail_];
}

template<typename T>
T Deque<T>::PopFront() {
    if (IsEmpty()) {
        std::__throw_logic_error("queue is empty");
    }

    head_ = (head_ + 1) % capacity_;
    return data_[(head_ - 1 + capacity_) % capacity_];
}

template<typename T>
int Deque<T>::Size() {
    if (head_ <= tail_) {
        return tail_ - head_;
    } else {
        return tail_ + (capacity_ - head_);
    }
}

#endif //DEQUE_H