#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"
#include <unistd.h>
#include <time.h>

static const int MAXPENDING = 5;	// Maximum pending connections

int main(int argc, char *argv[]) {
	time_t	ticks;
	char sendbuffer[BUFSIZE];	// Send buffer
	char recvbuffer[BUFSIZE];	// Receive buffer
	int numBytes = 0;

	if (argc != 2)	// Check correct number of arguments
		DieWithUserMessage("Parameter(s)", "<Server Port>");

	in_port_t servPort = atoi(argv[1]);		// Server (local) port

	// Create socket
	int servSock;
	if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithSystemMessage("socket() failed");

	struct sockaddr_in servAddr;	// Server address structure
	memset(&servAddr, 0, sizeof(servAddr));		// Init mem to 0
	servAddr.sin_family = AF_INET;		// Family: IPv4
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any incoming
	servAddr.sin_port = htons(servPort);

	// Bind to local address
	if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("bind() failed");

	// Marck socket to listen to incoming connections
	if (listen(servSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for (;;) {
		// Wait for a client connection
		int clntSock = accept(servSock, (struct sockaddr *) NULL, NULL);
		if (clntSock < 0)
			DieWithSystemMessage("accept() failed");

		// Receive buffer from client
		while((numBytes = recv(clntSock, recvbuffer, BUFSIZE - 1, 0)) > 0) {
			recvbuffer[numBytes] = '\0';	// Null-terminate the string
			fputs(recvbuffer, stdout);		// Print buffer on standard output
			
			// Look for end of reception ('\r\n' in the string)
			if (strstr(recvbuffer, "\r\n") > 0)
				break;
		}

		// Send buffer to client
		snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", recvbuffer);
		ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
		if (numBytesSent < 0)
			DieWithSystemMessage("send() failed");

		close(clntSock);	// close client socket
	}
}