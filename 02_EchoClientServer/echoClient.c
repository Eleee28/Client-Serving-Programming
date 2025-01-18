#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

	char *servIP = argv[1];		// Server IP address

	in_port_t servPort = atoi(argv[2]);		// Server port

	char *echoString = argv[3]; // String to be sent to the echoServer

	// Create socket using TCP
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	struct sockaddr_in servAddr;	// Server address structure
	memset(&servAddr, 0, sizeof(servAddr));		// Init mem to 0
	servAddr.sin_family = AF_INET;		// Family: IPv4

	int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
	if (rtnVal == 0)
		DieWithUserMessage("inet_pton() failed", "invalid address string");
	else if (rtnVal < 0)
		DieWithSystemMessage("inet_pton() failed");
	servAddr.sin_port = htons(servPort);    // Server port

	// Establish connection to server
	if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("connect() failed");

	// Send buffer
	snprintf(sendbuffer, sizeof(sendbuffer), "%s\r\n", echoString);
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