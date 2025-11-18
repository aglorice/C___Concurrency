//
// Created by aglorice on 2025/11/17.
//

#include <future>
#include <iostream>

int find_the_answer_to_ltuae() {
    return 42;
}

void do_other_stuff();

int main() {
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    std::cout << "The answer is " << the_answer.get() << std::endl;
}

