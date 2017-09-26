#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<WinSock2.h>

#define BUF_SIZE 30
void ErrorHandling(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	SOCKET hAcptSock, hRecvSock;

	SOCKADDR_IN recvAdr, sendAdr;
	int sendAdrSize, strlen;
	char buf[BUF_SIZE];
	int result;

	fd_set read, except, readCopy, exceptCopy;
	struct timeval timeout;

	if (argc != 2) {
		printf("Usage:%s <port>\n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("Wsastartup() error");
	}

	hAcptSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&recvAdr, 0, sizeof(recvAdr));
	recvAdr.sin_family = AF_INET;
	recvAdr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	recvAdr.sin_port = htons(atoi(argv[1]));


	if (bind(hAcptSock, (SOCKADDR*)&recvAdr, sizeof(recvAdr) )== SOCKET_ERROR)
		ErrorHandling("bind() error!");
	if (listen(hAcptSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error!");

	sendAdrSize = sizeof(sendAdr);
	hRecvSock = accept(hAcptSock, (SOCKADDR*)&sendAdr, &sendAdrSize);
	FD_ZERO(&read);
	FD_ZERO(&except);
	FD_SET(hRecvSock, &read);
	FD_SET(hRecvSock, &except);

	while (1)
	{
		readCopy = read;
		exceptCopy = except;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		result = select(0, &readCopy, 0, &exceptCopy, &timeout);

		if (result > 0) {
			if (FD_ISSET(hRecvSock,&exceptCopy))
			{
				strlen = recv(hRecvSock, buf, BUF_SIZE - 1, MSG_OOB);
				buf[strlen] = 0;
				printf("½ô¼±µÄÏûÏ¢: %s \n", buf);
			}

			if (FD_ISSET(hRecvSock, &readCopy))
			{
				strlen = recv(hRecvSock, buf, BUF_SIZE - 1, 0);
				if (strlen == 0)
				{
					break;
					closesocket(hRecvSock);
				}
				else
				{
					buf[strlen] = 0;
					puts(buf);
				}
			}
		}
	}
	closesocket(hAcptSock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}