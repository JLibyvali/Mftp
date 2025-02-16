#include "Event.hpp"
#include "debug.h"
#include "threadpool.hpp"

#include <ios>
#include <iostream>
#include <type_traits>

int main()
{
    std::cout << LOG_FMT("---------------- Test Threads Pool ------------------", LOG_BLUE) << std::endl;
    std::cout << "Test Type Trivially: " << std::boolalpha << threadspool::isTrival<ftp::event::NewConEvent *> << "\t"
              << std::is_copy_assignable<ftp::event::NewConEvent *>::value << "\t"
              << std::is_trivially_assignable<ftp::event::NewConEvent *&, ftp::event::NewConEvent *>::value << "\t"
              << std::is_trivially_destructible<ftp::event::NewConEvent *>::value << std::endl;

    threadspool::ThreadsPool<ftp::event::NewConEvent *>::instance(8);

    return 0;
}