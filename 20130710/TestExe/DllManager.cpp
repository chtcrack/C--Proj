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


// װ��Dll��ָ���Ľ���
bool DllManager::LoadDll(void)
{
	//�жϽ�������DLL���Ƿ�Ϊ��
	m_strProcessName.Trim();
	m_strDllName.Trim();

	if (m_strProcessName=="" || m_strProcessName.IsEmpty())
	{
		//AfxMessageBox("����������Ϊ��");
		return false;
	}

	if (m_strDllName=="" || m_strDllName.IsEmpty())
	{
		//AfxMessageBox("DLL������Ϊ��");
		return false;
	}

	//�������̿��գ��ҵ�ָ���Ľ���
	DWORD processId=FindTargetProcess(m_strProcessName);
    if (processId==0)//���û���ҵ�
    {
		//AfxMessageBox("û���ҵ�ָ���Ľ���");
		return  FALSE;
    }

	//��ָ���Ľ���
	HANDLE hprocess=OpenProcess(PROCESS_CREATE_THREAD|
		                        PROCESS_VM_OPERATION|
								PROCESS_VM_READ|
								PROCESS_VM_WRITE,
								FALSE,
								processId);

	if (hprocess==NULL)//����򿪽���ʧ��
	{
		//AfxMessageBox("���̴�ʧ��");
		return  FALSE;
	}



	

	//���廹ԭһЩ����Ҽ��ع���
	BYTE LdrCode[]		= {0x8D,0x44,0x24,0x10,0x89,0x44,0x24,0x04};

	BYTE LdrHookCode[]	= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	//����LdrInitializeThunk����ڵ�ַ 

	PTHREAD_START_ROUTINE LdrHookAddr = (PTHREAD_START_ROUTINE) 

		GetProcAddress(GetModuleHandle(TEXT("ntdll")), "LdrInitializeThunk"); 

	if (LdrHookAddr==NULL)

		return FALSE;


	//�����ȣϣϣ˵Ĵ��� 

	int	 iReturnCode = ReadProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrHookCode, 8, NULL); 

	if (!iReturnCode)

		return FALSE;


	//��ԭ���ȣϣϣ˹���

	iReturnCode = WriteProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrCode, 8, NULL); 

	if (!iReturnCode)

		return FALSE;




    //��ָ�����̿ռ����������ڴ�ռ䣬Ϊ�˴��DLL����
	char dllName[MAX_PATH];memset(dllName,0,MAX_PATH);
	memcpy(dllName,m_strDllName,MAX_PATH);

    DWORD dwSize=(DWORD)(strlen(dllName)+1);


	DWORD dwWritten=0;
    LPVOID buffer;
    buffer=VirtualAllocEx(hprocess,NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);
    
	if (buffer==NULL)//����ڴ�����ʧ��
	{
		//�رս��̾��
		CloseHandle(hprocess);
		return FALSE;
	}


    //��DLL����д�뵽ָ�����̵ĸ�����������ڴ�ռ�
	BOOL bRet=WriteProcessMemory(hprocess,buffer,(LPVOID)dllName,dwSize,&dwWritten);
    if (bRet==FALSE)
    {
		//�ͷ��ڴ�ռ�
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);

		return FALSE;
    }

	if (dwSize!=dwWritten)
	{
		//�ͷ��ڴ�ռ�
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		//�رս��̾��
		CloseHandle(hprocess);

		return FALSE;
	}


    //��̬װ��ָ����DLL�ļ�
   HANDLE hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)LoadLibrary,buffer,0,0);
   if (hthread==NULL)//��������DLL���߳�ʧ��
   {
	   //�ͷ��ڴ�ռ�
	   VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
	   //�رս��̾��
	   CloseHandle(hprocess);
	   return FALSE;
   }

   WaitForSingleObject(hthread,INFINITE);

   //AfxMessageBox("�ɹ�ע��DLL");

   //ע��ɹ���ԭ�ȣϣϣ˴���
   iReturnCode = WriteProcessMemory(hprocess, (LPVOID)LdrHookAddr,&LdrHookCode, 8, NULL); 

   if (!iReturnCode)

	   return FALSE;



   //�ͷ���Դ
   VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
   CloseHandle(hthread);
   CloseHandle(hprocess);

   return TRUE;
}

