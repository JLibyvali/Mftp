#pragma once

namespace reactor
{

enum class StatusCode : int 
{
    Normal_err = -1,
    Func_retError = 333
};

bool any_error(int _var);

class ResourceInit;
}  // namespace reactor