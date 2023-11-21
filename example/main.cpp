#include <iostream>
#include <thread>
#include <functional>
#include "TimeIt.hpp"
#include "TimeFunction.hpp"

// Example functions
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void longRunningProcess() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int add(int a, int b) {
    return a + b;
}

void overheadTest() {
    std::cout << "\nOverhead Test:" << std::endl;
    constexpr int iterations = 100000;
    double total_duration_with_timeit = 0.0;
    double total_duration_with_timefunction = 0.0;

    // Testing overhead with TimeIt::TimeIt class
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            TimeIt::TimeIt timer("");
            fibonacci(10);
        }
        auto end = std::chrono::high_resolution_clock::now();
        total_duration_with_timeit = std::chrono::duration<double>(end - start).count();
    }

    // Testing overhead with TimeIt::TimeFunction class
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; ++i) {
            TimeIt::TimeFunction::timed_Function<void>("", std::function<void()>([]() { fibonacci(10); }));
        }
        auto end = std::chrono::high_resolution_clock::now();
        total_duration_with_timefunction = std::chrono::duration<double>(end - start).count();
    }

    // Print the results
    std::cout << "Total time with TimeIt::TimeIt: " << total_duration_with_timeit << " seconds\n";
    std::cout << "Total time with TimeIt::TimeFunction: " << total_duration_with_timefunction << " seconds\n";
    std::cout << "Average overhead per iteration with TimeIt::TimeIt: " << total_duration_with_timeit / iterations << " seconds\n";
    std::cout << "Average overhead per iteration with TimeIt::TimeFunction: " << total_duration_with_timefunction / iterations << " seconds\n";
}

int main() {
    overheadTest();
    return 0;
}
