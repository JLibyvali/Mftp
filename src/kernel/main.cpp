#include "CLI/CLI.hpp"
#include "Arg_parser.hpp"


int main(int argc, char *argv[])
{
    // parse input arguments
    CLI::App app("Mftp is a convenient FTP solution ");
    argv = app.ensure_utf8(argv);

    ftp::Arg_parser my_parser(app);
    my_parser.Arg_handler_set(app);
    
    CLI11_PARSE(app, argc, argv);

    return 0;
}