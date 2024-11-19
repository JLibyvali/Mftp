#include "constant.hpp"

#include "debug.hpp"

#include <sstream>
#include <string>

// ##########################################
// C-style system error code
// ##########################################
std::string reactor::error_info = {};

int         ret_error(reactor::StatusCode _code, const std::string _custom)
{
    std::string str;
    switch (_code)
    {
    case reactor::StatusCode::Normal_err:
        {
            str = "Some error occurred with EXIT -1";
            break;
        }
    case reactor::StatusCode::Success:
        {
            str = "";
            break;
        }
    case reactor::StatusCode::Func_retError:
        {
            str = "Invoked function EXIT error";
            break;
        }
    default:
        {
            str = "Unknow type EXIT code";
        }
    }

    std::stringstream ss;
    ss << RED << "[Error INFORMATION] ";
    ss << "At " << __func__ << " " << __LINE__ << " :";
    ss << str << " : " << _custom << " ";
    ss << NONE;

    // Update error info
    auto temp = ss.str();
    reactor::error_info.swap(temp);

    return static_cast<int>(_code);
}

inline bool reactor::any_error(int _val)

{
    auto code = static_cast<StatusCode>(_val);

    switch (code)
    {
    case reactor::StatusCode::Normal_err:
    case reactor::StatusCode::Func_retError:
        {
            return true;
            break;
        }

    default: return false;
    }
}

inline std::string reactor::any_info(int _val)
{
    auto code = static_cast<StatusCode>(_val);

    switch (code)
    {
    case reactor::StatusCode::Normal_err:
    case reactor::StatusCode::Func_retError:
        {
            return error_info;
        }
    default: return "Error When get error information.";
    }
}