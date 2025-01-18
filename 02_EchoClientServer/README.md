# Echo Client-Server Project

## Project Description
This project implements a simple TCP Echo Client-Server system. The Echo Server listens for incoming TCP connections, receives messages from clients, and sends the same message back to the client. The Echo Client connects to the server, sends a message, and displays the echoed message received from the server.

## Features
- **Echo Server**: Receives a message from the client, displays it and sends it back.
- **Echo Client**: Connects to the server, sends a message and prints the echoed message.

## File Structure
- ``echoServer.c``: Contains the code for the server that listens for client connections and echoes back messages.
- ``echoClient.c``: Contains the code for the client that connects to the server, sends a message and prints the echoed message.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o echoServer echoServer.c DieWithMessage.c
gcc -o echoClient echoClient.c DieWithMessage.c
~~~
This will generate two executable files: ``echoServer`` and ``echoClient``.

## Usage Instructions

### Running the Server
The server needs to be run first. It listens on a specified port for incoming connections.
~~~ bash
./echoServer <serverPort>
~~~
- ``<serverPort>``: The port number on which the server will listen for incoming connections.

### Running the Client
Once the server is running, you can start the client by providing the server's IP address, the port number the server is listening on and the echo message.
~~~ bash
./echoClient <serverIP> <serverPort> <message>
~~~
- ``<serverIP>``: The IP address of the server.
- ``<serverPort>``: The port number on which the server is listening.
- ``<message>``: The message to be echoed.

## Error Handling
The programs implement robust error handling. If any system calls fail (e.g., socket creation, connection, ot data transmission), an error message will be printed, and the program will exit.

## Notes
- The server runs indefinitely, waiting for client connections. To stop the server, use ``Ctrl + C``.
- No multi-threading support in the server, it handles one client at a time.
