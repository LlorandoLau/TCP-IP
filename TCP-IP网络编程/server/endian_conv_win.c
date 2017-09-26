//conv:Conversion 转换，文件名的意思就是字节符转换
#include<stdio.h>
#include <WinSock2.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[]) {
	WSADATA wsaData;
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr = 0x12345678;
	unsigned long net_addr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSASTARTUP() ERROR!)");

	//h:host n:network
	net_port = htons(host_port);	//把short型数据从主机字节序转化为网络字节序
	net_addr = htonl(host_addr);	//把long型数据从主机字节序转化为网络字节序

	/*# 完整显示地址数值
	有: 0x12345678
	没有:12345678
	*/
	printf("主机端口:	%#x \n", host_port);
	printf("网络端口:	%#x \n", net_port);
	printf("主机地址:	%#lx \n",host_addr);
	printf("网络地址:	%#lx \n",net_addr);
	
	WSACleanup();
	return 0;
}
void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}