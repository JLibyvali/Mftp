#include "sigact.hpp"

#include "constant.hpp"
#include "debug.hpp"

#include <csignal>
#include <format>
#include <iostream>
#include <sstream>
#include <syncstream>

using namespace reactor;

SigAction::SigAction()
{
    // Init sigset mask
    sigemptyset(&m_cur_sigset);
    sigemptyset(&m_prev_sigset);
    sigaddset(&m_cur_sigset, m_worksig);

    // init sigaction struct
    sigemptyset(&m_sa.sa_mask);
    m_sa.sa_sigaction = handler;
    m_sa.sa_mask      = m_cur_sigset;  // Blocking another arrived second signal, when in signal handler.
    m_sa.sa_flags     = SA_RESTART | SA_SIGINFO;
}

int SigAction::notify(pid_t _proc)
{

    if (_proc <= 0)
        return ret_error(StatusCode::Normal_err);

    union sigval sval;
    sval.sival_int = 0;

    int ret        = sigqueue(_proc, m_worksig, sval);
    if (ret == -1)
        return ret_error(StatusCode::Func_retError);

    return 0;
}

int SigAction::listen(int _timeout)
{
    if (_timeout < 0)
        return ret_error(StatusCode::Normal_err);
}

void SigAction::handler(int _sig, siginfo_t *_info_ptr, void *_ucontext_ptr)
{
    auto print_siginfo = [&]()
    {
        std::stringstream ss;
        std::osyncstream  out{std::cout};

        ss << BLUE << "[Signal Information] :\n";
        ss << std::format(
            "signal number: {}, signal code: {}, signal associated value: {}\n", _info_ptr->si_signo,
            _info_ptr->si_code, _info_ptr->si_value.sival_int
        );
        ss << "From " << (_info_ptr->si_code == SI_USER ? "User kill()/raise()" : "")
           << (_info_ptr->si_code == SI_QUEUE ? "User sigqueue()" : "")
           << (_info_ptr->si_code == SI_KERNEL ? "Kernel" : "") << " ";
        ss << "Sender process: " << _info_ptr->si_pid << ", user: " << _info_ptr->si_uid << "\n";

        out << ss.str() << std::endl;
    };

    // print_siginfo();

}

void SigAction::set_sigcb(int _sig) {}