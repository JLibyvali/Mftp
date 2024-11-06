#include "asio.hpp"

#include <iostream>

using tcp_socket = asio::ip::tcp::socket;
using addr_type  = asio::ip::address;
using port_type  = asio::ip::port_type;

int main()
{
    // io_context
    /// Single io_context, single thread
    asio::io_context io;
    tcp_socket       sock1(io);
    tcp_socket       sock2(io);

    return 0;
}