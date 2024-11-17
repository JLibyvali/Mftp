#pragma once

#include "constant.hpp"

namespace reactor
{
class Pool
{

public:

    Pool();
    ~Pool()                                  = default;

    // no copy
    Pool(const Pool &_src)            = delete;
    Pool &operator=(const Pool &_src) = delete;

private:
    
};
}  // namespace reactor