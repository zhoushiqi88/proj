// testsocket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<stdio.h>
#include <iostream>
#ifdef WIN32
#include<Windows.h>
#else
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#define closesocket close
#endif

#include<thread>
using namespace std;

class TcpThread{
public:
	void Main()
	{
		char buf[1024] = {0};
		for(;;) {
			int relen = recv(client,buf,sizeof(buf)-1,0);
			if(relen <= 0) {
				break;
			}
			if(strstr(buf,"quit") != NULL) {
				printf("quit success\n");
				break;
			}
			buf[relen] = '\0';
			send(client,"ok\n",3,0);
			printf("recv %s\n",buf);
		}
		closesocket(client);
		delete this;
	}
	int client = 0;
};	


int main(int argc,char* argv[])
{
#ifdef WIN32
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
#endif
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("create socket failed\n");
		return -1;
	}
	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);


	if (bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		printf("bind port %d failed!\n", port);
		return -2;
	}
	printf("bind port %d success\n", port);
	listen(sock, 10);

	for(;;) {
		sockaddr_in caddr;
		socklen_t len = sizeof(caddr);
		int client = accept(sock,(sockaddr*)&caddr,&len);
		if(client <=0) break;
		printf("accept client %d\n", client);
		char* ip= inet_ntoa(caddr.sin_addr);
		unsigned short cport = ntohs(caddr.sin_port);
		printf("client ip %s\nclient port is %d\n",ip,cport);
		TcpThread *th = new TcpThread();
		th->client = client;
		thread sth(&TcpThread::Main,th);
		sth.detach();
	}
	closesocket(sock);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
