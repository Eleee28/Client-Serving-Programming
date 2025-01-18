# HTTP Server Project: Serving Files to a Browser

## Project Description
This project implements a basic HTTP server in C that serves files tp a web browser. The server listens for HTTP ``GET`` requests, locates the requested file, and sends it to the browser along with appropriate HTTP headers. If the file is not found, the server returns a custom ``404 Not Found`` error page.

## Features
- **File Serving**: Serves files from the local directory to web clients (e.g. browsers).
- **Custom 404 Error Page**: Returns an ``error.html`` file if the requested resource is not found.
- **Default File**: Serves ``index.html`` when the root path (``/``) is requested.
- **Dynamic Headers**: Generates HTTP headers based on the file size and status (``200 OK`` or ``404 Not Found``).
- **Browser Compatible**: Fully compatible with modern web browsers as clients.

## File Structure
- ``httpServerFile.c``: Contains the code for the HTTP server.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.
- ``index.html``: The default homepage served at ``/``.
- ``error.html``: The error page served for invalid or missing resources.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o httpServer httpServer.c DieWithMessage.c
~~~
This will generate an executable file: ``httpServer``.

## Usage Instructions

### Running the Server
The server needs to be run first. It listens on a specified port for incoming connections.
~~~ bash
./httpServer <serverPort>
~~~
- ``<serverPort>``: The port number on which the server will listen for incoming connections.

### Connecting via Browser
Once the server is running, open your web browser and enter the server's IP address and port in the address bar followed by the file path.
~~~bash
http://<serverIP>:<serverPort>/<filePath>
~~~
- ``<serverIP>``: The IP address of the server.
- ``<serverPort>``: The port number on which the server is listening.
- ``<filePath>``: The path of the file.


## Error Handling
The server handles errors gracefully, including:
- Missing command-line arguments
- Socket creation, binding or listening failures
- Missing or inaccessible files

## Limitations
- **Single-Threaded**: The server can only handle one client at a time.
- **Basic HTTP Parsing**: Only supports ``GET`` requests and simple parsing.
- **No MIME Type Support**: The server does not specify ``Content-Type`` headers based on file extensions.
- **Hardcoded Error Page**: Always servers the same ``error.html` for 404 errors.
