

# It's About Sending a Message ✉️
In this class assignment, you'll build client and server applications that will communicate with each other using Request-Response and Publish-Subscriber models of messaging.

You will be building this minimal C++ messaging application using [cppzmq](https://github.com/zeromq/zmqpp), the C++ bindings for ZeroMQ.  

##  Objectives
Construct a simple application which sends messages between a client application and a locally hosted server application

- Clone the repository  
- Ensure the repository compiles  
- Implement a reply-request messaging pattern  
      - The client should initiate the request  
      - The server should reply  
- Implement a publish-subscribe messaging pattern  
      - The server should publish updates  
      - The client should subscribe to the server’s updates
 
## Setup Instructions
Follow these steps to clone, build, and run the project on your machine:

### 1. Clone the repository
```bash
git clone https://github.com/AlexanderCard/CSC481-581-M4.git
cd CSC481-581-M4
```
### 2. Install ZeroMQ
You must first install the ZeroMQ library (libzmq):
You only need the header file zmq.hpp (no compiled binaries). 

You can install via package manager or clone directly.

**On macOS (Homebrew):**
```bash
brew install zeromq
brew install cppzmq
```
**On Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libzmq3-dev
```
**On Arch Linux:**
```bash
sudo pacman -S zeromq cppzmq
```
**On Windows:**

Option 1: Use vcpkg
```bash
vcpkg install zeromq
vcpkg install cppzmq
```
Option 2: Cloning the repository
```bash
git clone https://github.com/zeromq/cppzmq.git
cd cppzmq
```
 Copy zmq.hpp to your include path
 
 Note: cppzmq requires ZeroMQ to be installed.

### 3. Build & Run
Build the project
```bash
mkdir build && cd build
cmake ..
make
```
Run the server
```bash
./server
```
Run the client
```bash
./client
```
The client and server prompt you to choose a mode:
```bash
Choose mode: 1 = Request-Reply, 2 = Subscribe
```
If you see this console log, then you have successfully installed ZeroMQ and built the repository.
## Core Concepts
### 1. Request-Reply (REQ/REP)
A client sends a message to the server, and the server sends a reply back.

Used in RPC-style communication: one client, one response. Like web brower <-> web server, app <-> weather api.

Your implementation:
```
Server uses zmq::socket_type::rep
Client uses zmq::socket_type::req
Connects via TCP at tcp://localhost:5555
```
### 2. Publish-Subscribe (PUB/SUB)
The server pushes messages to all connected subscribers.
Clients subscribe to topics (e.g., "update") and receive only matching messages.
Ideal for broadcasting events like logs, updates, or market data.

Your implementation:
```
Server uses zmq::socket_type::pub
Client uses zmq::socket_type::sub
Server publishes every few seconds to tcp://localhost:5556
```
### 3. **What is a 0MQ Context?**

A **ZeroMQ context** is like the environment or container where all sockets live. It manages resources, I/O threads, and internal state for all sockets created from it.
Every ZeroMQ application must create a context first, sockets cannot be created without it.

### Syntax:
```cpp
zmq::context_t  context(1); // 1 is the number of I/O threads
```
**Note:**  The number `1` refers to the number of I/O threads used internally. You won't need more than 1 for basic messaging apps like this assignment.

### 4. **What is a 0MQ Socket?**
A **ZeroMQ socket** is an abstraction over traditional sockets. It's how you send/receive data. Unlike raw TCP sockets, ZeroMQ sockets are categorized into different **types** like:

-   `zmq::socket_type::req` (Request)
    
-   `zmq::socket_type::rep` (Reply)
    
-   `zmq::socket_type::pub` (Publisher)
    
-   `zmq::socket_type::sub` (Subscriber)

### Creating and Binding a Socket on Server:
```cpp
zmq::socket_t socket(context, zmq::socket_type::rep);
socket.bind("tcp://localhost:5555"); 
// Binds to port 5555 on localhost interface
```
### Connecting from client:
```cpp
zmq::socket_t  socket(context, zmq::socket_type::req);
socket.connect("tcp://localhost:5555");
```
**Note:**
-   `.bind()` is used on the **server** side (listens for connections).
-   `.connect()` is used on the **client** side (initiates connection).

### 5. **What is a Message?**
A **ZeroMQ message** is a lightweight container for sending or receiving data. You can send/receive strings, binary blobs, or game objects.

#### Constructing a Message from a String:

```cpp
std::string text = "Hello World!"; 
zmq::message_t  message(text.size()); 
memcpy(message.data(), text.data(), text.size());
```
Or a cleaner syntax using constructor:

```cpp
zmq::message_t  message(text.begin(), text.end());
```
#### Sending the Message:

```cpp
socket.send(message, zmq::send_flags::none); 
```
#### Receiving a Message:

```cpp
zmq::message_t reply;
socket.recv(reply, zmq::recv_flags::none); 
std::string reply_str(static_cast<char*>(reply.data()), reply.size());
```
**Note:**
-   `recv` and `send` are blocking by default.
-   `zmq::recv_flags::none` means wait until message is available.

## Helpful Resources
[ZeroMQ Docs](https://zguide.zeromq.org/)

[ZeroMQ API reference](https://brettviren.github.io/zio/doxy/html/index.html)

## Final Output
<img src="https://github.com/ATHARVA47/CSC481-581_Sending_A_Message/blob/master/media/output.png"/>

## Final Notes
This assignment is your introduction to networking with ZeroMQ, you understand this code and adapt this appropriately for adding networking support to your game engine.
