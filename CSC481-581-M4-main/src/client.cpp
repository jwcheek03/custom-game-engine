#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

// variable for parameter to be used in context creation call
# define THREADS 1

void request_client() {
    // Create the context with appropriate number of threads
    zmq::context_t context(THREADS);
    
    // create a req-rep socket for communication
    
    // bind the socket to a local host port(same as server's)
    
    std::cout << "\nWaiting to send a request to the server" << std::endl; 
    while(true){
	// String to send as request to the server
	std::string req_string;
	// Create a zmq message with the above string 
	zmq::message_t reply;
	// Recieve message from the socket and print to console
    }
    // Close the socket and context after use
}

void subscribe_client() {
    // Create the context with appropriate number of threads
    zmq::context_t context(THREADS);
    
    // create a pub-sub socket for communication
    
    // bind the socket to a local host port(same as publisher's)

    std::cout << "\nSubscribed to updates...\n";
    while (true) {
	// Recieve a message from the publisher
	
	// Retrieve the message and convert to string
	
	// Print the message to console
	std::string pub_string;
    }
    // Close the socket and context after use
}

int main() {
    // Choosing the type of messaging pattern the client is using
    std::cout << "Choose mode: 1 = Request-Reply, 2 = Subscribe\n> ";
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
