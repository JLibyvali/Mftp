#pragma once
#include "constant.hpp"

#include <csignal>
#include <sys/signalfd.h>

namespace reactor
{
class SigAction
{

public:

    SigAction();
    ~SigAction() = default;

    /**
     * @brief Notify another process
     * @param _proc must be positive value, the signal notified destination.
     * @return int
     */
    int  notify(pid_t _proc);

    /**
     * @brief Will blocked at invoked timepoint, unless got notified or timeout
     * @param _timeout set blocked timeout, default no.
     * @return int
     */
    int  listen(int _timeout = 0);

    /**
     * @brief Set specific signal handler, default RT signal no handler, standard signal using system default handler.
     *
     * @param _set process signal set
     * @param _sig operate signal
     */
    void set_sigcb(int _sig);

private:

    // sigaction() parameters about.
    int                     m_worksig = SIGRTMIN + 1;
    sigset_t                m_cur_sigset, m_prev_sigset;
    struct sigaction        m_sa;
    siginfo_t               m_siginfo;
    struct signalfd_siginfo m_sig_fdinfo;
    static void                    handler(int _sig, siginfo_t *_info_ptr, void *_ucontext_ptr);

    volatile sig_atomic_t   m_sigflag;  // information flag between process and handler.
};
}  // namespace reactor