// SkinDll.h : SkinDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CSkinDllApp
// �йش���ʵ�ֵ���Ϣ������� SkinDll.cpp
//

class CSkinDllApp : public CWinApp
{
public:
	CSkinDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

DWORD WINAPI UloadProce(PVOID param);