#include "constant.hpp"

#include "debug.h"

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
    ss << LOG_RED << "[Error INFORMATION] ";
    ss << "At " << __func__ << " " << __LINE__ << " :";
    ss << str << " : " << _custom << " ";
    ss << LOG_NONE;

    // Update error info
    auto temp = ss.str();
    reactor::error_info.swap(temp);

    return static_cast<int>(_code);
}