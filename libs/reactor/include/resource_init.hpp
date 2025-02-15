#pragma once

#include "constant.hpp"

#include <atomic>
#include <cstdio>
#include <mutex>
#include <sched.h>

namespace reactor
{

// Singleton implement init class;

// all process information;
struct Mprocs;

class ResourceInit
{
public:

    /**
     * @brief Using Double Check Locking ensure concurrent coding thread-safety with atomic operation.
     *
     * @return ResourceInit* instance pointer
     */
    static ResourceInit *procedure();

    /**
     * @brief Init work process pool
     *
     */
    void                 procs_init();

    ResourceInit(const ResourceInit &_src)            = delete;
    ResourceInit &operator=(const ResourceInit &_src) = delete;

private:

    // generate nprocs process
    const int get_nproc();

    ResourceInit()                             = default;
    ~ResourceInit()                            = default;

    int                                m_nproc = -1;
    static std::mutex                  m_mutex;
    static std::atomic<ResourceInit *> m_instance;
};

}  // namespace reactor