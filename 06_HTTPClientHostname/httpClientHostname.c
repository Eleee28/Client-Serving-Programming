#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Practical.h"

int main(int argc, char *argv[]) {
	char recvbuffer[BUFSIZE];	// Receive buffer (I)
	char sendbuffer[BUFSIZE];	// Send buffer (O)
	int numBytes = 0;

	if (argc < 4)	// Check correct number of arguments
		DieWithUserMessage("Parameter(s)", "<Server Address> <Server Port> <echoString>");

	char *httpRequest = argv[3]; // http request for server

	char *host = argv[1];	// Server address/name

	char *service = argv[2]; // Server port/service

	// Create socket using TCP
	int sock;

	struct addrinfo *servAddr; // Holder for returned list of server addrs
	int rtnVal = getaddrinfo(host, service, NULL, &servAddr); // not using any filter for third argument
	if (rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

	for (struct addrinfo *addr = servAddr; addr != NULL; addr = addr->ai_next) {
		// Create a reliable, stream socket using TCP
		sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		if (sock < 0)
			continue; // Socket creation failed, try next address

		// Establish the connection to the echo server
		if (connect(sock, addr->ai_addr, addr->ai_addrlen) == 0)
			break; // Socket connection succeeded, break and return socket

		close(sock); // Socket connection failed, try next address
		sock = -1;
	}

	freeaddrinfo(servAddr); // Free addrinfo allocated in getaddrinfo()

	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	// Send buffer
	snprintf(sendbuffer, sizeof(sendbuffer), "%s", httpRequest);

	ssize_t numBytesSent = send(sock, sendbuffer, strlen(sendbuffer), 0);
	if (numBytesSent < 0)
		DieWithSystemMessage("send() client failed");

	// Receive buffer
	while ((numBytes = recv(sock, recvbuffer, BUFSIZE - 1, 0)) > 0) {
		recvbuffer[numBytes] = '\0';	// Null-terminate the string
		fputs(recvbuffer, stdout);		// Print buffer on standard output
	}
	if (numBytes < 0)
		DieWithSystemMessage("recv() failed");
	fputc('\n', stdout);	// Print final newline

	close(sock);
	exit(0);
}