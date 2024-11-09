#pragma once
#include "CLI/CLI.hpp"
#include "preprocessor.hpp"

#include <array>
#include <boost/noncopyable.hpp>
#include <cstdint>
#include <string>
#include <utility>

namespace ftp
{
class Arg_parser final : private boost::noncopyable
{
public:

    explicit Arg_parser(CLI::App &_app);
    ~Arg_parser() = default;

private:

    std::string  m_directroy;
    bool         m_Islog, m_Isbackend;
    std::int32_t m_cmd_num = FTP_CMD_NUM;

    using cmd_text         = std::pair<std::string, std::string>;
    std::array<cmd_text, FTP_CMD_NUM> m_ftp_cmds;
};

void Arg_handler(CLI::App &_app);
}  // namespace ftp
