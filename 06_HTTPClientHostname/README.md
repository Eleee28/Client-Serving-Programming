# HTTP Client Using Hostname

## Project Description
This project implements a simple HTTP client in C that connects to a server using its hostname and port. It sends an HTTP request provided as an argument and outputs the server's response to standard output.
The program demonstrates basic network programming concepts, including:
- Resolving hostnames usign ``getaddrinfo()``.

- Establishing a TCP connection to a server.

- Sending and receiving data over a socket.

## Features

- Resolves server hostname to an IP address using ``getaddrinfo()``.

- Establishes a TCP connection with the server.

- Sends an HTTP request to a server.

- Receives and displays the server's response.

## File Structure
- ``httpClientHostname.c``: Contains the implementations of the HTTP client.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o httpClientHostname httpClientHostname.c DieWithMessage.c
~~~
This will generate an executable file: ``httpClientHostname``.

## Usage Instructions

Run the program with the following syntax:
~~~bash
./httpClientHostname <serverAddress> <serverPort> <HTTPrequest>
~~~
**Arguments:**
- ``<serverAddress>``: The hostname or IP address of the server.

- ``<serverPort>``: The port number of the server.

- ``<HTTPrequest>``: The HTTP request string to sent to the server (e.g. ``GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n``)

## Error Handling
- The program handles errors during:

    - Hostname resolution with getaddrinfo().
    
    - Socket creation and connection.
    
    - Sending and receiving data over the network.

- Errors are displayed with descriptive messages.

## Limitations
- The HTTP request string must be properly formatted and include all required headers (e.g., ``Host``).

- The program does not handle HTTPS connections (TLS/SSL).

- The size of the receive buffer (``BUFSIZE``) may limit the amount of data received in a single read.
