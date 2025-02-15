#include "benchmark/benchmark.h"
#include "debug.h"
#include "lf_queue.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

#define THREADS_NUM 10'000
std::array<std::thread, THREADS_NUM> threads;
std::array<std::string, 5>           data{"First str", "Second String", "Third Text", "Fourth", "Fifth"};
std::atomic<int>                     producer_cnt;

// _count Control the producer num in ALL threads.
void                                 manage(int _count)
{
    producer_cnt.store(_count);
    for (int i = 0; i < THREADS_NUM; i++)
    {
        threads[i] = std::thread(
            []()
            {
                bool isproducer = false;

                this_thread::sleep_for(std::chrono::milliseconds(10));
                if (producer_cnt.fetch_sub(1, std::memory_order_relaxed) > 0)
                    isproducer = true;

                if (isproducer)
                {
                }
                else
                {
                }
            }
        );
    }
}

int main(int argc, char *argv[])
{
    cout << LOG_FMT("----------------- Test Lock Free Queue ------------------------", LOG_BLUE) << endl;
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv))
        return -1;
    lfque::LFQueue<std::string> myqueue;

    return 0;
}
