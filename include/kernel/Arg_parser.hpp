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

struct UserCommands
{
    std::string                m_list, m_add, m_del, m_set, m_anonymous;
    std::vector<CLI::Option *> m_user_opts;
};

struct ConfigCommands
{
    std::size_t                m_space;
    bool                       m_telnet, m_database, m_console;
    std::size_t                port;

    std::vector<CLI::Option *> m_config_opts;
};

struct ProgramOptions
{

    std::string                m_datadir{base_dir + R"(/data)"};
    /**
     * @brief Is generate Log file? Is Mftp running in backend.
     */
    bool                       m_Islog{false}, m_Isbackend{false};
    std::size_t                m_cport{2121}, m_dport{2222};

    /**
     * @brief Storage all Mftp program options via CLI11.
     */
    std::vector<CLI::Option *> m_program_opts;
};

/**
 * @brief This class responsible for all arguments pares.
 * CLI11 reference: https://cliutils.github.io/CLI11/book/chapters/options.html.
 */
class ArgParser final : private boost::noncopyable

{
public:

    /**
     * @brief Construct a new Arg_parser object, and will initialize some comands in ctor.
     *
     * @param _app The first CLI::APP object declared in `main()` function.
     */
    explicit ArgParser(CLI::App &_app);
    ~ArgParser() = default;

    void Arg_handler_set(CLI::App &_app);

private:

    /**
     * @brief cmd_text the map `<commands name, commands description>` of Mftp program.
     */
    using cmd_text = std::pair<std::string, std::string>;
    std::array<cmd_text, FTP_CMDTEXT_LEN> m_cmdtext;

    /**
     * @brief MFtp `User` and `Config` Subcommand via CLI11::App type.
     */
    CLI::App                             *m_ftp_user_cmds, *m_ftp_config_cmds;
    ProgramOptions                        m_ftp_options;

    // User Config subcommand
    UserCommands                          m_user;
    ConfigCommands                        m_config;
};

}  // namespace ftp
