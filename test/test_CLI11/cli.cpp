#include "CLI/CLI.hpp"

#include "cli.hpp"

#include <array>
#include <boost/core/noncopyable.hpp>
#include <iostream>
#include <memory>
#include <vector>

std::array<std::pair<std::string, std::string>, CMD_NUM> cli::subcmd_str{
    {{"List current config", "list"}, {"User manage", "user"}}
};

struct test_options
{
    std::string m_text;
    int         m_id;
};

class test_Subcmd final : private boost::noncopyable
{
public:
private:

    friend void               args_set(CLI::App &_app);
    std::array<CLI::App *, 1> m_list;
    test_options              m_options;
};

void args_set(CLI::App &_app)
{

    _app.footer("Custom footer");

    // test
    test_Subcmd test;

    test.m_list[0] = _app.add_subcommand("list", "List all information");
    test.m_list[0]->add_option("--text", test.m_options.m_text, "Test input text");
    test.m_list[0]->add_option("--id", test.m_options.m_id, "Test id ");
}

int main(int argc, char *argv[])
{
    CLI::App parameters{"Test CLI11 app description"};
    argv = parameters.ensure_utf8(argv);

    args_set(parameters);
    CLI11_PARSE(parameters, argc, argv);
}
