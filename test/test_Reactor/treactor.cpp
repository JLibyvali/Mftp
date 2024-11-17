#include "reactor.hpp"

#include <chrono>
#include <future>
#include <iostream>

std::chrono::duration<double> time()
{

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < 100000; i++)
    {
        reactor::ResourceInit::procedure();
    }

    return (std::chrono::high_resolution_clock::now() - start);
}

int main()
{

    auto func1 = std::async(std::launch::async, [&]() { return time(); });
    auto func2 = std::async(std::launch::async, [&]() { return time(); });
    auto func3 = std::async(std::launch::async, [&]() { return time(); });
    auto func4 = std::async(std::launch::async, [&]() { return time(); });

    auto total = func1.get() + func2.get() + func3.get() + func4.get();
    std::cout << "Total time: " << total.count() << std::endl;
    // Just one instance generated and very fast

    return 0;
}