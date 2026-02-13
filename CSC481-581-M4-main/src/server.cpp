#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// variable for parameter to be used in context creation call
#define THREADS 1

void reply_handler() {
    // Create the context with appropriate number of threads
	zmq::context_t context(THREADS);
    
    // Create a req-rep socket for communication
    zmq::socket_t socket(context, zmq::socket_type::rep);
    socket.bind("tcp://localhost:5555");
    
    // Bind the socket to a local host port(same as client's)
    std::cout << "Waiting for Client to send a message" <<std::endl;
    while (true) {
	// Recieve the message from the client in the socket
	
	// Retrieve the message and convert to string and print to console 
	
	// Construct a ZMQ message from a string and reply on the socket 
        std::string reply_str = "Hello Client";
    }
    // Close the socket and context after use
}

void pub_handler() {
    // Create the context with appropriate number of threads
    zmq::context_t context(THREADS);
    
    // Create a pub-sub socket for communication
    zmq::socket_t socket(context, zmq::socket_type::sub);
    socket.bind("tcp://localhost:5555");
    
    // Bind the socket to a local host port(same as client's)
    std::cout << "Waiting to publish messages" << std::endl;
    while (true) {
	// After a certain number of iterations publish a message
	
	// Construct a ZMQ message from a string and publish it to the socket  
        std::string update = "Message #"; 
    }
    // Close the socket and context after use
}

int main() {
    std::cout<< "The server has started up..."<< std::endl;
    
    // Choosing the type of messaging pattern the server is using
    std::cout << "Choose mode: 1 = Request-Reply, 2 = Subscribe\n> ";
    int mode;
    std::cin >> mode;

    if (mode == 1) {
	reply_handler();
    } 
    else if (mode == 2) {
	pub_handler();
    }    return 0;
}
