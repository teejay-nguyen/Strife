#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io;

        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 5555));

        std::cout << "Server listening on port 5555..." << std::endl;

        while (true) {
            tcp::socket socket(io);
            acceptor.accept(socket);

            std::cout << "Client connected." << std::endl;
        }
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}