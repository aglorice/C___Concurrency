//
// Created by aglorice on 2025/11/22.
//

#include<future>
#include <list>
#include <iostream>

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if (input.empty()) {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(),input,input.begin());
    T const&pivot = *result.begin();
    auto divide_point = std::partition(input.begin(),input.end(),
        [&](T const&t) {
        return  t<pivot;
    });
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(),input,input.begin(),divide_point);
    std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>,std::move(lower_part)));
    auto new_higher(parallel_quick_sort(std::move(input)));

    result.splice(result.end(),new_higher);
    result.splice(result.begin(),new_lower.get());
    return result;
}


int main() {
    std::list<int> a = {12,312,3,12,3,12,312,3,};
    auto ret = parallel_quick_sort<int>(a);
    for (auto &i : ret) {
        std::cout << i << " ";
    }
}

