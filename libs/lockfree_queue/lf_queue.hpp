/**
 * First version, using C++ atomic and CAS to implement a Lock-free list queue.
 */
#pragma once
#include "Event.hpp"

#include <atomic>
#include <boost/noncopyable.hpp>

namespace lf_que
{

// Concept reuired type is moveable.
template <typename T>
concept has_moveable = requires {
    typename T::value_type;
    std::is_move_constructible_v<T> &&std::is_move_assignable_v<T>;
};

/**
 * @brief WHY: Implemente a RAII queue based on event driver, and required the data type is moveable.
 *        HOW: Implemented as a bidirectional circular list. with private data type node.
 * @tparam DataType Custom data type, will explicit template speciliazation serveral.
 */
template <typename DataType>
    requires has_moveable<DataType>
class LockFreeQueue final : public boost::noncopyable
{

private:

    struct Node
    {
        DataType            m_data;
        ftp::EventT         __event;
        std::string         m_msg;
        std::atomic<Node *> next;
        std::atomic<Node *> prev;

        explicit Node(ftp::EventT _event);
        ~Node() = default;
    };

    std::atomic_uint    m_size;
    std::atomic<Node *> m_head;
    std::atomic<Node *> m_tial;

public:

    explicit LockFreeQueue(ftp::EventT _event, DataType _data);
    ~LockFreeQueue() = default;

    // move semantics
    LockFreeQueue(LockFreeQueue<DataType> &&_src) noexcept;
    LockFreeQueue<DataType> &operator=(LockFreeQueue<DataType> &&_lhs) noexcept;

    // method
    [[nodiscard]] bool       empty() const;
    int                      push(DataType _data);
    int                      push(DataType &&_data);

    DataType                 pop();
};

}  // namespace lf_que