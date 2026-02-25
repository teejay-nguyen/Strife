#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main() {
    boost::asio::io_context io;
    tcp::socket socket(io);

    socket.connect({boost::asio::ip::make_address("127.0.0.1"), 5555});

    std::cout << "Connected!\n";

    while (true) {
        std::string msg;
        std::getline(std::cin, msg);
        msg += "\n";
        boost::asio::write(socket, boost::asio::buffer(msg));
    }
}