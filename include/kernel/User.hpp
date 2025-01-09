#pragma once
#include "Preprocessor.hpp"

#include <memory>

namespace ftp
{
namespace ftp_impl
{
class User_impl
{};
}  // namespace ftp_impl

class User
{
public:
private:

    std::unique_ptr<ftp_impl::User_impl> m_impl;
};

}  // namespace ftp