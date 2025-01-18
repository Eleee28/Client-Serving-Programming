# Address Utility and GteAddrInfo Project

## Project Description
This project contains two utilities implemented in C:

1. **AddressUtility**:
    - A utility for working with socket addresses.

    - Provides functionality to print socket addresses and compare two socket addresses for equality.

2. **GetAddrInfo**:
    - A utility to resolve a hostname and service into a list of socket addresses using the ``getaddrinfo()`` system call.

    - Prints the resolved addresses to standard output.

These programs demonstrate fundamental networking concepts in C, focusing on working with ``sockaddr`` structures and DNS resolution.

## Features

### AddressUtility
- **PrintSocketAddress**:
    - Prints a human-readable string representation of a socket address (``sockaddr``) to a given file stream.

    - Supports both IPv4 and IPv6 addresses.

    - Includes the port number in the output if available.

- **SockAddrsEqual**:
    - Compares two socket addresses for equality.

    - Supports both IPv4 and IPv6 addresses.

    - Accounts for address family, address and port.

### GetAddrInfo
- Resolves a given hostname and service/port into a list of socket addresses.

- Outputs the resolved addresses in a human-readable format.

- Utilizes the ``getaddrinfo()`` function for flexible address resolution.

- Supports both IPv4 and IPv6 address families.

## File Structure
- ``AddressUtility.c``: Contains the implementations of ``PrintSocketAddress`` and ``SockAddrsEqual``.
- ``GetAddrInfo.c``: Contains the main fcuntion to resolve hostnames and print socket addresses.
- ``Practical.h``: Header file containing the declarations of utility functions.
- ``DieWithMessage.c``: Contains error-handling functions.

## Compilation Instructions
To compile the project, use the following commands:
~~~ bash
gcc -o GetAddress GetAddrInfo.c AddressUtility.c DieWithMessage.c
~~~
This will generate an executable file: ``GetAddress``.

## Usage Instructions

### AddressUtility
This utility is a library that provides reusable functions for handling socket addresses. It does not include a main function.

## GetAddrInfo
1. Run the program by providing a hostname (or IP address) and a service (or port number) as arguments:
~~~bash
./GetAddress <address/name> <port/service>
~~~

For example:
~~~bash
./GetAddress www.google.com 0
./GetAddress www.tudublin.ie http
~~~

## Error Handling
- Handles invalid arguments with clear error messages.
- Displays errors returned by ``getaddrinfo()`` using ``gai_strerror()``.

## Limitations
- **AddressUtility** functions are designed as helpers and not standalone utilities.
- **GetAddrInfo** outputs raw socket address information without additional formatting or validation.