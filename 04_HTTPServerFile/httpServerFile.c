#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Practical.h"

#define SIZE 10000

static const int MAXPENDING = 5;	// Maximum pending connections

int main(int argc, char *argv[]) {
	char sendbuffer[SIZE];	// Send buffer
	char recvbuffer[SIZE];	// Receive buffer
	int numBytes = 0, char_in, count = 0, size = 0; // for file manipulation

	// char arrays to store first line of HTTP Request
	char discard1[50];
	char path[200] = {'.'};
	char discard2[50];

	struct stat statbuf; // open file attributes
	FILE *fptr; // file pointer to open file

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

	// Mark socket to listen to incoming connections
	if (listen(servSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	// Infinite server loop
	for (;;) {
		// Wait for a client connection
		int clntSock = accept(servSock, (struct sockaddr *) NULL, NULL);
		if (clntSock < 0)
			DieWithSystemMessage("accept() failed");

		// Receive buffer from client
		while((numBytes = recv(clntSock, recvbuffer, SIZE - 1, 0)) > 0) {
			recvbuffer[numBytes] = '\0';	// Null-terminate the string
			fputs(recvbuffer, stdout);		// Print buffer on standard output
			
			// Look for end of reception ('\r\n' in the string)
			if (strstr(recvbuffer, "\r\n\r\n") > 0)
				break;
		}

		sscanf(recvbuffer, "%s %s %s", discard1, (path + 1), discard2);

		printf("\nPath: %s\n", path); // debugging

		if (strcmp(path, "./favicon.ico") == 0) { // ignore request for favicon
			printf("\n\nFound favicon.ico\n\n");
			close(clntSock); // close client socket
			continue;
		}

		if (strcmp(path, "./") == 0)
			strcpy(path, "./index.html");

		fptr = fopen(path, "r"); // O_RDONLY
		
		if (!fptr) { // file does not exist
			strcpy(path, "./error.html");
			fptr = fopen(path, "r");
			stat("./error.html", &statbuf);
			size = statbuf.st_size; // file size of open file

			// Store negative HTTP headers in outgoing buffer
			snprintf(sendbuffer, sizeof(sendbuffer), "HTTP/1.1 404 Not Found\r\nContent-Length: %d\r\nCache-Control: no-cache\r\nConnection: close\r\n\r\n", size);

			// DEBUG -- TODO delete
			printf("Sending error header: %s\n", sendbuffer);
		}
		else { // file exists
			stat(path, &statbuf);
			size = statbuf.st_size;

			// Store positive HTTP headers in outgoing buffer
			snprintf(sendbuffer, sizeof(sendbuffer), "HTTP/1.1 200 OK\r\nContent-Length: %d\r\nCache-Control: no-cache\r\nConnection: close\r\n\r\n", size);
			// DEBUG -- TODO delete
			printf("Sending good header: %s\n", sendbuffer);
		}

		// Send buffer with header to client
		ssize_t numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
		if (numBytesSent < 0)
			DieWithSystemMessage("send() failed");

		count = 0; // Reset count for each file

		// Insert contents of open file (byte-wise) in outgoing buffer and return to connected socke
		while ((char_in = fgetc(fptr)) != EOF) { // read contents of file character by character
			sendbuffer[count++] = char_in;
			if (count >= SIZE - 1) { // Send buffer if it's full
				sendbuffer[count] = '\0';
				send(clntSock, sendbuffer, count, 0);
				count = 0;
			}
		}
		
		if (count > 0) { // Send remainning data in buffer
			sendbuffer[count] = '\0';

			// Send file contents to client
			numBytesSent = send(clntSock, sendbuffer, strlen(sendbuffer), 0);
			if (numBytes < 0)
				DieWithSystemMessage("send() filed");
		}

		// Reset all variables and buffers -- TODO

		fclose(fptr);	// close file
		close(clntSock);	// close client socket

	}
}