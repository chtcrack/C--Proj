// stdafx.cpp : 只包括标准包含文件的源文件
// SkinDll.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


void MyDebug(const char * sz, ...)
{
	char szData[1024]={0};

	va_list args;

	va_start(args, sz);

	_vsnprintf(szData, sizeof(szData) - 1, sz, args);

	va_end(args);

	OutputDebugString(szData);

	return;
}