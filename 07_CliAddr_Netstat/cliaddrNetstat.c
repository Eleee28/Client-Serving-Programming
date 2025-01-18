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

# define HOME_PAGE "HTTP/1.1 200 File Found\r\nContent-Length: 100\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Found</TITLE></HEAD><BODY><h2>FILE Found</h2><hr><p>Your requested FILE was found.</p></BODY></HTML>"

#define ERROR_PAGE "HTTP/1.1 404 File Not Found\r\nContent-Length: 136\r\nConnection: close\r\n\r\n<HTML><HEAD><TITLE>File Not Found</TITLE></HEAD><BODY><h2>FILE Not Found</h2><hr><p>Your requested FILE was not found.</p></BODY></HTML>"

#define SIZE 10000

static const int MAXPENDING = 5;	// Maximum pending connections

int main(int argc, char *argv[]) {
	char sendbuffer[SIZE];	// Send buffer
	char recvbuffer[SIZE];	// Receive buffer
	int numBytes = 0;

	char cmd[16];
	char path[64];
	char vers[16];

	socklen_t clntAddrLen;	// length of address struct
	struct sockaddr_in servaddr, cliaddr;	// new address structure
	char clntName[INET_ADDRSTRLEN];	// buffer to hold client address

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
		
		clntAddrLen = sizeof(cliaddr);
		// Wait for a client connection
		int clntSock = accept(servSock, (struct sockaddr *) NULL, &clntAddrLen);
		if (clntSock < 0)
			DieWithSystemMessage("accept() failed");

		printf("connection from %s, port %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, clntName, sizeof(clntName)), ntohs(cliaddr.sin_port));

		

		// Receive buffer from client
		while((numBytes = recv(clntSock, recvbuffer, SIZE - 1, 0)) > 0) {
			recvbuffer[numBytes] = '\0';	// Null-terminate the string
			fputs(recvbuffer, stdout);		// Print buffer on standard output
			
			// Look for end of reception ('\r\n' in the string)
			if (strstr(recvbuffer, "\r\n\r\n") > 0)
				break;
		}

		sscanf(recvbuffer, "%s %s %s", cmd, path, vers);

		printf("\nPath: %s\n", path);

		// Check path to determine what to send
		if (!strcmp(cmd, "GET")) {
			if (!strcmp(path, "/index.html") || !strcmp(path, "/"))
				snprintf(sendbuffer, sizeof(sendbuffer), "%s", HOME_PAGE);
			else
				snprintf(sendbuffer, sizeof(sendbuffer), "%s", ERROR_PAGE);
		}

		// Send buffer to client
		//snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", recvbuffer);
		ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
		if (numBytesSent < 0)
			DieWithSystemMessage("send() failed");

		close(clntSock);	// close client socket
	}
}