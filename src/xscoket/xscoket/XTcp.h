#pragma once

#ifdef XSCOKET_EXPORTS
#define XSCOKET_API __declspec(dllexport)
#else
#define XSCOKET_API __declspec(dllimport)
#endif
#include<string>
class XSCOKET_API XTcp
{
public:
	XTcp();
	int CreatSocket();
	bool Bind(unsigned short port);
	XTcp Accept();
	void Close();
	int Recv(char*buf,int bufsize);
	int Send(const char*buf,int bufsize);
	virtual ~XTcp();
	int sock = 0;
	unsigned short port = 0;
	char ip[16];
};

