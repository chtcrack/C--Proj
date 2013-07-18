#include "StdAfx.h"
#include ".\Hook.h"


//! 最大实际修改字节
const unsigned int kMax_byte2modify = 1 + 1 + sizeof(unsigned long);

//! 最大hooksize
const unsigned int kMax_byte2cover = 0xFF;

//! 钩子结点结构
struct HookNode
{
	HookNode* next;         //!< 链表下一结点
	unsigned char* mem;     //!< hook内存位置
	unsigned int byte2cover;//!< hook长度
	unsigned char* lpsc;    //!< 指向sc
	unsigned char oldcode[kMax_byte2modify];//!< 覆盖前的数据(用于卸载时还原判定)
	unsigned char newcode[kMax_byte2modify];//!< 覆盖后的数据(用于卸载时覆盖判定)
	unsigned char sc[1];    //!< 钩子代码
};
//////////////////////////////////////////////////////////////////////////
/////////////////////////以下是链表相关///////////////////////////////////
//! 钩子链表头
HookNode* g_hook_headlist = (HookNode*)kErrHookNode;
//! 从链表中删除指定结点
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
//! 钩子覆盖判定，检查指定范围是否在链表中
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
//! 向链表中追加一个结点
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
/////////////////////////以下是UEF相关////////////////////////////////////
//! 存放旧UEF
LPTOP_LEVEL_EXCEPTION_FILTER  g_oldUEFHandling = LPTOP_LEVEL_EXCEPTION_FILTER(-1);
//! 顶层异常处理回调函数
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
/////////////////////以下是LastHookErr相关////////////////////////////////
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
///////////////////////以下是Hook Check相关///////////////////////////////
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
/////////////////////////以下是Hook sc相关////////////////////////////////
const unsigned int gk_sc_code_len = 0x24;

void  FixSc(HookNode* node,HookRoutin routin,const bool docodeend)
{
	unsigned char* scs = node->sc;
	if(!docodeend)    //代码前行需要先写原始代码
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
	if(docodeend)  //代码后行后写原始代码
	{
		memcpy(scs,node->mem,node->byte2cover);
		scs += node->byte2cover;
	}
	*scs = 0xE9;  ++scs;
	*(unsigned long*)(scs) = CalcHookOffset(scs,dest);
	scs += sizeof(unsigned long);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////以下是Hook、UnHook相关//////////////////////////////
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
				//注意先替换U.E.F！
				LPTOP_LEVEL_EXCEPTION_FILTER  olds = SetUnhandledExceptionFilter(HookUEFHandling);
				if(olds != &HookUEFHandling) g_oldUEFHandling = olds;
				//考虑到U.E.F可能被反复下，只保存最后一次非CrackUEFHandling的原U.E.F
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
	if(g_oldUEFHandling != (LPTOP_LEVEL_EXCEPTION_FILTER)(-1))  //如果有改变顶层异常
	{
		LPTOP_LEVEL_EXCEPTION_FILTER  olds = SetUnhandledExceptionFilter(g_oldUEFHandling);  //尝试还原UEF
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
