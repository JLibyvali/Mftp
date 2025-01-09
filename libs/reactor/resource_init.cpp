#include "resource_init.hpp"

#include "constant.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <unistd.h>

// ##############################
// Misc
// ##############################

struct reactor::Mprocs
{
    Mprocs()                                   = default;
    ~Mprocs()                                  = default;
    Mprocs(const Mprocs &_src)                 = delete;
    Mprocs      &operator=(const Mprocs &_src) = delete;

    // all process information
    static pid_t m_main_pid, m_con_pid, m_data_pid;

    // fd information

};

pid_t reactor::Mprocs::m_main_pid, reactor::Mprocs::m_con_pid, reactor::Mprocs::m_data_pid;

// ##################################################################
//  method definition
// #################################################################
using namespace reactor;
std::mutex                  ResourceInit::m_mutex;
std::atomic<ResourceInit *> ResourceInit::m_instance;

// ##################################################################
//  method definition
// #################################################################
ResourceInit               *ResourceInit::procedure()
{
    // Read instance pointer if any instance existed, using atomic.load(std::memory_order_acquire) ensure
    // that read order
    auto ins_ptr = m_instance.load(std::memory_order_acquire);

    if (ins_ptr == nullptr)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        ins_ptr = m_instance.load(std::memory_order_relaxed
        );  // second read, so that when threading waiting lock, other will not create instance.

        if (ins_ptr == nullptr)
        {
            ins_ptr = new ResourceInit();
            m_instance.store(ins_ptr, std::memory_order_release);
        }
    }

    return ins_ptr;
}

const int ResourceInit::get_nproc()
{
    auto nproc_ptr = popen("nproc", "r");
    if (!nproc_ptr)
        return static_cast<int>(StatusCode::Func_retError);

    char tmp[10] = {};
    fgets(tmp, 10, nproc_ptr);
    int ret = pclose(nproc_ptr);
    if (ret == -1)
        return static_cast<int>(StatusCode::Func_retError);

    return std::stoi(tmp);
}

void ResourceInit::procs_init()
{
    m_nproc = get_nproc();
    if (reactor::any_error(m_nproc))
        throw std::runtime_error{"None m_nproc"};

    // Generate sub process
}