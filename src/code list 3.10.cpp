//
// Created by aglorice on 2025/11/13.
//

#include <mutex>
#include <iostream>

class Y {
private:
    int some_detail;
    mutable std::mutex m;
    int get_detail() const {
        std::lock_guard<std::mutex> lock_a(m);
        return some_detail;
    }
public:
    explicit Y(int sd) : some_detail(sd){}
    // 因为operator 是非成员函数，所以需要使用友元
    friend bool operator==(Y const & lhs,Y const & rhs) {
        // 这里不仅是为了节约性能，更是避免对同一个互斥量重复上锁
        if (&lhs == &rhs) {
            return true;
        }
        int const lhs_value = lhs.get_detail();
        int const rhs_value = rhs.get_detail();
        return lhs_value == rhs_value;
    }
};

int main() {
    Y l1(213);
    Y l2(213);
    std::cout << (l1 == l2) << std::endl;
}