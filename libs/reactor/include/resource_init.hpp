#pragma once

#include "interface.hpp"

#include <atomic>
#include <cstdio>
#include <mutex>
#include <stdexcept>
#include <string>

namespace reactor
{

// Singleton implement init class;
class ResourceInit
{
public:

    static ResourceInit *procedure();

private:

    // generate nprocs process
    static int get_nproc();

    ResourceInit()                                                         = default;
    ~ResourceInit()                                                        = default;
    ResourceInit(const ResourceInit &_src)                                 = delete;
    ResourceInit                      &operator=(const ResourceInit &_src) = delete;

    static int                         m_nproc;
    static std::mutex                  m_mutex;
    static std::atomic<ResourceInit *> m_instance;
};

ResourceInit *ResourceInit::procedure() 
{
    auto ins_ptr = m_instance.load(std::memory_order_acquire);

    if (ins_ptr == nullptr)
    {
        std::lock_guard<std::mutex> lock{m_mutex};
        m_nproc = get_nproc();  // get  machine processors num
        if(any_error(m_nproc))
            throw std::runtime_error{"None m_nproc"};
        
        ins_ptr = m_instance.load(std::memory_order_relaxed);
        if (ins_ptr == nullptr)
        {
            ins_ptr = new ResourceInit();
            m_instance.store(ins_ptr, std::memory_order_release);
        }
    }

    return ins_ptr;
}

int ResourceInit::get_nproc()
{
    auto nproc_ptr = popen("nproc", "r");
    if (!nproc_ptr)
        return static_cast<int>(StatusCode::Func_retError);

    char        buf[10] = {};
    std::string tmp;
    while (fgets(buf, 10, nproc_ptr) != nullptr)
        tmp += buf;

    int ret = pclose(nproc_ptr);
    if (ret == -1)
        return static_cast<int>(StatusCode::Func_retError);

    return std::stoi(tmp);
}
}  // namespace reactor
