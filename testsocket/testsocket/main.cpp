// testsocket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"XTcp.h"
#include<stdlib.h>
#include<thread>

class TcpThread{
public:
	void Main()
	{
		char buf[1024] = {0};
		for(;;) {
			int relen = client.Recv(buf,sizeof(buf)-1);
			if(relen <= 0) {
				break;
			}
			if(strstr(buf,"quit") != NULL) {
				printf("quit success\n");
				break;
			}
			buf[relen] = '\0';
			client.Send("ok\n",3);
			printf("recv %s\n",buf);
		}
		client.Close();
		delete this;
	}
	XTcp client;
};	


int main(int argc,char* argv[])
{

	unsigned short port = 8080;
	if (argc > 1) {
		port = atoi(argv[1]);
	}
	XTcp ser;
	ser.CreatSocket();
	ser.Bind(port);
	for (;;) {
		XTcp client = ser.Accept();
		TcpThread *th = new TcpThread();
		th->client = client;
		std::thread sth(&TcpThread::Main, th);
		sth.detach();
	}
	ser.Close();
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
