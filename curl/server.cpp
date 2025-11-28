#include <iostream>
#include <asio.hpp>
using asio::ip::tcp;

int main() {
    asio::io_context io;
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
    std::cout << "Server online on port 8080\n";

    for (;;) {
        tcp::socket socket(io);
        acceptor.accept(socket);
        std::string msg = "Hello from Render C++ server!\n";
        asio::write(socket, asio::buffer(msg));
    }
}
