//
// Created by aglorice on 2025/11/11.
//
#include <numeric>
#include <thread>
#include <iostream>

template<class Iterator,class T>
struct accumulate_block {
    void operator()(Iterator first,Iterator last,T & result) {
        result = std::accumulate(first,last,result);
    }
};

template<class Iterator,class T>
T parallel_accumulate(Iterator first,Iterator last,T init) {
    unsigned long const length = std::distance(first,last);
    if (!length) {
        return init;
    }
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1)/min_per_thread; // 向上取整
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    std::cout << "hardware_threads = " << hardware_threads << std::endl;
    unsigned long const num_threads = std::min(hardware_threads!=0 ? hardware_threads:2,max_threads);
    unsigned long const block_size = length/num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start = first;
    for (unsigned long i = 0;i<(num_threads-1);++i) {
        Iterator block_end = block_start;
        std::advance(block_end,block_size);
        threads[i] = std::thread(
            accumulate_block<Iterator,T>(),
            block_start,block_end,std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator,T>()(
        block_start,last,results[num_threads-1]);
    for (auto &entry : threads) {
        entry.join();
    }
    return std::accumulate(results.begin(),results.end(),init);
}


template<class Iterator,class T>
T common_accumulate(Iterator first,Iterator end,T init) {
    return std::accumulate(first,end,init);
}


int main()
{
    std::vector<int> vi;
    // 增加数据量以使时间测量更明显
    const int num_elements = 1000000; // 一千万个元素
    for(int i=0; i < num_elements; ++i)
    {
        vi.push_back(1); // 使用1，方便计算总和
    }
    // 初始值
    int initial_value = 5;
    std::cout << "std::distance(first,last) = " << std::distance(vi.begin(),vi.end()) << std::endl;

    // 测量 parallel_accumulate 的时间
    auto start_parallel = std::chrono::high_resolution_clock::now();
    int sum1 = parallel_accumulate(vi.begin(), vi.end(), initial_value);
    auto end_parallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_parallel = end_parallel - start_parallel;

    std::cout << "sum1 (parallel) = " << sum1 << std::endl;
    std::cout << "Parallel accumulate took: " << duration_parallel.count() << " seconds" << std::endl;

    std::cout << "----------------------------------------" << std::endl;

    // 测量 common_accumulate 的时间
    auto start_common = std::chrono::high_resolution_clock::now();
    int sum2 = common_accumulate(vi.begin(), vi.end(), initial_value);
    auto end_common = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_common = end_common - start_common;

    std::cout << "sum2 (common) = " << sum2 << std::endl;
    std::cout << "Common accumulate took: " << duration_common.count() << " seconds" << std::endl;

    return 0;
}