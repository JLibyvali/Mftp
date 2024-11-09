#include "CLI/CLI.hpp"
#include "arg_parser.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    // parse input arguments
    CLI::App app("Mftp is a convenient FTP solution way");
    argv = app.ensure_utf8(argv);
    
    ftp::Arg_parser test(app);
    CLI11_PARSE(app, argc, argv);
    ftp::Arg_handler(app);

    return 0;
}