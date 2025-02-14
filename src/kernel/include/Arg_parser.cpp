#include "Arg_parser.hpp"

#include "CLI/CLI.hpp"
#include "Preprocessor.hpp"

#include <algorithm>
#include <array>
#include <functional>
#include <string>

using namespace ftp;

ArgParser::ArgParser(CLI::App &_app)
{
    // CLI11 commands and subcommands based on `CLI11::App` object, and the name should not begin with `--xxx`,
    // But Any option name must begin with `--xxx`.
    m_cmdtext[0]      = {"user", "User configurations"};
    m_cmdtext[1]      = {"config", "FTP server configurations"};
    m_cmdtext[2]      = {"--port", "Set FTP control port, data port is that plus 1"};
    m_cmdtext[3]      = {"-d,--dir,--directory", "FTP storage database directory"};
    m_cmdtext[4]      = {"--log", "Output a log file"};
    m_cmdtext[5]      = {"--backend", "FTP server run in the backend"};

    // Add commands text to _app object.
    m_ftp_user_cmds   = _app.add_subcommand(m_cmdtext[0].first, m_cmdtext[0].second);
    m_ftp_config_cmds = _app.add_subcommand(m_cmdtext[1].first, m_cmdtext[1].second);

    m_ftp_options.m_program_opts.push_back(
        _app.add_option(m_cmdtext[2].first, m_ftp_options.m_cport, m_cmdtext[2].second)
    );
    m_ftp_options.m_program_opts.push_back(
        _app.add_option(m_cmdtext[3].first, m_ftp_options.m_datadir, m_cmdtext[3].second)
    );
    m_ftp_options.m_program_opts.push_back(
        _app.add_option(m_cmdtext[4].first, m_ftp_options.m_Islog, m_cmdtext[4].second)
    );
    m_ftp_options.m_program_opts.push_back(
        _app.add_option(m_cmdtext[5].first, m_ftp_options.m_Isbackend, m_cmdtext[5].second)
    );

    std::for_each(
        m_ftp_options.m_program_opts.begin(), m_ftp_options.m_program_opts.end(),
        [&](CLI::Option *_opt_ptr) { _opt_ptr->capture_default_str(); }
    );

    // add user subcommand options.
    m_user.m_user_opts.push_back(
        m_ftp_user_cmds->add_option("--list", m_user.m_list, "list all users information or specific user configs")
    );
    m_user.m_user_opts.push_back(m_ftp_user_cmds->add_option("--add", m_user.m_add, "add account with given username"));
    m_user.m_user_opts.push_back(m_ftp_user_cmds->add_option("--del", m_user.m_del, "delete the username account"));
    m_user.m_user_opts.push_back(m_ftp_user_cmds->add_option("--set", m_user.m_set, "set username account's privilege")
    );
    m_user.m_user_opts.push_back(
        m_ftp_user_cmds->add_option("--anonymous", m_user.m_anonymous, "Anonymous users configurations")
    );

    // add config subcommand options.
    m_config.m_config_opts.push_back(
        m_ftp_config_cmds->add_option("--space", m_config.m_space, "data directory information")
    );
    m_config.m_config_opts.push_back(
        m_ftp_config_cmds->add_option("--telnet", m_config.m_telnet, "enable telnet mode, default ON")
    );
    m_config.m_config_opts.push_back(
        m_ftp_config_cmds->add_option("--database", m_config.m_database, "entering the database control")
    );
    m_config.m_config_opts.push_back(
        m_ftp_config_cmds->add_option("--console", m_config.m_console, "Entering ftp server console")
    );
    m_config.m_config_opts.push_back(
        m_ftp_config_cmds->add_option("--port", m_config.port, "default console port and data port: 2121 2222")
    );
}

void ftp::ArgParser::Arg_handler_set(CLI::App &_app)
{
    // Check: https://github.com/CLIUtils/CLI11/tree/main/examples/subcom_in_files
    m_ftp_user_cmds->callback(user_interface);
    m_ftp_config_cmds->callback(config_interface);
}
