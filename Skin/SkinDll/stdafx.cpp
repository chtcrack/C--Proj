// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// SkinDll.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

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