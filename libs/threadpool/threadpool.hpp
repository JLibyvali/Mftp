/**
 * @file threadpool.hpp
 * @author JLibyvali  -->(https://github.com/JLibyvali)
 * @brief The self implementation of threads pool via `condition_variable` or `semaphore` to synchours.
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "boost/core/noncopyable.hpp"
#include "boost/lockfree/policies.hpp"
#include "boost/lockfree/queue.hpp"

#include <atomic>
#include <condition_variable>
#include <fcntl.h>
#include <mutex>
#include <thread>
#include <vector>

namespace threadspool
{
/**
 * @brief Using condition_variable to finish a Thread pool.
 *
 */

/**
 * @brief The Boost lockfree class requirement, ensure that at compile time, then the compiler can intent.
 *
 * @tparam T
 */
template <typename T>
concept isTrival =
    std::is_copy_assignable_v<T> && std::is_trivially_assignable_v<T &, T> && std::is_trivially_destructible_v<T>;

/**
 * @brief A Wrapper of Boost LockFree Queue, for threads pool .
 *
 * @tparam DataType
 */
template <typename DataType>
    requires isTrival<DataType>
class ThreadsPool final : private boost::noncopyable
{
private:

    static std::mutex                                                 m_singleton;
    static std::atomic<ThreadsPool<DataType> *>                       m_instance;
    static int                                                        m_threadsnum;
    bool                                                              m_stop;
    std::mutex                                                        m_mutex;
    std::condition_variable                                           m_cv;
    boost::lockfree::queue<DataType, boost::lockfree::capacity<1024>> m_que;
    std::vector<std::thread>                                          m_threads;

    // Singleton
    ThreadsPool<DataType>();

    ~ThreadsPool<DataType>();

public:

    /**
     * @brief Singleton mode thread pool, `_num` for threads num.
     *
     * @param _num Thread num
     * @return ThreadsPool<DataType>* Singleton mode.
     */
    static ThreadsPool<DataType> *instance(int _num);
    ThreadsPool<DataType>(ThreadsPool<DataType> &&_src)            = delete;
    ThreadsPool<DataType> &operator=(ThreadsPool<DataType> &&_lhs) = delete;
};
}  // namespace threadspool

#include "threadpool.tpp"