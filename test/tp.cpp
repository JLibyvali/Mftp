#include "process.hpp"

#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

void routine()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Process 1........." << std::endl;
    std::clog << "Error message........." << std::endl;
    std::exit(0);
}

void asyn_routine()
{
    std::this_thread::sleep_for(std::chrono::seconds(4));
    exit(0);
}

class Rountine
{
public:

    void operator()()
    {
        std::cout << "Waiting 2  seconds" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        exit(0);
    }
};

int main()

{

    std::cout << "Test normal process" << std::endl;

    TinyProcessLib::Process proc{
        routine, [](const char *bytes, size_t n)
        { std::cout << "Read from process stdout: " << std::string{bytes, n} << std::endl; },
        [](const char *bytes, size_t n)
        { std::cout << "Read from process stderr: " << std::string(bytes, n) << std::endl; }
    };
    std::cout << "Waiting: " << proc.get_id() << " .............." << std::endl;

    int exit_status = proc.get_exit_status();  // Blocking until process exit
    std::cout << "Exit code: " << exit_status << std::endl;

    std::cout << "Test async sleep " << std::endl;

    auto asyn_proc = std::make_shared<TinyProcessLib::Process>(
        asyn_routine, [](const char *bytes, size_t n)
        { std::cout << "Read from process stdout: " << std::string{bytes, n} << std::endl; },
        [](const char *bytes, size_t n)
        { std::cout << "Read from process stderr: " << std::string(bytes, n) << std::endl; }
    );
    std::thread task_0{[&asyn_proc]()
                       {
                           int exit_code;
                           exit_code = asyn_proc->get_exit_status();
                           std::cout << "Exit code: " << exit_code << std::endl;
                       }};
    task_0.detach();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    asyn_proc->kill(true);
    std::cout << "Asynchronous killed, not blocking...................." << std::endl;

    std::cout << "Test None blocking with polling" << std::endl;
    Rountine rt;
    exit_status = -1;
    TinyProcessLib::Process nonb_proc{
        rt, [](const char *bytes, size_t n)
        { std::cout << "Read process stdout: " << std::string(bytes, n) << std::endl; }, nullptr
    };
    nonb_proc.close_stdin();
    while (!nonb_proc.try_get_exit_status(exit_status))
    {
        std::cout << "Process running\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Process finished: " << exit_status << std::endl;

    return 0;
}