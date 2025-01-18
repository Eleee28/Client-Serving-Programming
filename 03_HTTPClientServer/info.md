# HTTP Client-Server Project

## Project Description
This project implements a basic HTTP server and client in C. The HTTP server listens for ``GET`` requests and responds with either an HTML "File Found" page or a "File Not Found" page based on the requested URL path. The HTTP client connects to the server, sends a ``GET`` request, and displays the server's response.

## Features
- **HTTP Server**: Listens for incoming HTTP ``GET`` requests and returns either a "200 File Found" or "404 File Not Found" HTML response.
- **HTTP Client**: Connects to the server, sends a ``GET`` request for a specified resource and displays the response.
- **Simple Routing**: Responds to requests for ``/index.html`` with a successful response and an HTML page. Any other path returns a 404 error page.
- **HTTP/1.1 Protocol**: Adheres to basic HTTP/1.1 headers in response.

## File Structure
- ``httpServer.c``: Contains the code for the HTTP server that listens for client connections, parses HTTP requests and sends appropriate HTML responses.
- ``httpClient.c``: Contains the code for the HTTP client that connects to the server, sends a ``GET`` request and displays the server`s response.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o httpServer httpServer.c DieWithMessage.c
gcc -o httpClient httpClient.c DieWithMessage.c
~~~
This will generate two executable files: ``httpServer`` and ``httpClient``.

## Usage Instructions

### Running the Server
The server needs to be run first. It listens on a specified port for incoming connections.
~~~ bash
./httpServer <serverPort>
~~~
- ``<serverPort>``: The port number on which the server will listen for incoming connections.

### Running the Client
Once the server is running, you can start the client by providing the server's IP address, the port number the server is listening on and the echo message.
~~~ bash
./httpClient <serverIP> <serverPort> <request>
~~~
- ``<serverIP>``: The IP address of the server.
- ``<serverPort>``: The port number on which the server is listening.
- ``<request>``: The GET request in correct format.

### Using the Browser
After running the server, you can connect to localhost on the specified port in the browser and send requests from the Browser.

## Error Handling
The programs implements basic error handling. If any system calls fail (e.g., socket creation, connection, ot data transmission), an error message will be printed, and the program will exit.

## Notes
- The server runs indefinitely, waiting for client connections. To stop the server, use ``Ctrl + C``.
- No multi-threading support in the server, it handles one client at a time
- It implements basic routing, it only recognizes requests for ``/index.html``.
- It only supports the ``GET`` method and simple parsing.
