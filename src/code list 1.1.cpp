//
// Created by aglorice on 2025/11/7.
//

#include <iostream>
#include <thread>


void hello() {
    std::cout << "Hello Concurrent World\n";
}

int main() {
    std::thread t(hello);
    t.join();
}