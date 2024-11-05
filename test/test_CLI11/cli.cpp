#include "CLI/CLI.hpp"

#include "cli.hpp"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

std::array<std::pair<std::string, std::string>, CMD_NUM> cli::subcmd_str{
    {{"List current config", "list"}, {"User manage", "user"}}
};

std::array<CLI::App_p, CMD_NUM> cli::subcmd;

void                            args_handle(CLI::App &_parm)
{
    _parm.require_option(1);
    _parm.footer("Custom footer");

    // Add all subcommand to app
    for (int i = 0; i < CMD_NUM; i++)
    {
        cli::subcmd[i] = std::make_shared<CLI::App>(cli::subcmd_str[i].first, cli::subcmd_str[i].second);
        _parm.add_subcommand(cli::subcmd[i]);
    }

    // Set list
    std::string what;
    cli::subcmd[0]->usage("list <WHAT>");
    cli::subcmd[0]->add_option("--what", what, "List what config");
    cli::subcmd[0]->require_option(1);
    // Set user
    std::string user;
    std::string passwd;
    cli::subcmd[1]->usage("user [--user] [--passwd]");
    cli::subcmd[1]->add_option("--user", user, "User information");
    cli::subcmd[1]->add_option("--passwd", passwd, "Password");
    cli::subcmd[1]->require_option(1);
    // Set config
    _parm.set_config("--config", "Mftp.in", "Config of Mftp");
    _parm.allow_config_extras(true);
}

int main(int argc, char *argv[])
{
    CLI::App parameters{"Mftp description"};
    argv = parameters.ensure_utf8(argv);
    args_handle(parameters);
    CLI11_PARSE(parameters, argc, argv);
}
