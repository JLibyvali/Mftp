#include "Preprocessor.hpp"

//------------------------------------------------------------------------------------------------------
// Define and initialize these variable for Mftp.
//------------------------------------------------------------------------------------------------------
static const std::string                            base_dir{"~/.local/share/Mftp"};
static const std::array<std::string, FTP_FS_CMDNUM> fserver_cmd_text{"look",  "w",        "who",    "pwd",    "cd",
                                                                     "touch", "del",      "ls",     "mkdir",  "file",
                                                                     "cat",   "download", "upload", "logout", "q",
                                                                     "quit",  "exit"};
static const std::map<std::string, std::function<void(std::string_view)>> fserver_cmd;