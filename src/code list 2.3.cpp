//
// Created by aglorice on 2025/11/7.
//

#include <iostream>
#include <thread>

void do_something(int & i) {
    ++i;
}

void do_something_in_current_thread() {

}


class thread_guard {
    std::thread & t;
public:
    explicit thread_guard(std::thread & t_): t(t_){}
    ~thread_guard() {
        std::cout << "thread_guard 析构函数被调用了！！\n";
        // 判断线程是否汇合
        if (t.joinable()) {
            t.join();
        }
    }

    // 阻止对象默认的拷贝和赋值方法
    thread_guard(thread_guard const &)=delete;
    thread_guard & operator=(thread_guard const &)=delete;
};
struct func {
    int & i;
    func(int & i_) : i(i_){}
    void operator()() {
        for (long j = 0;j<10000000;++j) {
            do_something(i);
        }
    }
};

void f() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_something_in_current_thread();
}

int main() {
    f();
}
