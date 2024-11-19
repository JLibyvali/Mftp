#include "sigact.hpp"

#include "constant.hpp"
#include "debug.hpp"

#include <csignal>
#include <cstddef>
#include <format>
#include <iostream>
#include <sstream>
#include <syncstream>

using namespace reactor;

SigAction::SigAction() : m_worksig(SIGRTMIN + 1)
{
    // Init sigset mask
    sigemptyset(&m_cur_sigset);
    sigemptyset(&m_prev_sigset);
    sigaddset(&m_cur_sigset, m_worksig);

    // init sigaction struct
    sigemptyset(&m_sa.sa_mask);
    m_sa.sa_handler   = NULL;          // Set At behind interface.
    m_sa.sa_sigaction = NULL;
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

int SigAction::listen(int _timeout, bool _handler)
{
    if (_timeout < 0)
        return ret_error(StatusCode::Normal_err);

    // If handler flag set, use handler when signal notified
    if (_handler)
    {
        if (any_error(sigprocmask(SIG_BLOCK, &m_cur_sigset, &m_prev_sigset)))
            return ret_error(StatusCode::Func_retError);

        // Set handler
        m_sa.sa_sigaction = work_handler;
        if (any_error(sigaction(m_worksig, &m_sa, NULL)))
            return ret_error(StatusCode::Func_retError);
    }
    else
    {
        // block all signal before sigwaitinfo
        if (any_error(sigprocmask(SIG_BLOCK, &m_cur_sigset, &m_prev_sigset)))
            return ret_error(StatusCode::Func_retError);

        int sig = sigwaitinfo(&m_cur_sigset, &m_siginfo);
        if (any_error(sig))
            return ret_error(StatusCode::Func_retError);

        // do more work.
    }

    return ret_error(StatusCode::Normal_err);
}

volatile std::sig_atomic_t SigAction::m_sigflag = false;

void                       SigAction::work_handler(int _sig, siginfo_t *_info_ptr, void *_ucontext_ptr)
{
    auto print_siginfo = [&]()
    {
        thread_local std::stringstream ss;
        std::osyncstream               out{std::cout};

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

    // Default handler print work_sig information.
    print_siginfo();
    m_sigflag = true;
}