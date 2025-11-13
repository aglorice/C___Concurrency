//
// Created by aglorice on 2025/11/13.
//

//
// Created by aglorice on 2025/11/12.
//
#include <mutex>

class some_big_object {

};

void swap(some_big_object & lhs,some_big_object & rhs) {

}

class X {
private:
    some_big_object some_detail;
    mutable std::mutex m;
public:
    X(some_big_object const & sd) : some_detail(sd){}

    friend void swap(X & lhs,X & rhs) {
        /*
         * 两层意思
         * 1.节约性能开销
         * 2.避免对一个实例锁两次导致出现异常
         */
        if (&lhs == &rhs) {
            return;
        }
        std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);

        std::lock(lock_a,lock_b);
        swap(lhs.some_detail,rhs.some_detail);
    }
};

int main() {

}