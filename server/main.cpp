#include <iostream>
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

class ChatSession : public std::enable_shared_from_this<ChatSession> {
public:
    ChatSession(tcp::socket socket) : socket_(std::move(socket)) {}

    void start() {
        std::cout << "Client joined the chat." << std::endl;
        do_read();
    }

private:
    tcp::socket socket_;
    boost::asio::streambuf buffer_;

    void do_read() {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_, buffer_, "\n",
            [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                if (!ec) {
                    std::istream input(&buffer_);
                    std::string message;
                    std::getline(input, message);
                    std::cout << "Received message: " << message << std::endl;
                    do_read();
                }
            }
        );
    }
};

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io, short port) : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

private:
    tcp::acceptor acceptor_;

    void do_accept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<ChatSession>(std::move(socket))->start();
                }
                do_accept();
            }
        );
    }
};

int main() {
    boost::asio::io_context io;
    ChatServer server(io, 5555);
    io.run();
}