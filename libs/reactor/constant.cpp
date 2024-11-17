#include "constant.hpp"

// Exception and error code

bool reactor::any_error(int _var)
{
    auto tmp = static_cast<StatusCode>(_var);

    switch (tmp)
    {
    case reactor::StatusCode::Func_retError:
        {
            return true;
            break;
        }

    case reactor::StatusCode::Normal_err:
        {
            return true;
            break;
        }
    default: return false;
    }
}