//
// Created by aglorice on 2025/11/11.
//

#include <thread>
#include <iostream>

class joining_thread {
    std::thread t;
public:
    joining_thread() noexcept = default;
    template<class Callable,class ...Args>
    explicit joining_thread(Callable && func,Args && ...args)
        : t(std::forward<Callable>(func),std::forward<Args>(args)...) {
        std::cout << "explicit joining_thread(Callable && func,Args && ...args)" << std::endl;
    }
    explicit joining_thread(std::thread t_) noexcept
        : t(std::move(t_)){}

    // 移动构造函数
    joining_thread(joining_thread && other) noexcept
        : t(std::move(other.t)){}

    joining_thread & operator=(joining_thread && other) noexcept {
        if (joinable()) {
            join(); // 要等待当前的线程结束才能去接受另外一个线程
        }
        t = std::move(other.t);
        return *this;
    }

    joining_thread & operator=(std::thread other) noexcept {
        if (joinable()) {
            join();
        }
        t = std::move(other);
        return *this;
    }

    ~joining_thread() noexcept {
        if (joinable()) {
            join();
        }
    }

    void swap(joining_thread & other) noexcept {
        t.swap(other.t);
    }

    std::thread::id get_id() const noexcept {
        return t.get_id();
    }

    void join() {
        t.join();
    }

    void detach() {
        t.detach();
    }

    bool joinable() const noexcept {
        return t.joinable();
    }
};

void f1() {
    std::cout << "f1" << std::endl;
}

void f2() {
    std::cout << "f2" << std::endl;
}

void func() {
    joining_thread t1(f1);
    t1 = std::thread(f2);
    joining_thread t2((std::thread(f1)));
    std::thread t3 = std::thread(f2);
    joining_thread t4(std::move(t3));
    // joining_thread t4(t3); 这样是错误的，因为这样传入属于按值传递，但是std::thread是不可拷贝的，并且
    // std::thread 的拷贝构造是被删除的。
}

int main() {
    func();
}