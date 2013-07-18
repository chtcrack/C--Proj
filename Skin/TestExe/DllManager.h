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
	// 要注入的进程名称
	CString m_strProcessName;
public:
	// 要注入的DLL名称
	CString m_strDllName;
public:
	// 装载Dll到指定的进程
	bool LoadDll(void);
public:
	// 找到指定的进程，返回进程ID
	DWORD FindTargetProcess(CString processName);
public:
	// 设置要注入的进程名称
	void SetProcessName(CString ProcessName);
public:
	// 设置要注入的DLL 名称
	void SetDllName(CString DllName);
public:
	// 卸载DLL函数
	bool UnLoadDll();
};

//提权
BOOL UpPrivilege();
