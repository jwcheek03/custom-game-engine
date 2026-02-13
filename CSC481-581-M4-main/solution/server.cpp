#include <zmq.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#define THREADS 1

void reply_handler() {
    zmq::context_t context(THREADS);
    zmq::socket_t responder(context, zmq::socket_type::rep);
    responder.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;
        responder.recv(request, zmq::recv_flags::none);

        std::string request_str(static_cast<char*>(request.data()), request.size());
        std::cout << "Received request from client: " << request_str << std::endl;

        std::string reply_str = "Hello Client";
        zmq::message_t reply(reply_str.size());
        memcpy(reply.data(), reply_str.data(), reply_str.size());
        responder.send(reply, zmq::send_flags::none);
    }
    responder.close();
    context.close();
}

void pub_handler() {
    zmq::context_t context(THREADS);
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind("tcp://*:5556");
    int count = 0;
    while (true) {
	std::this_thread::sleep_for(std::chrono::seconds(3));
        std::string update = "Message #" + std::to_string(count);
	count = ++count;
        zmq::message_t message(update.size());
        memcpy(message.data(), update.data(), update.size());
        publisher.send(message, zmq::send_flags::none);
        std::cout << "Published: " << update << std::endl;
    }
    publisher.close();
    context.close();
}

int main() {
    std::cout << "Choose a mode: 1:Request-Reply, 2:Subscribe\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        reply_handler();
    } 
    else if (mode == 2) {
        pub_handler();
    }

    return 0;
}
