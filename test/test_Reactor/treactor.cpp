#include "reactor.hpp"
#include "resource_init.hpp"
#include "sigact.hpp"

#include <chrono>
#include <future>
#include <iostream>

void test_singleton()
{
    auto time = []() -> std::chrono::duration<double>
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (std::size_t i = 0; i < 100000; i++)
        {
            reactor::ResourceInit::procedure();
        }

        return (std::chrono::high_resolution_clock::now() - start);
    };

    auto func1 = std::async(std::launch::async, [&]() { return time(); });
    auto func2 = std::async(std::launch::async, [&]() { return time(); });
    auto func3 = std::async(std::launch::async, [&]() { return time(); });
    auto func4 = std::async(std::launch::async, [&]() { return time(); });

    auto total = func1.get() + func2.get() + func3.get() + func4.get();
    std::cout << "Single time performance: " << total.count() << std::endl;
}

void test_signal()
{
    auto res = reactor::ResourceInit::procedure();
    res->procs_init();
}

int main() { return 0; }