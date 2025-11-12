//
// Created by aglorice on 2025/11/12.
//

#include <iostream>
#include <mutex>
#include <deque>

template<class T,class Container = std::deque<T>>
class stack {
public:
    explicit stack(const Container &);
    explicit stack(Container && = Container());
    template<class Alloc>
    explicit stack(const Alloc&);

    template<class Alloc> stack(const Container &,const Alloc &);
    template<class Alloc>stack(Container&&,const Alloc &);
    template<class Alloc>stack(stack&&,const Alloc &);

    bool empty() const;
    size_t size() const;
    T & top();
    T const& top() const;
    void push(T const&);
    void push(T &&);
    void pop();
    void swap(stack&&);
    template<class ...Args>
    void emplace(Args&&... args);
};