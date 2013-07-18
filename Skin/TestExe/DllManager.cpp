#include "StdAfx.h"
#include "DllManager.h"


DllManager::DllManager(void)
: m_strProcessName(_T(""))
, m_strDllName(_T(""))
{
	UpPrivilege();
}

DllManager::DllManager(CString strProcessName,CString strDllName)
{
    m_strProcessName=strProcessName;
	m_strDllName=strDllName;
}
DllManager::~DllManager(void)
{
}


// 装载Dll到指定的进程
bool DllManager::LoadDll(void)
{
	//判断进程名和DLL名是否为空
	m_strProcessName.Trim();
	m_strDllName.Trim();

	if (m_strProcessName=="" || m_strProcessName.IsEmpty())
	{
		//AfxMessageBox("进程名不能为空");
		return false;
	}

	if (m_strDllName=="" || m_strDllName.IsEmpty())
	{
		//AfxMessageBox("DLL名不能为空");
		return false;
	}

	//遍历进程快照，找到指定的进程
	DWORD processId=FindTargetProcess(m_strProcessName);
    if (processId==0)//如果没有找到
    {
		//AfxMessageBox("没有找到指定的进程");
		return  FALSE;
    }

	//打开指定的进程
	HANDLE hprocess=OpenProcess(PROCESS_CREATE_THREAD|
		                        PROCESS_VM_OPERATION|
								PROCESS_VM_READ|
								PROCESS_VM_WRITE,
								FALSE,
								processId);

	if (hprocess==NULL)//如果打开进程失败
	{
		//AfxMessageBox("进程打开失败");
		return  FALSE;
	}



	

	//定义还原一些反外挂加载勾子
	BYTE LdrCode[]		= {0x8D,0x44,0x24,0x10,0x89,0x44,0x24,0x04};

	BYTE LdrHookCode[]	= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	//计算LdrInitializeThunk的入口地址 

	PTHREAD_START_ROUTINE LdrHookAddr = (PTHREAD_START_ROUTINE) 

		GetProcAddress(GetModuleHandle(TEXT("ntdll")), "LdrInitializeThunk"); 

	if (LdrHookAddr==NULL)

		return FALSE;


	//读被ＨＯＯＫ的代码 

	int	 iReturnCode = ReadProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrHookCode, 8, NULL); 

	if (!iReturnCode)

		return FALSE;


	//还原被ＨＯＯＫ勾子

	iReturnCode = WriteProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrCode, 8, NULL); 

	if (!iReturnCode)

		return FALSE;




    //在指定进程空间申请虚拟内存空间，为了存放DLL名称
	char dllName[MAX_PATH];memset(dllName,0,MAX_PATH);
	memcpy(dllName,m_strDllName,MAX_PATH);

    DWORD dwSize=(DWORD)(strlen(dllName)+1);


	DWORD dwWritten=0;
    LPVOID buffer;
    buffer=VirtualAllocEx(hprocess,NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);
    
	if (buffer==NULL)//如果内存申请失败
	{
		//关闭进程句柄
		CloseHandle(hprocess);
		return FALSE;
	}


    //将DLL名称写入到指定进程的刚申请的虚拟内存空间
	BOOL bRet=WriteProcessMemory(hprocess,buffer,(LPVOID)dllName,dwSize,&dwWritten);
    if (bRet==FALSE)
    {
		//释放内存空间
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);

		return FALSE;
    }

	if (dwSize!=dwWritten)
	{
		//释放内存空间
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		//关闭进程句柄
		CloseHandle(hprocess);

		return FALSE;
	}


    //动态装载指定的DLL文件
   HANDLE hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibrary,buffer,0,0);
   if (hthread==NULL)//创建加载DLL的线程失败
   {
	   //释放内存空间
	   VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
	   //关闭进程句柄
	   CloseHandle(hprocess);
	   return FALSE;
   }

   WaitForSingleObject(hthread,INFINITE);

   //AfxMessageBox("成功注入DLL");

   //注入成功还原ＨＯＯＫ代码
   iReturnCode = WriteProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrHookCode, 8, NULL); 

   if (!iReturnCode)

	   return FALSE;



   //释放资源
   VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
   CloseHandle(hthread);
   CloseHandle(hprocess);

   return TRUE;
}

// 找到指定的进程，返回进程ID,如果没有找到，返回
DWORD DllManager::FindTargetProcess(CString processName)
{
	HANDLE  hsnapshot;
	//进程快照
	hsnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    PROCESSENTRY32  processentry;
	processentry.dwSize=sizeof(PROCESSENTRY32);
	Process32First(hsnapshot,&processentry);

	do 
	{
		if (!_stricmp(processName,processentry.szExeFile))//对比字符串,忽略掉大小写
		{
			return  processentry.th32ProcessID;
		}
	}
	while(Process32Next(hsnapshot,&processentry));

	return 0;
}

