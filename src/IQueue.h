#pragma once
#include <queue>
#include <mutex>

template <typename T>
class IQueue {
    private:
    std::mutex mutex;
    std::queue<T> q;
    public:
    T pop();
    void push(T c);
    int size();
};

template <typename T> void IQueue<T>::push(T c) {
    const std::lock_guard<std::mutex> lock(mutex);
    q.push(c);
}

template <typename T> T IQueue<T>::pop() {
    const std::lock_guard<std::mutex> lock(mutex);
    T ret = q.front();
    q.pop();
    return ret;
}

template <typename T> int IQueue<T>::size() {
    const std::lock_guard<std::mutex> lock(mutex);
    return q.size();
}

