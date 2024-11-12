#pragma once

#include "preprocessor.hpp"

#include <memory>

namespace ftp
{
namespace ftp_impl
{
class Config_impl
{};
}  // namespace ftp_impl

class Config
{
public:
private:

    std::unique_ptr<ftp_impl::Config_impl> m_impl;
};

}  // namespace ftp