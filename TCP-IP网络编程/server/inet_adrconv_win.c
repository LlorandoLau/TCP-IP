#include <stdio.h>
#include<string.h>
#include<WinSock2.h>
void ErrorHandling(char* message);

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup()　error!");

	//把IP地址转化为网络地址
	{
		char *addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);	//把IP地址转成32整数型 1.2.3.4->0x4030201
		if (conv_addr == INVALID_SOCKET)
			printf("Error occured!\n");
		else
			printf("32位整数型地址: %#lx \n", conv_addr);
	}


	//网络地址转化为IP地址
	{
		/*
		struct sockaddr_in{
			sa_family_t		sin_family;	    地址族:IPV4/IPv6
			unit16_t		sin_port;		16为TCP/UDP端口号
			struct in_addr	sin_addr;		32位IPv4地址
			char			sin_zero[8];	不使用

			*/
		struct sockaddr_in addr;	
		char* strPtr;
		char strArr[20];

		addr.sin_addr.s_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("IP地址:	%s \n", strArr);
	}

	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}