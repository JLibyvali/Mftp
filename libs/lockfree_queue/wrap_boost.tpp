#pragma once

#include "wrap_boost.hpp"

#include <condition_variable>

template <typename DataType>
    requires lfque::isTrival<DataType>
lfque::LFQueBoost<DataType>::LFQueBoost(std::mutex &_mu, std::condition_variable &_cv) 
{}
