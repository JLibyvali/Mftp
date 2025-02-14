#include "Arg_parser.hpp"
#include "CLI/CLI.hpp"

int main(int argc, char *argv[])
{
    //------------------------------------------------------------------------------------------------------
    // CLI11 object features.
    //------------------------------------------------------------------------------------------------------
    CLI::App app("Mftp is a convenient FTP solution ");
    app.footer(R"(Example:
    ' ./Mftp  ', Default FTP server will listen at port 2121, and will use port 2222 to transcation data.
    './Mftp --log ', Set output log file.  
    ' ./Mftp --backend --log ', Backend work.  
    )");

    argv = app.ensure_utf8(argv);
    app.require_subcommand(1);

    ftp::ArgParser my_parser(app);
    my_parser.Arg_handler_set(app);

    CLI11_PARSE(app, argc, argv);

    return 0;
}