// 设置进程名称
void DllManager::SetProcessName(CString ProcessName)
{
	m_strProcessName=ProcessName;
}

// 设置DLL 名称
void DllManager::SetDllName(CString DllName)
{
	m_strDllName=DllName;
}

// 卸载DLL函数
bool DllManager::UnLoadDll()
{
	//判断进程名和DLL名是否为空
	m_strProcessName.Trim();
	m_strDllName.Trim();

	if (m_strProcessName=="" || m_strProcessName.IsEmpty())
	{
		//AfxMessageBox("进程名不能为空");
		return false;
	}

	if (m_strDllName=="" || m_strDllName.IsEmpty())
	{
		//AfxMessageBox("DLL名不能为空");
		return false;
	}

	//遍历进程快照，找到指定的进程
	DWORD processId=FindTargetProcess(m_strProcessName);
	if (processId==0)//如果没有找到
	{
		//AfxMessageBox("没有找到指定的进程");
		return  FALSE;
	}

	//打开指定的进程
	HANDLE hprocess=OpenProcess(PROCESS_CREATE_THREAD|
		PROCESS_VM_OPERATION|
		PROCESS_VM_READ|
		PROCESS_VM_WRITE,
		FALSE,
		processId);

	if (hprocess==NULL)//如果打开进程失败
	{
		return  FALSE;
	}

	//在指定进程空间申请虚拟内存空间，为了存放DLL名称
	char  dllName[MAX_PATH];memset(dllName,0,MAX_PATH);
	memcpy(dllName,m_strDllName,MAX_PATH);

	DWORD dwSize=(DWORD)(strlen(dllName)+1);
	DWORD dwWritten=0;
	LPVOID buffer;
	buffer=VirtualAllocEx(hprocess,NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);

	if (buffer==NULL)//如果内存申请失败
	{
		//关闭进程句柄
		CloseHandle(hprocess);
		return FALSE;
	}

	//将DLL名称写入到指定进程的刚申请的虚拟内存空间
	BOOL bRet=WriteProcessMemory(hprocess,buffer,(LPVOID)dllName,dwSize,&dwWritten);
	if (bRet==FALSE)
	{
		//释放内存空间
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);
		return FALSE;
	}


	if (dwSize!=dwWritten)
	{
		//释放内存空间
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		//关闭进程句柄
		CloseHandle(hprocess);
		return FALSE;
	}

    
  

	//获得DLL对应的HMODULE
	HANDLE hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)GetModuleHandle,buffer,0,0);
	if (hthread==NULL)//创建卸载DLL的线程失败
	{
		//释放内存空间
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);

		return FALSE;
	}


    //获得远程线程GetModuleHandle的执行结果
	WaitForSingleObject(hthread,INFINITE);

	DWORD hmodule=0;
	bRet=GetExitCodeThread(hthread,&hmodule);
	if (bRet==FALSE)
	{
		return FALSE;
	}
	TRACE("hmodule=%d/n",hmodule);
	if (hmodule==0)
	{
		AfxMessageBox("目标DLL不存在");
		//释放资源
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);
		CloseHandle(hthread);
		CloseHandle(hprocess);
		
		return FALSE;
	}

	//释放资源
	VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);
	CloseHandle(hthread);

    //卸载DLL
	hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)FreeLibrary,(LPVOID)hmodule,0,0);
    if(hthread==NULL)
	{
		//释放资源
		CloseHandle(hprocess);
		return false;
	}

	WaitForSingleObject(hthread,INFINITE);
	//释放资源
	//AfxMessageBox("成功卸载DLL");
	CloseHandle(hthread);
	CloseHandle(hprocess);

	return TRUE;
}

//提权
BOOL UpPrivilege()
{
	HANDLE hprocess=::GetCurrentProcess();

	char privilege[]=SE_DEBUG_NAME;

	TOKEN_PRIVILEGES Privileges;

	Privileges.PrivilegeCount=1;

	HANDLE hToken;   

	OpenProcessToken(hprocess,TOKEN_ADJUST_PRIVILEGES,&hToken);   

	LUID luid;

	LookupPrivilegeValue(NULL,privilege,&luid);

	Privileges.Privileges[0].Luid=luid;

	Privileges.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;

	if(AdjustTokenPrivileges(hToken,FALSE,&Privileges,NULL,NULL,NULL)!=0)
		return TRUE;

	return FALSE;
}

