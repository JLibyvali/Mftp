/**
 * @file Event.hpp
 * @author JLibyvali  -->(https://github.com/JLibyvali)
 * @brief Described All Event type declarations, defintion will locate at src/kernel/include.
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <functional>

namespace ftp::event
{
enum class EventId : int
{
    newConnect = 133,
    unKnown    = -1
};

/**
 * @brief Event base struct, will hold an ID for specific type.
 */
struct EventT
{
    [[nodiscard]] virtual int getid() const = 0;
};

struct Param
{};

struct NewConEvent final : public EventT
{
    EventId                      m_id = EventId::newConnect;
    std::function<void(Param *)> m_task;

    [[nodiscard]] int            getid() const override { return static_cast<int>(m_id); }
};
}  // namespace ftp::event
