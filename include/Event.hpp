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

namespace ftp
{
enum class EventId : int
{
    newConnect = 133
};

/**
 * @brief Event base class, will hold an ID for specific type.
 */
class EventT
{
public:

    EventT()                                = default;
    virtual ~EventT()                       = default;

    [[nodiscard]] virtual int getid() const = 0;

protected:

    EventId m_id;
};

class NewConEvent : public EventT
{
public:

    NewConEvent() { m_id = EventId::newConnect; }

    virtual ~NewConEvent()                                   = default;

    NewConEvent(const NewConEvent &_src)                     = default;
    NewConEvent &operator=(const NewConEvent &_lhs)          = default;

    NewConEvent(NewConEvent &&_src) noexcept                 = default;
    NewConEvent      &operator=(NewConEvent &&_lhs) noexcept = default;

    [[nodiscard]] int getid() const override { return EventT::getid(); }

private:
    
};
}  // namespace ftp
