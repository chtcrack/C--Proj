#include "stdafx.h"
#include "hook.h"

//! ���ʵ���޸��ֽ�
static const unsigned int kMax_byte2modify = 1 + 1 + sizeof(unsigned long);

//! ���hooksize
static const unsigned int kMax_byte2cover = 0xFF;

//! ���ӽ��ṹ
struct HookNode
{
	HookNode* next;         //!< ������һ���
	unsigned char* mem;     //!< hook�ڴ�λ��
	unsigned int byte2cover;//!< hook����
	unsigned char* lpshellcode;  //!< ָ��shellcode
	unsigned char oldcode[kMax_byte2modify];//!< ����ǰ������(����ж��ʱ��ԭ�ж�)
	unsigned char newcode[kMax_byte2modify];//!< ���Ǻ������(����ж��ʱ�����ж�)
	unsigned char shellcode[1];    //!< ���Ӵ���
};
//////////////////////////////////////////////////////////////////////////
/////////////////////////�������������///////////////////////////////////
//! ��������ͷ
static HookNode* g_hook_headlist = NULL;
//! ��������ɾ��ָ�����
static bool  DeleteFromList(HookNode* node)
{
	HookNode* now = g_hook_headlist;
	HookNode* previous = g_hook_headlist;
	while(now != NULL)
	{
		if(node == now)
		{
			if(now == g_hook_headlist)
			{
				//Ҫɾ���Ľڵ�Ϊ��һ���ڵ㡣
				g_hook_headlist = now->next;
			}
			else
			{
				previous->next = now->next;  
			}
			delete[] (unsigned char*)now;
			return true;
		}
		previous = now;
		now = now->next;
	}
	//û�н��
	return false;
}
//! ���Ӹ����ж������ָ����Χ�Ƿ���������
static bool  CheckMemFromList(unsigned char* mem,const size_t byte2cover)
{
	HookNode* now = g_hook_headlist;
	while(now != NULL)
	{
		unsigned char *mem_end = now->mem + now->byte2cover;
		if((mem >= now->mem) && (mem <= mem_end))
		{
			return true;
		}
		if((mem + byte2cover >= now->mem) && (mem + byte2cover <= mem_end))
		{
			return true;
		}
		now = now->next;
	}
	return false;
}
//! ��������׷��һ�����
static void  Add2List(HookNode* node)
{
	node->next = g_hook_headlist;
	g_hook_headlist = node;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////������UEF���////////////////////////////////////
//! ��ž�UEF
static LPTOP_LEVEL_EXCEPTION_FILTER  g_oldUEFHandling = LPTOP_LEVEL_EXCEPTION_FILTER(-1);
//! �����쳣����ص�����
static LONG WINAPI  HookUEFHandling(struct _EXCEPTION_POINTERS * ExceptionInfo)
{
	if(ExceptionInfo->ExceptionRecord->ExceptionCode  ==  STATUS_BREAKPOINT)
	{
		HookNode* now = g_hook_headlist;
		while(now != NULL)
		{
			if((DWORD)now->mem == ExceptionInfo->ContextRecord->Eip)
			{
				ExceptionInfo->ContextRecord->Eip  =  (DWORD)now->lpshellcode;
				return  EXCEPTION_CONTINUE_EXECUTION;
			}
			now = now->next;
		}
	}
	if(g_oldUEFHandling == NULL)  return  EXCEPTION_CONTINUE_SEARCH;
	return  g_oldUEFHandling(ExceptionInfo);
}
//////////////////////////////////////////////////////////////////////////
/////////////////////������LastHookErr���////////////////////////////////
static HookErrCode g_last_hook_err_;

HookErrCode GetLastHookErr()
{
	return g_last_hook_err_;
}
static void SetLastHookErr(const HookErrCode new_errcode)
{
	g_last_hook_err_ = new_errcode;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////������Hook Check���///////////////////////////////
static HookErrCode  Check_hooksize(const unsigned int hooksize)
{
	if(hooksize > kMax_byte2cover)    return HookErr_HookSize_OverFlow;
	if(hooksize == 0)  return HookErr_HookSize_0;
	return HookErr_Success;
}

static HookErrCode Check_hookmem(void* hookmem)
{
	unsigned char tmp[kMax_byte2modify];
	try
	{
		memcpy(tmp,hookmem,sizeof(tmp));
		if(Hookit(hookmem,(LPCVOID)tmp,sizeof(tmp)) == FALSE)
			return HookErr_HookMem_Write;
	}
	catch(...)
	{
		return HookErr_HookMem_Read;
	}
	return HookErr_Success;
}

static HookErrCode Check_Routine(HookRoutine routine)
{
	try
	{
		unsigned char tmp[2];
		memcpy(tmp,(const void*)routine,sizeof(tmp));
	}
	catch(...)
	{
		return HookErr_Routin;
	}
	return HookErr_Success;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////������Hook shellcode���/////////////////////////////
static const unsigned int gk_hook_shellcode_len = 0x24;
/*
68 XXXXXXXX           push EIP
9C                    pushfd
60                    pushad
834424 0C 08          add [esp+C],8  //����esp
54                    push esp
E8 XXXXXXXX           call Routine
817C24 24 XXXXXXXX    cmp [esp+24],EIP  //�ж�EIP�Ƿ��޸�
61                    popad
74 02                 je ..
9D                    popfd
C3                    retn
9D                    popfd
8D6424 04             lea esp,[esp+4]
...
E9 XXXXXXXX           jmp EIP
*/

static void  FixShellCode(HookNode* node,HookRoutine routine,const bool docodeend)
{
	unsigned char* scs = node->shellcode;
	if(!docodeend)    //����ǰ����Ҫ��дԭʼ����
	{
		memcpy(scs,node->mem,node->byte2cover);
		scs += node->byte2cover;
	}
	const void* dest = node->mem + node->byte2cover;
	*scs = 0x68;  ++scs;
	*(unsigned long*)(scs) = (unsigned long)(dest);
	scs += sizeof(unsigned long);
	memcpy(scs,"\x9C\x60\x83\x44\x24\x0C\x08\x54",8);
	scs += 8;
	*scs = 0xE8;  ++scs;
	*(unsigned long*)(scs) = CalcHookOffset(scs,routine);
	scs += sizeof(unsigned long);
	*(unsigned long*)(scs) = 0x24247C81;
	scs += sizeof(unsigned long);
	*(unsigned long*)(scs) = (unsigned long)(dest);
	scs += sizeof(unsigned long);
	memcpy(scs,"\x61\x74\x02\x9D\xC3\x9D\x8D\x64\x24\x04",10);
	scs += 10;
	if(docodeend)  //������к�дԭʼ����
	{
		memcpy(scs,node->mem,node->byte2cover);
		scs += node->byte2cover;
	}
	*scs = 0xE9;  ++scs;
	*(unsigned long*)(scs) = CalcHookOffset(scs,dest);
	scs += sizeof(unsigned long);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////������Hook��UnHook���//////////////////////////////
static bool Hookin(HookNode* node)
{
	const unsigned int thisbyte2cover =
		(node->byte2cover > sizeof(node->newcode))
		? sizeof(node->newcode) : node->byte2cover;
	if(Hookit(node->mem,node->newcode,thisbyte2cover) == FALSE)
		return false;
	Add2List(node);
	return  true;
}

HookNode* Hook(void* hookmem,const unsigned int hooksize,HookRoutine routine,const bool docodeend)
{
	try
	{
		HookErrCode err;
		err = Check_hooksize(hooksize);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return NULL;    }
		err = Check_hookmem(hookmem);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return NULL;    }
		err = Check_Routine(routine);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return NULL;    }

		HookNode* node = (HookNode*)new unsigned char
			[hooksize + gk_hook_shellcode_len + sizeof(void*) + sizeof(HookNode)];
		node->next = NULL;
		node->byte2cover = hooksize;
		node->mem = (unsigned char*)hookmem;
		node->lpshellcode = node->shellcode;
		memcpy(node->oldcode,node->mem,sizeof(node->oldcode));
		memcpy(node->newcode,node->mem,sizeof(node->newcode));

		FixShellCode(node,routine,docodeend);

		switch(node->byte2cover)
		{
		case 1:  case 2: case 3: case 4:
			{
				if(CheckMemFromList(node->mem,node->byte2cover))
				{
					SetLastHookErr(HookErr_Hook_Cover);
					delete[] (unsigned char*)node;
					return NULL;
				}
				//ע�����滻U.E.F��
				LPTOP_LEVEL_EXCEPTION_FILTER  olds = SetUnhandledExceptionFilter(HookUEFHandling);
				if(olds != &HookUEFHandling) g_oldUEFHandling = olds;
				//���ǵ�U.E.F���ܱ������£�ֻ�������һ�η�CrackUEFHandling��ԭU.E.F
				node->newcode[0] = 0xCC;
				break;
			}
		case 5:
			{
				if(CheckMemFromList(node->mem,node->byte2cover))
				{
					SetLastHookErr(HookErr_Hook_Cover);
					delete[] (unsigned char*)node;
					return NULL;
				}
				node->newcode[0] = 0xE9;
				*(unsigned long*)(&node->newcode[1]) = CalcHookOffset(node->mem + 1,node->lpshellcode);
				break;
			}
		default:
			{
				node->newcode[0] = 0xFF;
				node->newcode[1] = 0x25;
				*(unsigned long*)(&node->newcode[2]) = (unsigned long)&node->lpshellcode;
				break;
			}
		}
		if(!Hookin(node))
		{
			SetLastHookErr(HookErr_Hook_Write);
			delete[] (unsigned char*)node;
			return NULL;
		}
		SetLastHookErr(HookErr_Success);
		return node;
	}
	catch(...)
	{
		SetLastHookErr(HookErr_Unkown);
		return NULL; 
	}
}

HookErrCode Unhook(HookNode* node,const bool errbreak)
{
	HookErrCode err = HookErr_Success;
	try
	{
		const unsigned int thisbyte2cover =
			(node->byte2cover > sizeof(node->newcode))
			? sizeof(node->newcode) : node->byte2cover;
		if(memcmp(node->mem,node->oldcode,thisbyte2cover) == 0)
		{
			err = HookErr_UnHook_Restore;
		}
		else
		{
			if(memcmp(node->mem,node->newcode,thisbyte2cover) != 0)
			{
				err = HookErr_UnHook_BeCover;
				if(errbreak)        return err;
			}
			if(Hookit(node->mem,node->oldcode,thisbyte2cover) == FALSE)
			{
				err = HookErr_UnHook_Write;
				if(errbreak)        return err;
			}
		}
		if(!DeleteFromList(node))
			err = HookErr_Del_NoExist;
	}
	catch(...)
	{
		err = HookErr_Unkown;
	}
	return err;
}

HookErrCode  HookClear(void)
{
	try
	{
		HookErrCode err = HookErr_Success;
		if(g_oldUEFHandling != (LPTOP_LEVEL_EXCEPTION_FILTER)(-1))  //����иı䶥���쳣
		{
			LPTOP_LEVEL_EXCEPTION_FILTER  olds = SetUnhandledExceptionFilter(g_oldUEFHandling);  //���Ի�ԭUEF
			if(olds != &HookUEFHandling)
				err = HookErr_Clear_UEF;
		}
		while(g_hook_headlist != NULL)
		{
			HookErrCode tmp = Unhook(g_hook_headlist,false);
			if( tmp != HookErr_Success )      err = tmp;
		}
		return err;
	}
	catch(...)
	{
	}
	return HookErr_Unkown;
}