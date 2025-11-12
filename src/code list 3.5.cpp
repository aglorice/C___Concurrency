//
// Created by aglorice on 2025/11/12.
//

#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <iostream>

struct empty_stack final : std::exception {
    const char * what() const noexcept override {
        return "empty stack";
    }
};

template <class T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other);
        data = other.data;
    }
    threadsafe_stack & operator = (const threadsafe_stack&) = delete;
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value));
    }
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) {
            throw empty_stack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }
    void pop(T &value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) {
            throw empty_stack();
        }
        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

};

int main() {
    threadsafe_stack<int> si;
    si.push(5);
    si.push(5123);
    si.push(5123);
    si.push(51);
    auto p = si.pop();
    std::cout << *p << std::endl;
    if (!si.empty()) {
        int x;
        si.pop(x);
        std::cout << x << std::endl;
    }
}