// �ҵ�ָ���Ľ��̣����ؽ���ID,���û���ҵ�������
DWORD DllManager::FindTargetProcess(CString processName)
{
	HANDLE  hsnapshot;
	//���̿���
	hsnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    PROCESSENTRY32  processentry;
	processentry.dwSize=sizeof(PROCESSENTRY32);
	Process32First(hsnapshot,&processentry);

	do 
	{
		if (!_stricmp(processName,processentry.szExeFile))//�Ա��ַ���,���Ե���Сд
		{
			return  processentry.th32ProcessID;
		}
	}
	while(Process32Next(hsnapshot,&processentry));

	return 0;
}

// ���ý�������
void DllManager::SetProcessName(CString ProcessName)
{
	m_strProcessName=ProcessName;
}

// ����DLL ����
void DllManager::SetDllName(CString DllName)
{
	m_strDllName=DllName;
}

// ж��DLL����
bool DllManager::UnLoadDll()
{
	//�жϽ�������DLL���Ƿ�Ϊ��
	m_strProcessName.Trim();
	m_strDllName.Trim();

	if (m_strProcessName=="" || m_strProcessName.IsEmpty())
	{
		//AfxMessageBox("����������Ϊ��");
		return false;
	}

	if (m_strDllName=="" || m_strDllName.IsEmpty())
	{
		//AfxMessageBox("DLL������Ϊ��");
		return false;
	}

	//�������̿��գ��ҵ�ָ���Ľ���
	DWORD processId=FindTargetProcess(m_strProcessName);
	if (processId==0)//���û���ҵ�
	{
		//AfxMessageBox("û���ҵ�ָ���Ľ���");
		return  FALSE;
	}

	//��ָ���Ľ���
	HANDLE hprocess=OpenProcess(PROCESS_CREATE_THREAD|
		PROCESS_VM_OPERATION|
		PROCESS_VM_READ|
		PROCESS_VM_WRITE,
		FALSE,
		processId);

	if (hprocess==NULL)//����򿪽���ʧ��
	{
		return  FALSE;
	}

	//��ָ�����̿ռ����������ڴ�ռ䣬Ϊ�˴��DLL����
	char  dllName[MAX_PATH];memset(dllName,0,MAX_PATH);
	memcpy(dllName,m_strDllName,MAX_PATH);

	DWORD dwSize=(DWORD)(strlen(dllName)+1);
	DWORD dwWritten=0;
	LPVOID buffer;
	buffer=VirtualAllocEx(hprocess,NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);

	if (buffer==NULL)//����ڴ�����ʧ��
	{
		//�رս��̾��
		CloseHandle(hprocess);
		return FALSE;
	}

	//��DLL����д�뵽ָ�����̵ĸ�����������ڴ�ռ�
	BOOL bRet=WriteProcessMemory(hprocess,buffer,(LPVOID)dllName,dwSize,&dwWritten);
	if (bRet==FALSE)
	{
		//�ͷ��ڴ�ռ�
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);
		return FALSE;
	}


	if (dwSize!=dwWritten)
	{
		//�ͷ��ڴ�ռ�
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		//�رս��̾��
		CloseHandle(hprocess);
		return FALSE;
	}

    
  

	//���DLL��Ӧ��HMODULE
	HANDLE hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)GetModuleHandle,buffer,0,0);
	if (hthread==NULL)//����ж��DLL���߳�ʧ��
	{
		//�ͷ��ڴ�ռ�
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);		
		CloseHandle(hprocess);

		return FALSE;
	}


    //���Զ���߳�GetModuleHandle��ִ�н��
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
		AfxMessageBox("Ŀ��DLL������");
		//�ͷ���Դ
		VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);
		CloseHandle(hthread);
		CloseHandle(hprocess);
		
		return FALSE;
	}

	//�ͷ���Դ
	VirtualFreeEx(hprocess,buffer,dwSize,MEM_DECOMMIT);
	CloseHandle(hthread);

    //ж��DLL
	hthread=CreateRemoteThread(hprocess,NULL,0,(LPTHREAD_START_ROUTINE)FreeLibrary,(LPVOID)hmodule,0,0);
    if(hthread==NULL)
	{
		//�ͷ���Դ
		CloseHandle(hprocess);
		return false;
	}

	WaitForSingleObject(hthread,INFINITE);
	//�ͷ���Դ
	//AfxMessageBox("�ɹ�ж��DLL");
	CloseHandle(hthread);
	CloseHandle(hprocess);

	return TRUE;
}

//��Ȩ
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

