#pragma once
#include "Config.hpp"
#include "User.hpp"

#include <array>
#include <functional>
#include <map>
#include <string>
#include <string_view>

/**
 * @brief Interface file include almost class
 *
 */

namespace ftp
{

// class for parse program arguments
#define FTP_CMDTEXT_LEN 50
#define FTP_SUBCMD_NUM  2
#define FTP_OPT_NUM     4
#define FTP_FS_CMDNUM   17
static const std::string                                                  base_dir;
static const std::array<std::string, FTP_FS_CMDNUM>                       fs_cmd_text;
static const std::map<std::string, std::function<void(std::string_view)>> fs_cmd;
class Arg_parser;

// class fot user subcommand interface
void user_interface();
class User;

// class for config subcommand interface
void config_interface();
class Config;

}  // namespace ftp