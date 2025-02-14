/**
 * @file Preprocessor.hpp
 * @author Jlibyvali
 * @brief This file aimed to collect all `macro` and `Global variable` declaration here, for better manage.
 * The define and initialization work will be done in `init.cpp`.
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "Config.hpp"
#include "User.hpp"

#include <array>
#include <functional>
#include <map>
#include <string>
#include <string_view>

namespace ftp
{

#define FTP_CMDTEXT_LEN 50  // The Mftp program all arguments size, when used in cli.
#define FTP_FS_CMDNUM   17  // FTP-server commands num.
#define FTP_SUBCMD_NUM  2
#define FTP_OPT_NUM     4

/**
 * @brief The Mftp program configuration home in `~/.local/share/Mftp`.
 */
static const std::string                                                  base_dir;

/**
 * @brief FTP server commands name string array.
 */
static const std::array<std::string, FTP_FS_CMDNUM>                       fserver_cmd_text;

/**
 * @brief FTP server commands name-function map.
 */
static const std::map<std::string, std::function<void(std::string_view)>> fserver_cmd;

// class for parse program arguments.
class ArgParser;

// class fot user subcommand interface
void user_interface();
class User;

// class for config subcommand interface
void config_interface();
class Config;

}  // namespace ftp