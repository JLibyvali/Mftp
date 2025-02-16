/**
 * @file wrap_boost.hpp
 * @author JLibyvali  -->(https://github.com/JLibyvali)
 * @brief  A wrapper of Boost lock free library
 * @version 0.1
 * @date 2025-02-16
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "boost/lockfree/queue.hpp"

#include <boost/core/noncopyable.hpp>
#include <boost/lockfree/policies.hpp>
#include <condition_variable>
#include <mutex>
#include <type_traits>

namespace lfque
{

/**
 * @brief The Boost lockfree class requirement, ensure that at compile time, then the compiler can intent.
 *
 * @tparam T
 */
template <typename T>
concept isTrival = requires {
    std::is_copy_assignable<T>::value &&std::is_trivially_assignable<T &, T>::value
                                      &&std::is_trivially_destructible<T>::value;
};

/**
 * @brief A Wrapper of Boost LockFree Queue, for threads pool .
 *
 * @tparam DataType
 */
template <typename DataType>
    requires isTrival<DataType>
class LFQueBoost : private boost::noncopyable
{
private:

    std::mutex                                                       m_mutex;
    std::condition_variable                                          m_cv;
    boost::lockfree::queue<DataType, boost::lockfree::capacity<128>> m_tasks;

    void                                                             swapfrom(LFQueBoost<DataType> &_src) noexcept;

public:

    explicit LFQueBoost<DataType>(std::mutex &_mutex, std::condition_variable &_cv);
    ~LFQueBoost<DataType>();

    // Moveable
    LFQueBoost<DataType>(LFQueBoost<DataType> &&_src) noexcept;
    LFQueBoost<DataType> &operator=(LFQueBoost<DataType> &&_lhs) noexcept;

    [[nodiscard]] bool    empty() const;
    int                   push(const DataType &_src);
    int                   push(DataType &&_src);
    DataType              pop() const;
};
}  // namespace lfque

#include "wrap_boost.tpp"