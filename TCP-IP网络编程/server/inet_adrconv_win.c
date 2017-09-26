#include <stdio.h>
#include<string.h>
#include<WinSock2.h>
void ErrorHandling(char* message);

int main(int argc, char *argv[]) {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup()��error!");

	//��IP��ַת��Ϊ�����ַ
	{
		char *addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);	//��IP��ַת��32������ 1.2.3.4->0x4030201
		if (conv_addr == INVALID_SOCKET)
			printf("Error occured!\n");
		else
			printf("32λ�����͵�ַ: %#lx \n", conv_addr);
	}


	//�����ַת��ΪIP��ַ
	{
		/*
		struct sockaddr_in{
			sa_family_t		sin_family;	    ��ַ��:IPV4/IPv6
			unit16_t		sin_port;		16ΪTCP/UDP�˿ں�
			struct in_addr	sin_addr;		32λIPv4��ַ
			char			sin_zero[8];	��ʹ��

			*/
		struct sockaddr_in addr;	
		char* strPtr;
		char strArr[20];

		addr.sin_addr.s_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("IP��ַ:	%s \n", strArr);
	}

	WSACleanup();
	return 0;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}