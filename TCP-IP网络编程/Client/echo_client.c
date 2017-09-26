#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<WinSock2.h>

#define BUF_SIZE 1024
void ErrorHandling(char* message);

int main(int argc, char* argv[]) {
	
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
	int strilen;
	SOCKADDR_IN servAddr;

	if (argc != 3) {
		printf("Usage:%s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("Wsastartup() error");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("Hsocket() error!");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("Connection error!");
	else
		puts("Connected............");

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		send(hSocket, message, strlen(message), 0);
		strilen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strilen] = 0;
		printf("����������Ϣ: %s", message);
	}

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}