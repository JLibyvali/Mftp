#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <filesystem>
#include <format>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cout << std::format("Usage {} <PORT> \n", argv[0]) << std::endl;
        return 1;
    }

    boost::asio::io_service ser;
    

    return 0;
}