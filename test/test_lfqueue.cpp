#include "benchmark/benchmark.h"
#include "debug.h"
#include "lf_queue.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#define THREADS_NUM 10
std::array<std::thread, THREADS_NUM> threads;
std::array<std::string, 5>           data{"First str", "Second String", "Third Text", "Fourth", "Fifth"};
std::atomic<int>                     producer_cnt;
std::atomic<int>                     counter;

// _count Control the producer num in ALL threads.
void                                 manage(lfque::LFQueue<std::string> &_obj, int _count)
{
    producer_cnt.store(_count);
    for (int i = 0; i < THREADS_NUM; i++)
    {
        threads[i] = std::thread(
            [&]()
            {
                bool isproducer = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                if (producer_cnt.fetch_sub(1, std::memory_order_relaxed) > 0)
                    isproducer = true;

                if (isproducer)
                {
                    for (int i = 0; i < 100; i++)
                        _obj.push(data[i % 5]);
                }
                else
                {
                    for (int i = 0; i < 100; i++)
                    {
                        if (auto item = _obj.pop(); !item.empty())
                            counter.fetch_add(1);
                    }
                }
            }
        );
    }

    for (int i = 0; i < THREADS_NUM; i++)
        threads[i].join();
}

static void BM_queue(benchmark::State &_state)
{
    counter.store(0, std::memory_order_release);
    int producernum = 5;

    for (auto _ : _state)
    {
        benchmark::ClobberMemory();
    }

    _state.counters["Success Transcation"] = counter.load(std::memory_order_acquire);
    _state.SetItemsProcessed(_state.iterations());
}

[[maybe_unused]] static void do_benchmark(int _argc, char *_argv_ptr[])
{
    benchmark::Initialize(&_argc, _argv_ptr);
    if (benchmark::ReportUnrecognizedArguments(_argc, _argv_ptr))
        return;
    benchmark::SetDefaultTimeUnit(benchmark::kMillisecond);

    benchmark::RegisterBenchmark("BM_LFQueue", BM_queue);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
}

static void do_lfqueue(lfque::LFQueue<std::string> &_obj)
{
    for (int i = 0; i < 5; i++)
        _obj.push(data[i]);

    std::cout << _obj.pop() << std::endl;
}

int main(int argc, char *argv[])
{
    std::cout << LOG_FMT("----------------- Test Lock Free Queue ------------------------", LOG_BLUE) << std::endl;

    lfque::LFQueue<std::string> myqueue;
    do_lfqueue(myqueue);

    return 0;
}
