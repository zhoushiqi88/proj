#pragma once
#include<string>
class XTcp
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
	std::string ip;
};

