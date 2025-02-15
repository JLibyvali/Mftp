#include "lf_queue.hpp"

#include <atomic>

// LockFreeQueue::Node constructors
template <typename DataType>
    requires lfque::has_moveable<DataType>
lfque::LFQueue<DataType>::Node::Node(DataType &_data) : m_data(_data), next(nullptr), prev(nullptr)
{}

// LockFreeQueue all constructors
template <typename DataType>
    requires lfque::has_moveable<DataType>
lfque::LFQueue<DataType>::LFQueue(DataType &_data) : m_size(0), m_head(nullptr), m_tail(nullptr)
{}

template <typename DataType>
    requires lfque::has_moveable<DataType>
void lfque::LFQueue<DataType>::swapfrom(LFQueue<DataType> &_src) noexcept
{
    this->m_size.store(_src.m_size.load(std::memory_order_acquire), std::memory_order_release);
    this->m_head.store(_src.m_head.load(std::memory_order_acquire), std::memory_order_release);
    this->m_tail.store(_src.m_tail.load(std::memory_order_acquire), std::memory_order_release);
}

template <typename DataType>
    requires lfque::has_moveable<DataType>
lfque::LFQueue<DataType>::LFQueue(lfque::LFQueue<DataType> &&_src) noexcept
{

    swapfrom(_src);

    _src.m_size.store(0, std::memory_order_relaxed);
    _src.m_head.store(nullptr, std::memory_order_relaxed);
    _src.m_tail.store(nullptr, std::memory_order_relaxed);
}

template <typename DataType>
    requires lfque::has_moveable<DataType>
lfque::LFQueue<DataType> &lfque::LFQueue<DataType>::operator=(lfque::LFQueue<DataType> &&_lhs) noexcept
{
    if (this == &_lhs)
        return *this;

    LFQueue<DataType> temp{_lhs};

    swapfrom(temp);
    _lhs.m_size.store(0, std::memory_order_relaxed);
    _lhs.m_head.store(nullptr, std::memory_order_relaxed);
    _lhs.m_tail.store(nullptr, std::memory_order_relaxed);
}

// Methods
template <typename DataType>
    requires lfque::has_moveable<DataType>
bool lfque::LFQueue<DataType>::empty() const
{
    return !static_cast<bool>(this->m_size.load(std::memory_order_acquire));
}

template <typename DataType>
    requires lfque::has_moveable<DataType>
int lfque::LFQueue<DataType>::push(DataType &_data)
{
    auto tempnode = new Node(_data);
    tempnode->prev.store(this->m_tail.load(std::memory_order_relaxed), std::memory_order_release);

    // CAS: Compare and Swap, try continuously compare `if(m_tail == tempnode->prev)`,
    // IF Another threads change the `m_tail` pointer, then just wait to next time to update `m_tail` pointer.
    while (!this->m_tail.compare_exchange_weak(
        tempnode->prev.load(), tempnode, std::memory_order_release, std::memory_order_relaxed
    ))
    {
    }

    m_size.fetch_add(1, std::memory_order_release);
}

template <typename DataType>
    requires lfque::has_moveable<DataType>
DataType lfque::LFQueue<DataType>::pop()
{
    if (!m_size.load(std::memory_order_acquire))
    {
        DataType non;
        return non;
    }

    Node *tempnode = m_head.load(std::memory_order_acquire);
    while (tempnode && !this->m_head.compare_exchange_weak(
                           tempnode, tempnode->next.load(), std::memory_order_release, std::memory_order_relaxed
                       ))
    {
    }

    m_size.fetch_sub(1, std::memory_order_release);
    return tempnode->m_data;
}