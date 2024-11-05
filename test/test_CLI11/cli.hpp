#pragma once

#include "CLI/CLI.hpp"

#include <array>
#include <string>
#include <utility>

#define CMD_NUM 2

namespace cli
{


extern std::array<std::pair<std::string, std::string>, CMD_NUM> subcmd_str;
extern std::array<CLI::App_p, CMD_NUM>                            subcmd;


};  // namespace cli
