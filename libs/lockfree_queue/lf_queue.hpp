/**
 * First version edition based on CAS.
 */

#pragma once
#include "Event.hpp"

#include <atomic>
#include <boost/noncopyable.hpp>

namespace lf_que
{

// Concept required that given type moveable.
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
class LockFreeQueue final : public boost::noncopyable
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

        Node()  = default;
        ~Node() = default;
    };

    std::atomic_uint    m_size;
    std::atomic<Node *> m_head;
    std::atomic<Node *> m_tail;

public:

    explicit LockFreeQueue(DataType &_data);
    ~LockFreeQueue() = default;

    LockFreeQueue(LockFreeQueue<DataType> &&_src) noexcept;
    LockFreeQueue<DataType> &operator=(LockFreeQueue<DataType> &&_lhs) noexcept;

    [[nodiscard]] bool       empty() const;

    int                      push(DataType &_data);
    int                      push(DataType &&_data);
    DataType                 pop();
};

}  // namespace lf_que