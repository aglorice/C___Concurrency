//
// Created by aglorice on 2025/11/14.
//

#include <mutex>


struct some_resource {
    void do_something() {

    }
};


std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void foo() {
    // 无论资源是否初始化了，代码到这里都要被阻塞。
    std::unique_lock<std::mutex> lk(resource_mutex);
    if (!resource_ptr) {
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();
}

int main() {
    foo();
}