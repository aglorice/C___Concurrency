//
// Created by aglorice on 2025/11/11.
//
#include <thread>
#include <iostream>

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_)
        : t(std::move(t_)) {
        std::cout << t.get_id() << " 进来了\n";
        if (!t.joinable()) {
            throw std::logic_error("No thread");
        }
    }

    ~scoped_thread() {
        if (t.joinable()) {
            std::cout << t.get_id() <<" 执行完了\n";
            t.join();
        }
    }

    scoped_thread(scoped_thread const &) = delete; // 禁用拷贝构造函数
    scoped_thread & operator=(scoped_thread const &) = delete;
};

void do_something(int &i) {
    ++i;
}

struct func {
    int &i;
    func(int &i_):i(i_){}

    void operator()() {
        std::cout << "开始执行 do_something\n";
        for (unsigned j = 0;i<1000000;++j) {
            do_something(i);
        }
        std::cout << "执行结束 do_something\n";
    }
};

void do_something_in_current_thread() {
    std::cout << "执行main线程\n";
}

void f() {
    int some_local_state = 0;
    std::cout << "some_local_state = " << some_local_state <<"\n";
    scoped_thread t((std::thread(func(some_local_state))));
    // scoped_thread t(std::thread(func(some_local_state))); // 这样可能被认为是函数声明而非实例化一个对象
    do_something_in_current_thread();
    std::cout << "some_local_state = " << some_local_state << "\n";
}

int main() {
    f();
}