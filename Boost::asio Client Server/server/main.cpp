#include <iostream>
#include <boost/asio.hpp>
#include <thread>

//// Сервер

std::pair<std::string, std::string> get_name_and_message(const std::string &text) {
    std::string name;
    std::string message;

    bool flag_name = true;
    for (char i : text) {
        if (flag_name) {
            if (i != ':') {
                name += i;
            } else {
                flag_name = false;
            }
        } else {
            message += i;
        }
    }
    return std::make_pair(name, message);
}

void read_message(boost::asio::ip::tcp::socket &socket) {
    try {
        boost::asio::streambuf buffer;
        std::string text;
        while (boost::asio::read_until(socket, buffer, '\n')) {
            std::istream stream(&buffer);
            getline(stream, text);
            auto value = get_name_and_message(text);
            std::cout << value.first << ": " << value.second << std::endl;
        }

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void client_session(boost::asio::ip::tcp::socket sock) {
    try {
        std::thread(read_message, std::ref(sock)).detach();

        std::string name = "Server";
        std::string text;
        while (std::getline(std::cin, text)) {
            std::string message = name + ":" + text + '\n';
            boost::asio::write(sock, boost::asio::buffer(message));
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void server() {
    boost::asio::io_service service;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 8001);

    boost::asio::ip::tcp::acceptor acc(service, ep.protocol());
    acc.bind(ep);
    acc.listen();

    while (true) {
        auto sock = boost::asio::ip::tcp::socket(service);
        acc.accept(sock);
        std::thread(client_session, std::move(sock)).detach();
    }
}

int main() {
    server();
    return 0;
}