#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

void request_client() {
    zmq::context_t context;
    zmq::socket_t requester(context, zmq::socket_type::req);
    requester.connect("tcp://localhost:5555");
    
    while(true){
	std::string req_string;
	std::cout << "\n>Enter message to send: ";
	std::cin.ignore();
	std::getline(std::cin,req_string);

	zmq::message_t request(req_string.size());
	memcpy(request.data(),req_string.data(), req_string.size());
	requester.send(request, zmq::send_flags::none);

	zmq::message_t reply;
	requester.recv(reply, zmq::recv_flags::none);
	std::string reply_str(static_cast<char*>(reply.data()), reply.size());
	std::cout << "Received reply from server: " << reply_str << std::endl;
    }
    requester.close();
    context.close();
}

void subscribe_client() {
    zmq::context_t context;
    zmq::socket_t subscriber(context, zmq::socket_type::sub);
    subscriber.connect("tcp://localhost:5556");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "Message", 7);

    std::cout << "Subscribed to updates...\n";
    while (true) {
        zmq::message_t update;
        subscriber.recv(update, zmq::recv_flags::none);
        std::string update_str(static_cast<char*>(update.data()), update.size());
        std::cout << "Received: " << update_str << std::endl;
    }
    subscriber.close();
    context.close();
}

int main() {
    std::cout << "Choose a mode: 1:Request-Reply, 2:Subscribe\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
        request_client();
    } 
    else if (mode == 2) {
        subscribe_client();
    }

    return 0;
}
