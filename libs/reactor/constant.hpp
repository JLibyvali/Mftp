#pragma once

namespace reactor
{

// Exception and error code
enum class StatusCode : int
{
    Normal_err    = -1,
    Func_retError = 333
};
bool any_error(int _var);

// Some system resource initial.
class ResourceInit;

// process poll
class Pool;
}  // namespace reactor