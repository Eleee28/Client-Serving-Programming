# HTTP Server with Client Address Logging

## Project Description
The ``cliaddrNetstat`` program is a basic HTTP server written in C that listens on a specified port and serves simple HTTP responses. It has been modified to capture and log client addressing information, such as the client's IP address and port number, during each connection.

## Features

1. **Client Address Logging:**

    - Captures the IP address and port of every connected client.
    
    - Logs the client address information in the console.

2. **HTTP Request Handling:**

    - Processes basic HTTP ``GET`` requests.
    
    - Serves a pre-defined "File Found" page for recognized paths (``/index.html`` or ``/``).
    
    - Responds with a "File Not Found" page for unrecognized paths.

3. **Connection Management:**

    - Accepts multiple client connections in a loop.
    
    - Closes each client connection after handling the request.

## File Structure
- ``cliaddrNetstat.c``: Contains the implementations of the HTTP server.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o cliaddrNetstat cliaddrNetstat.c DieWithMessage.c
~~~
This will generate an executable file: ``cliaddrNetstat``.

## Usage Instructions

Run the program with the following syntax:
~~~bash
./cliaddrNetstat <serverPort>
~~~
**Argument:**

- ``<serverPort>``: The port number on which the server listens for incoming connections.

## Error Handling
The server provides descriptive error messages for issues such as:

    - Failure in socket creation, binding, or listening.
    
    - Problems during data transmission or reception.

The server exits gracefully in case of fatal errors.

## Limitations
- Single-threaded: Processes one client connection at a time.

- Serves only predefined static HTML responses.

- Lacks support for HTTPS (TLS/SSL).