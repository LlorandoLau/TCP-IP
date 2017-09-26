//conv:Conversion ת�����ļ�������˼�����ֽڷ�ת��
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
	net_port = htons(host_port);	//��short�����ݴ������ֽ���ת��Ϊ�����ֽ���
	net_addr = htonl(host_addr);	//��long�����ݴ������ֽ���ת��Ϊ�����ֽ���

	/*# ������ʾ��ַ��ֵ
	��: 0x12345678
	û��:12345678
	*/
	printf("�����˿�:	%#x \n", host_port);
	printf("����˿�:	%#x \n", net_port);
	printf("������ַ:	%#lx \n",host_addr);
	printf("�����ַ:	%#lx \n",net_addr);
	
	WSACleanup();
	return 0;
}
void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}