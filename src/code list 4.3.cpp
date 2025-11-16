//
// Created by aglorice on 2025/11/16.
//

#include <memory>
#include <thread>

template<class T>
class threadsafe_queue {
public:
    threadsafe_queue();
    threadsafe_queue(const std::thread&);
    threadsafe_queue & operator=(const threadsafe_queue &) = delete;

    void push(T new_value);
    bool try_pop(T&value);
    std::shared_ptr<T> try_pop();
    void wait_and_pop(T &value);
    std::shared_ptr<T> wait_and_pop();
    bool empty() const;
};
