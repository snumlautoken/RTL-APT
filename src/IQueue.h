#pragma once
#include <queue>
#include <mutex>

template <typename T>
class IQueue {
    private:
    std::mutex mutex;
    std::queue<T> q;
    public:
    T front();
    void pop();
    void push(T c);
    int size();
};

template <typename T> void IQueue<T>::push(T c) {
    const std::lock_guard<std::mutex> lock(mutex);
    q.push(c);
}

template <typename T> T IQueue<T>::front() {
    const std::lock_guard<std::mutex> lock(mutex);
    T ret = q.front();
    return ret;
}

template <typename T> void IQueue<T>::pop() {
    const std::lock_guard<std::mutex> lock(mutex);
    q.pop();
}

template <typename T> int IQueue<T>::size() {
    const std::lock_guard<std::mutex> lock(mutex);
    return q.size();
}

