# TCP Client-Server Date Time Communication

## Project Description
These project consists of two simple C programs that implement TCP client and server. The server listens on a specified port for incoming connections and, after a successful connection, sends a welcome message with the current date and time. The client connects to the server, receives the message, and displays it.

### Features
- **Server Program**: Accepts incoming TCP connections and send the current date and time along with a custom message.
- **Client Program**: Connects to the server, receives the message, and displays it on the console.

## File Structure
- ``daytimeServer.c``: The TCP server implementation.
- ``daytimeClient.c``: The TCP client implementation.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o daytimeServer daytimeServer.c DieWithMessage.c
gcc -o daytimeClient daytimeClient.c DieWithMessage.c
~~~
This will generate two executable files: ``daytimeServer`` and ``daytimeClient``.

## Usage Instructions
### Running the Server
The server needs to be run first. It listens on a specified port for incoming connections.
~~~ bash
./daytimeServer <serverPort>
~~~
- ``<serverPort>``: The port number on which the server will listen for incoming connections.

### Running the Client
Once the server is running, you can start the client by providing the server's IP address and the port number the server is listening on.
~~~ bash
./daytimeClient <serverIP> <serverPort>
~~~
- ``<serverIP>``: The IP address of the server.
- ``<serverPort>``: The port number on which the server is listening.

## Error Handling
The programs implement robust error handling. If any system calls faill (e.g., socket creation, connection, ot data transmission), an error message will be printed, and the program will exit.

## Customization
- You can modify the welcome message in the ``daytimeServer.c`` file inside the ``snprintf`` function.
- The buffer size (``BUFSIZE``) and maximum pending connections (``MAXPENDING``) are defined in the source files and can be adjusted based on your requirements.

## Notes
- The server runs indefinitely, waiting for client connections. To stop the server, use ``Ctrl + C``.
- Make sure the server's port is open and not blocked by a firewall for remote connections.
