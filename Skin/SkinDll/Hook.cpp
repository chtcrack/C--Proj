#include "StdAfx.h"
#include ".\Hook.h"


//! ���ʵ���޸��ֽ�
const unsigned int kMax_byte2modify = 1 + 1 + sizeof(unsigned long);

//! ���hooksize
const unsigned int kMax_byte2cover = 0xFF;

//! ���ӽ��ṹ
struct HookNode
{
	HookNode* next;         //!< ������һ���
	unsigned char* mem;     //!< hook�ڴ�λ��
	unsigned int byte2cover;//!< hook����
	unsigned char* lpsc;    //!< ָ��sc
	unsigned char oldcode[kMax_byte2modify];//!< ����ǰ������(����ж��ʱ��ԭ�ж�)
	unsigned char newcode[kMax_byte2modify];//!< ���Ǻ������(����ж��ʱ�����ж�)
	unsigned char sc[1];    //!< ���Ӵ���
};
//////////////////////////////////////////////////////////////////////////
/////////////////////////�������������///////////////////////////////////
//! ��������ͷ
HookNode* g_hook_headlist = (HookNode*)kErrHookNode;
//! ��������ɾ��ָ�����
bool  DeleteFromList(HookNode* node)
{
	HookNode** lplp = &g_hook_headlist;
	HookNode* lp = *lplp;
	while(lp != kErrHookNode)
	{
		if(lp == node)
		{
			*lplp = lp->next;
			delete[]  (unsigned char*)lp;
			return true;
		}
		lplp = &(lp->next);
		lp = lp->next;
	}
	return false;
}
//! ���Ӹ����ж������ָ����Χ�Ƿ���������
bool  CheckMemFromList(unsigned char* mem,const size_t byte2cover)
{
	HookNode** lplp = &g_hook_headlist;
	HookNode* lp = *lplp;
	while(lp != kErrHookNode)
	{
		unsigned char* memend = lp->mem + lp->byte2cover;
		if( (mem >= lp->mem) && (mem <= memend) )
			return  true;
		if( (mem + byte2cover >= lp->mem) && (mem + byte2cover <= memend) )
			return  true;
		lplp = &(lp->next);
		lp = lp->next;
	}
	return false;
}
//! ��������׷��һ�����
void  Add2List(HookNode* node)
{
	HookNode** lplp = &g_hook_headlist;
	HookNode* lp = *lplp;
	while(lp != kErrHookNode)
	{
		lplp = &(lp->next);
		lp = lp->next;
	}
	*lplp = node;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////������UEF���////////////////////////////////////
//! ��ž�UEF
LPTOP_LEVEL_EXCEPTION_FILTER  g_oldUEFHandling = LPTOP_LEVEL_EXCEPTION_FILTER(-1);
//! �����쳣����ص�����
LONG WINAPI  HookUEFHandling(struct _EXCEPTION_POINTERS * ExceptionInfo)
{
	if(ExceptionInfo->ExceptionRecord->ExceptionCode  ==  STATUS_BREAKPOINT)
	{
		HookNode** lplp = &g_hook_headlist;
		HookNode* lp = *lplp;
		while(lp != kErrHookNode)
		{
			if((DWORD)lp->mem == ExceptionInfo->ContextRecord->Eip)
			{
				ExceptionInfo->ContextRecord->Eip  =  (DWORD)lp->lpsc;
				return  EXCEPTION_CONTINUE_EXECUTION;
			}
			lplp = &(lp->next);
			lp = lp->next;
		}
	}
	if(g_oldUEFHandling == NULL)
		return  EXCEPTION_CONTINUE_SEARCH;
	return  g_oldUEFHandling(ExceptionInfo);
}
//////////////////////////////////////////////////////////////////////////
/////////////////////������LastHookErr���////////////////////////////////
HookErrCode g_last_hook_err_;

HookErrCode GetLastHookErr()
{
	return g_last_hook_err_;
}
void SetLastHookErr(const HookErrCode new_errcode)
{
	g_last_hook_err_ = new_errcode;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////������Hook Check���///////////////////////////////
HookErrCode  Check_hooksize(const unsigned int hooksize)
{
	if(hooksize > kMax_byte2cover)    return HookErr_HookSize_OverFlow;
	if(hooksize == 0)  return HookErr_HookSize_0;
	return HookErr_Success;
}

HookErrCode Check_hookmem(void* hookmem)
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

HookErrCode Check_Routin(HookRoutin routin)
{
	try
	{
		unsigned char tmp[2];
		memcpy(tmp,(const void*)routin,sizeof(tmp));
	}
	catch(...)
	{
		return HookErr_Routin;
	}
	return HookErr_Success;
}
//////////////////////////////////////////////////////////////////////////
/////////////////////////������Hook sc���////////////////////////////////
const unsigned int gk_sc_code_len = 0x24;

void  FixSc(HookNode* node,HookRoutin routin,const bool docodeend)
{
	unsigned char* scs = node->sc;
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
	*(unsigned long*)(scs) = CalcHookOffset(scs,routin);
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
bool Hookin(HookNode* node)
{
	const unsigned int thisbyte2cover =
		(node->byte2cover > sizeof(node->newcode))
		? sizeof(node->newcode) : node->byte2cover;
	if(Hookit(node->mem,node->newcode,thisbyte2cover) == FALSE)
		return false;
	Add2List(node);
	return  true;
}

HookNode* Hook(void* hookmem,const unsigned int hooksize,HookRoutin routin,const bool docodeend)
{
	try
	{
		HookErrCode err;
		err = Check_hooksize(hooksize);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return kErrHookNode;    }
		err = Check_hookmem(hookmem);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return kErrHookNode;    }
		err = Check_Routin(routin);
		if(err != HookErr_Success)    {    SetLastHookErr(err);    return kErrHookNode;    }

		const unsigned int max_sc = hooksize + gk_sc_code_len + 1 + sizeof(void*);
		HookNode* node = (HookNode*)new unsigned char[max_sc + sizeof(HookNode) - 1];
		node->next = kErrHookNode;
		node->byte2cover = hooksize;
		node->mem = (unsigned char*)hookmem;
		node->lpsc = node->sc;
		memcpy(node->oldcode,node->mem,sizeof(node->oldcode));
		memcpy(node->newcode,node->mem,sizeof(node->newcode));

		FixSc(node,routin,docodeend);

		switch(node->byte2cover)
		{
		case 1:  case 2: case 3: case 4:
			{
				if(CheckMemFromList(node->mem,node->byte2cover))
				{
					SetLastHookErr(HookErr_Hook_Cover);
					delete[] (unsigned char*)node;
					return kErrHookNode;
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
					return kErrHookNode;
				}
				node->newcode[0] = 0xE9;
				*(unsigned long*)(&node->newcode[1]) = CalcHookOffset(node->mem,node->lpsc);
				break;
			}
		default:
			{
				node->newcode[0] = 0xFF;
				node->newcode[1] = 0x25;
				*(unsigned long*)(&node->newcode[2]) = (unsigned long)&node->lpsc;
				break;
			}
		}
		if(!Hookin(node))
		{
			SetLastHookErr(HookErr_Hook_Write);
			delete[] (unsigned char*)node;
			return kErrHookNode;
		}
		SetLastHookErr(HookErr_Success);
		return node;
	}
	catch(...)
	{
		SetLastHookErr(HookErr_Unkown);
		return kErrHookNode; 
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
			if(memcmp(node->mem,node->newcode,thisbyte2cover) == 0)
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
	HookErrCode err = HookErr_Success;
	if(g_oldUEFHandling != (LPTOP_LEVEL_EXCEPTION_FILTER)(-1))  //����иı䶥���쳣
	{
		LPTOP_LEVEL_EXCEPTION_FILTER  olds = SetUnhandledExceptionFilter(g_oldUEFHandling);  //���Ի�ԭUEF
		if(olds != &HookUEFHandling)
			err = HookErr_Clear_UEF;
	}
	while(g_hook_headlist != kErrHookNode)
	{
		HookErrCode tmp = Unhook(g_hook_headlist,false);
		if( tmp != HookErr_Success )      err = tmp;
	}
	return err;
}
