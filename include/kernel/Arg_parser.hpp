#pragma once
#include "CLI/CLI.hpp"
#include "Preprocessor.hpp"

#include <array>
#include <boost/noncopyable.hpp>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace ftp
{
struct User_options
{
    std::string                m_list, m_add, m_del, m_set, m_anonymous;

    std::vector<CLI::Option *> M_opts;
};

struct Config_options
{
    std::size_t                m_space;
    bool                       m_telnet, m_database, m_console;
    std::size_t                port;

    std::vector<CLI::Option *> M_opts;
};

struct Mftp_options
{

    std::string                m_directroy{base_dir + "/data"};
    bool                       m_Islog{false}, m_Isbackend{false};
    std::size_t                m_cport{2121}, m_dport{2222};

    std::vector<CLI::Option *> M_opts;
};

class Arg_parser final : private boost::noncopyable

{
public:

    explicit Arg_parser(CLI::App &_app);
    ~Arg_parser() = default;

    void Arg_handler_set(CLI::App &_app);

private:

    // top level subcommand and options
    using cmd_text = std::pair<std::string, std::string>;
    std::array<cmd_text, FTP_CMDTEXT_LEN> m_cmdtext;
    CLI::App                             *m_ftp_user_cmd, *m_ftp_config_cmd;
    Mftp_options                          m_ftp_options;

    // User Config subcommand
    User_options                          m_user;
    Config_options                        m_config;
};

}  // namespace ftp
