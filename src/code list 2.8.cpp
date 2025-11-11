//
// Created by aglorice on 2025/11/11.
//
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <iostream>

void do_work(unsigned id) {
    std::cout << id << std::endl;
}

void f() {
    std::vector<std::thread> threads;
    for (unsigned i = 0;i<20;++i) {
        threads.push_back(std::thread(do_work,i));
    }
    for (auto & entry : threads) {
        entry.join();
    }
}

int main() {
    f();
}