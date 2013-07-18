#pragma once

#include "Tlhelp32.h"
class DllManager
{
public:
	DllManager(void);
public:
	~DllManager(void);
public:
	DllManager(CString strProcessName,CString strDllName);
public:
	// Ҫע��Ľ�������
	CString m_strProcessName;
public:
	// Ҫע���DLL����
	CString m_strDllName;
public:
	// װ��Dll��ָ���Ľ���
	bool LoadDll(void);
public:
	// �ҵ�ָ���Ľ��̣����ؽ���ID
	DWORD FindTargetProcess(CString processName);
public:
	// ����Ҫע��Ľ�������
	void SetProcessName(CString ProcessName);
public:
	// ����Ҫע���DLL ����
	void SetDllName(CString DllName);
public:
	// ж��DLL����
	bool UnLoadDll();
};

//��Ȩ
BOOL UpPrivilege();
