//
// Created by aglorice on 2025/11/7.
//
#include <iostream>
#include <thread>

void do_something(int & i) {
    ++i;
}

struct func {
    int & i;
    func(int & i_) : i(i_){}
    void operator()() {
        for (long j = 0;j<10000000;++j) {
            do_something(i);
        }
    }
};

void oops() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main() {
    oops();
}