// xscoket.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "xscoket.h"


// 这是导出变量的一个示例
XSCOKET_API int nxscoket=0;

// 这是导出函数的一个示例。
XSCOKET_API int fnxscoket(void)
{
    return 42;
}

// 这是已导出类的构造函数。
Cxscoket::Cxscoket()
{
    return;
}
