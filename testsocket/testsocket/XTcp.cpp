#include "pch.h"
#include "XTcp.h"
#include<stdio.h>
#include <iostream>
#ifdef WIN32
#include<Windows.h>
#define socklen_t int
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

XTcp::XTcp()
{
#ifdef WIN32
	static bool first = true;
	if (first == true) {
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}
#endif
}

int XTcp::CreatSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("create socket failed\n");
	}
	return sock;
}

bool XTcp::Bind(unsigned short port) {
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);


	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
		printf("bind port %d failed!\n", port);
		return -2;
	}
	printf("bind port %d success\n", port);
	listen(sock, 10);
}

XTcp XTcp::Accept() {
	XTcp tcp;
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int client = accept(sock, (sockaddr*)&caddr, &len);
	if (client <= 0) return tcp;
	printf("accept client %d\n", client);
	tcp.ip = inet_ntoa(caddr.sin_addr);
	tcp.port = ntohs(caddr.sin_port);
	tcp.sock = client;
	printf("client ip %s\nclient port is %d\n", tcp.ip.c_str(), tcp.port);
	return tcp;
}

int XTcp::Recv(char*buf,int bufsize) {
	return recv(sock, buf, bufsize, 0);
}


int XTcp::Send(const char *buf,int bufsize) {
	int sendsize = 0;
	for (;;) {
		int len = send(sock, buf+sendsize, bufsize-sendsize, 0);
		if (len <= 0) break;
		sendsize += len;
	}
	return sendsize;
}

void XTcp::Close() {
	if (sock <= 0) return;
	closesocket(sock);
}

XTcp::~XTcp()
{
}
