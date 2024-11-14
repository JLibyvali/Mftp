#include "arg_parser.hpp"

#include "CLI/CLI.hpp"
#include "preprocessor.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <map>
#include <string>
#include <string_view>

using namespace ftp;

// some string initial
static const std::string                            base_dir{"~/.local/share/Mftp"};
static const std::array<std::string, FTP_FS_CMDNUM> fs_cmd_text{"look",   "w",      "who",   "pwd",  "cd",  "touch",
                                                                "del",    "ls",     "mkdir", "file", "cat", "download",
                                                                "upload", "logout", "q",     "quit", "exit"};
static const std::map<std::string, std::function<void(std::string_view)>> fs_cmd;

Arg_parser::Arg_parser(CLI::App &_app)
{
    // Arguments base configurations
    // _app.require_subcommand(1);
    _app.footer({R"(Example:
    default at  listen port 2121, and will use port 2222: ' ./Mftp  '
    Set output log file: './Mftp --log '
    Backend work: ' ./Mftp --backend --log '
    )"});

    // Init subcommand and options text
    m_cmdtext[0]     = {"user", "User configurations"};
    m_cmdtext[1]     = {"config", "FTP server configurations"};
    m_cmdtext[2]     = {"--port", "Set FTP control port, data port is that plus 1"};
    m_cmdtext[3]     = {"-d,--dir,--directory", "FTP storage database directory"};
    m_cmdtext[4]     = {"--log", "Output a log file"};
    m_cmdtext[5]     = {"--backend", "FTP server run in the backend"};

    // add to _app
    m_ftp_user_cmd   = _app.add_subcommand(m_cmdtext[0].first, m_cmdtext[0].second);
    m_ftp_config_cmd = _app.add_subcommand(m_cmdtext[1].first, m_cmdtext[1].second);
    m_ftp_options.M_opts.push_back(_app.add_option(m_cmdtext[2].first, m_ftp_options.m_cport, m_cmdtext[2].second));
    m_ftp_options.M_opts.push_back(_app.add_option(m_cmdtext[3].first, m_ftp_options.m_directroy, m_cmdtext[3].second));
    m_ftp_options.M_opts.push_back(_app.add_option(m_cmdtext[4].first, m_ftp_options.m_Islog, m_cmdtext[4].second));
    m_ftp_options.M_opts.push_back(_app.add_option(m_cmdtext[5].first, m_ftp_options.m_Isbackend, m_cmdtext[5].second));
    std::for_each(
        m_ftp_options.M_opts.begin(), m_ftp_options.M_opts.end(),
        [&](CLI::Option *_opt_ptr) { _opt_ptr->capture_default_str(); }
    );

    // add user's options
    m_user.M_opts.push_back(
        m_ftp_user_cmd->add_option("--list", m_user.m_list, "list all users information or specific user configs")
    );
    m_user.M_opts.push_back(m_ftp_user_cmd->add_option("--add", m_user.m_add, "add account with given username"));
    m_user.M_opts.push_back(m_ftp_user_cmd->add_option("--del", m_user.m_del, "delete the username account"));
    m_user.M_opts.push_back(m_ftp_user_cmd->add_option("--set", m_user.m_set, "set username account's privilege"));
    m_user.M_opts.push_back(
        m_ftp_user_cmd->add_option("--anonymous", m_user.m_anonymous, "Anonymous users configurations")
    );

    // add config's options
    m_config.M_opts.push_back(m_ftp_config_cmd->add_option("--space", m_config.m_space, "data directory information"));
    m_config.M_opts.push_back(
        m_ftp_config_cmd->add_option("--telnet", m_config.m_telnet, "enable telnet mode, default ON")
    );
    m_config.M_opts.push_back(
        m_ftp_config_cmd->add_option("--database", m_config.m_database, "entering the database control")
    );
    m_config.M_opts.push_back(
        m_ftp_config_cmd->add_option("--console", m_config.m_console, "Entering ftp server console")
    );
    m_config.M_opts.push_back(
        m_ftp_config_cmd->add_option("--port", m_config.port, "default console port and data port: 2121 2222")
    );
}

void ftp::Arg_parser::Arg_handler_set(CLI::App &_app)
{
    // add callback
    m_ftp_user_cmd->callback(user_interface);
    m_ftp_config_cmd->callback(config_interface);
}
