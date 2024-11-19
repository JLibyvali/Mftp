#pragma once
#include "debug.hpp"

#include <string>

namespace reactor
{

// ##########################################
// C-style system error code
// ##########################################
extern std::string error_info;
enum class StatusCode : int
{
    Normal_err    = -1,
    Success        = 0,
    Func_retError = 333
};

int         ret_error(StatusCode _code,const std::string _custom = "");
inline bool        any_error(int _val);
inline std::string any_info(int _val);

// Some system resource initial.
class ResourceInit;

// Linux signal wrap
class SigAction;

// Wrap for all fd
class Channel;

// thread poll, memory pool,object  pool
class Pool;

}  // namespace reactor