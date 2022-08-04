#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template<typename T>
class Cqueue {
public:
    explicit Cqueue(int capacity);

    void Push(T &node);

    T Pop();

    bool IsNotEmpty() {
        return head_ != tail_;
    }

    bool IsEmpty() {
        return head_ == tail_;
    }

    bool IsFull() {
        return (tail_ + 1) % capacity_ == head_;
    }

    int Size() {
        if (head_ <= tail_) {
            return tail_ - head_;
        } else {
            return tail_ + (capacity_ - head_);
        }
    }

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

#endif //QUEUE_H
