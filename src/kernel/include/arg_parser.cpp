#include "arg_parser.hpp"

#include "CLI/CLI.hpp"
#include "preprocessor.hpp"

using namespace ftp;

Arg_parser::Arg_parser(CLI::App &_app)
{
    _app.require_subcommand(1);

    _app.footer({R"(Example:
    default at  listen port 2121, and will use port 2222: ' ./Mftp  '
    Set output log file: './Mftp --log '
    Backend work: ' ./Mftp --backend --log '
    )"});
    // sub commands
    m_ftp_cmds[0] = {"user", "User configurations"};
    m_ftp_cmds[1] = {"config", "FTP server configurations"};
    m_ftp_cmds[2] = {"port", "Set FTP control port, data port is that plus 1"};

    // options
    m_ftp_cmds[3] = {"-d,--dir,--directory", "FTP storage database directory"};
    _app.add_option(m_ftp_cmds[3].first, m_directroy, m_ftp_cmds[3].second);
    m_ftp_cmds[4] = {"--log", "Output a log file"};
    _app.add_option(m_ftp_cmds[4].first, m_Islog, m_ftp_cmds[4].second);
    m_ftp_cmds[5] = {"--backend", "FTP server run in the backend"};
    _app.add_option(m_ftp_cmds[5].first, m_Isbackend, m_ftp_cmds[5].second);

    for (int i = 0; i < 3; i++)
        _app.add_subcommand(m_ftp_cmds[i].first, m_ftp_cmds[i].second);
}

void Arg_handler(CLI::App &_app)
{
    if (_app.got_subcommand("user"))
    {
    }
    else if (_app.got_subcommand("config"))
    {
    }
    else if (_app.got_subcommand("port"))
    {
    }

    
}
