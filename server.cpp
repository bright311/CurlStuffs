#include <asio.hpp>
#include <iostream>
#include <cstdlib>

using asio::ip::tcp;

int main() {
    try {
        asio::io_context io;

        int port = std::atoi(std::getenv("PORT")); // Render PORT
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));

        std::cout << "Listening on port " << port << std::endl;

        for (;;) {
            tcp::socket socket(io);
            acceptor.accept(socket);
            std::string msg = "Hello from C++ server\n";
            asio::write(socket, asio::buffer(msg));
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
