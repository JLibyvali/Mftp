#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include "asio.hpp"
#include "debug.h"

#include <chrono>
#include <csignal>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>
#include <unistd.h>

using time_type        = asio::steady_timer;
using signal_type      = asio::signal_set;
using sig_handler_type = void (*)(const asio::error_code &er, int);
asio::io_context io;

void             func_t1(const asio::error_code &er)
{
    if (!er)
    {
        // std::cout isn't thread-safe resource
        std::cout << "A Timer 1 finished" << std::endl;
        return;
    }
    else
    {
        std::cerr << er.message() << std::endl;
    }
}

void func_t2(const asio::error_code &er)
{
    if (!er)
    {
        // std::cout isn't thread-safe resource
        // std::osyncstream(std::cout) << "A Timer 2 finished" << std::endl;
        std::cout << "A Timer 2 finished" << std::endl;
        return;
    }
    else
    {
        std::cerr << er.message() << std::endl;
    }
}

int main()
{
    // io_context
    // Single io_context, single thread
    std::cout << RED << "Test Single thread: " << std::this_thread::get_id() << " and Single io_context" << NONE
              << std::endl;
    time_type   tim1(io), tim2(io);  // Define 3 Asynchronous events for IO
    signal_type sig(io);
    sig.add(SIGALRM);
    sig.add(SIGINT);

    tim1.expires_after(std::chrono::seconds(2));
    tim2.expires_after(std::chrono::seconds(2));
    // help function
    auto run_io = [&]()
    {
        alarm(1);
        io.run();
    };

    sig_handler_type sigint_handler = [](const asio::error_code &er, int sig)
    {
        if (sig == SIGINT)
        {
            std::osyncstream(std::cout) << "INT signal called" << std::endl;
        }
    };

    sig_handler_type sigalarm_handler = [](const asio::error_code &er, int sig)
    {
        if (sig == SIGALRM)
        {
            std::osyncstream(std::cout) << "ALARM signal called" << std::endl;
        }
    };

    // Register handler
    tim2.async_wait(func_t2);
    tim1.async_wait(func_t1);
    sig.async_wait(sigint_handler);
    sig.async_wait(sigalarm_handler);

    // run_io();    Single run(), will block until all event's handler finished.
    // Multi threads, call multiple io.run. It's boost recommend usage.
    std::cout << FMT("Test Multiple threads, run(), but still single io_context", RED) << std::endl;
    asio::detail::thread_group work_threads;
    for (int i = 0; i < 5; i++)
    {
        work_threads.create_thread(run_io);

        // std::thread th{run_io};
        // // th.detach();  // io.run() is blocked, but can use thread.detach() to avoid
        // th.join();
    }
    work_threads.join();

    // But multiple threads of Handler invoke order is unsure
    // Can use strand to  ensure the handler invoke order in multiple threads

    // Strand ensure handler invoke order

    std::cout << "Waiting......" << std::endl;
    asio::io_context::strand st{io};
    return 0;
}