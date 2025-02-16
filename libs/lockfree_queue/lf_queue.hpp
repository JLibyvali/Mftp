/**
 * @file lf_queue.hpp
 * @author JLibyvali  -->(https://github.com/JLibyvali)
 * @brief Implemented A lock free queue via C++ CAS
 * @version 0.1
 * @date 2025-02-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "boost/noncopyable.hpp"

#include <atomic>

namespace lfque
{

/**
 * @brief Required type is MoveAble.
 *
 * @tparam T Generic Data Type.
 */
template <typename T>
concept has_moveable = requires {
    typename T::value_type;
    std::is_move_constructible_v<T> &&std::is_move_assignable_v<T>;
};

/**
 * @brief WHY: Implement a RAII queue based on event driver, and required the data type is moveable.
 *        HOW: Implemented as a bidirectional list, with private data type node.
 * @tparam DataType Custom data type.
 */
template <typename DataType>
    requires has_moveable<DataType>
class [[deprecated("IT's not complete NOW!!")]] LFQueue final : private boost::noncopyable
{

private:

    /**
     * @brief list Lock-free queue data nodes.
     */
    struct Node
    {
        DataType            m_data;
        std::atomic<Node *> next;
        std::atomic<Node *> prev;

        Node();
        explicit Node(DataType &_data);
        ~Node() = default;
    };

    std::atomic_uint    m_size;
    std::atomic<Node *> m_head;
    std::atomic<Node *> m_tail;

    /**
     * @brief Helper function for move semantic
     */
    void                swapfrom(LFQueue<DataType> &_src) noexcept;

public:

    LFQueue();
    ~LFQueue();

    explicit LFQueue(DataType &_data);
    LFQueue(LFQueue<DataType> &&_src) noexcept;
    LFQueue<DataType> &operator=(LFQueue<DataType> &&_lhs) noexcept;

    [[nodiscard]] bool empty() const;

    int                push(DataType &_data);
    int                push(DataType &&_data);
    DataType           pop();
};

}  // namespace lfque

#include "lf_queue.tpp"