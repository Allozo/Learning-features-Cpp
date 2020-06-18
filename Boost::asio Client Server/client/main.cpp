#include <iostream>
#include <boost/asio.hpp>
#include <thread>

//// Клиент

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

void client() {
    std::string ip_address = "127.0.0.1";
    auto port = 8001;

    try {
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_address), port);
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
        socket.connect(endpoint);

        std::thread(read_message, std::ref(socket)).detach();


        // пользователь вводит своё имя
        std::cout << "Input your name: ";
        std::string name = "Anna";
        std::getline(std::cin, name);

        std::string text;
        while (std::getline(std::cin, text)) {
            std::string message = name + ":" + text + '\n';
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    client();
    return 0;
}