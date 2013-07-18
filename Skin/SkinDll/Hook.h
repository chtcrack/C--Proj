

////////////////////////////////////////Hook函数////////////////////////////////////
/*!
  指定内存位置与回调函数，执行Hook操作。\n
  当hooksize == 1~4：采用UEF；5：采用jmp XXX；6~0xFF：采用jmp dword ptr [XXX]\n
  当hooksize <= 5时，有强制钩子覆盖判定，不可下在已有钩子范围内\n
  在hook位置复用时，注意根据需要特别注意先后行的选择\n
  罕见使用：当希望使用UEF却又需要覆盖hooksize>=5时，请在回调函数中设置Eip一样可以实现效果，而不能使hooksize>=5实现UEF。
  \param hookmem   指定hook内存的位置
  \param hooksize  hook长度
  \param routin    指定的回调函数(请参考HookRoutin)
  \param docodeend true：覆盖的代码后于回调执行，false：覆盖的代码先于回调执行
  \return 钩子结点指针，用于UnHook。\n
          当执行失败时，返回kErrHookNode。此时应该调用GetLastHookErr得到失败原因



  例子:
    #include "hook.h"
    void __stdcall Routin(CPU_ST* lpcpu)
    {
      return;
    }
    HookNode* node = Hook((void*)0x401000,5,Routin,false);  //在0x401000下5 byte JMP XXX钩子，代码先行
    HookNode* node = Hook((void*)0x401000,6,Routin,true);   //在0x401000下6 byte JMP [XXX]钩子，代码先行
    HookNode* node = Hook((void*)0x401000,1,Routin,true);   //在0x401000下1 byte UEF钩子，代码先行
    if(node == kErrHookNode)
    {
      cout<<"下钩子出错，错误码："<<GetLastHookErr();
    }
*/



////////////////////////////////////////UnHook函数////////////////////////////////////
/*!
  指定HookNode结点指针，执行UnHook操作。\n
  注意：UnHook函数直接返回Hook错误码，不影响GetLastHookErr\n
  因为卸载钩子会有一些异常情况，强制卸载极可能会造成崩溃，所以可以指定错误停止，
  \param node      指定HookNode结点指针
  \param errbreak  指定在卸载钩子遭遇错误时，是否停止卸载
  \return HookErr_Success　      操作成功完成\n
          HookErr_UnHook_Restore 钩子位置已经被还原(注意这只是一个Warning不影响卸载的安全性)\n
          HookErr_UnHook_BeCover 钩子位置被覆盖(强制卸载有风险，可停止卸载)\n
          HookErr_UnHook_Write   还原钩子时，写入失败(一般是权限不足)\n
          HookErr_Del_NoExist    钩子不存在于链表\n
          HookErr_Unkown         未知异常(可能是个非法的HookNode)
  
  例子:
    #include "hook.h"
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    if(node == kErrHookNode) return;
    cout<<"卸载钩子："<<Unhook(node,false);
*/


#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//! Hook错误码
enum  HookErrCode
{
  HookErr_Success,           //!< Hook成功完成
  HookErr_HookSize_0,        //!< hooksize为0
  HookErr_HookSize_OverFlow, //!< hooksize超限(限制最大为0xFF)
  HookErr_HookMem_Read,      //!< hookmem尝试读取失败(一般是地址非法)
  HookErr_HookMem_Write,     //!< hookmem尝试写入失败(一般是权限不足)
  HookErr_Routin,            //!< Routin地址非法
  HookErr_Del_NoExist,       //!< 删除时指定钩子不存在
  HookErr_Hook_Write,        //!< 写入钩子失败(一般是权限不足)
  HookErr_Hook_Cover,        //!< 与已存在的钩子位置有冲突
  HookErr_UnHook_Restore,    //!< 钩子已经被还原
  HookErr_UnHook_BeCover,    //!< 钩子位置被覆盖
  HookErr_UnHook_Write,      //!< 钩子还原时写失败(一般是权限不足)
  HookErr_Clear_UEF,         //!< 还原UEF失败(一般是UEF被覆盖)
  HookErr_Unkown,            //!< 未知异常
};

#pragma warning(push)
#pragma warning(disable:4510)  //warning C4510: “cpu_st”: 未能生成默认构造函数
#pragma warning(disable:4512)  //warning C4512: “cpu_st”: 未能生成赋值运算符
#pragma warning(disable:4610)  //warning C4610: struct“cpu_st”永远不能实例化 - 需要用户定义的构造函数
//! 标准回调函数使用的CPU结构
struct CPU_ST
{
  unsigned long regEdi;
  unsigned long regEsi;
  unsigned long regEbp;
  const unsigned long regEsp;    //!< 注意esp不能修改，改了也没意义
  unsigned long regEbx;
  unsigned long regEdx;
  unsigned long regEcx;
  unsigned long regEax;
  unsigned long regf;
  unsigned long regEip;
};
#pragma warning(pop)
//! 回调函数格式
typedef void (__stdcall *HookRoutin)(CPU_ST* cpu);
//! 钩子结点结构，前置声明，不开放定义
struct HookNode;
//! 非法钩子结点定义，用于标识Hook失败
HookNode* const kErrHookNode = (HookNode* const)-1;

HookNode* Hook(void* hookmem,
               const unsigned int hooksize,
               HookRoutin routin,
               const bool docodeend
               );

HookErrCode Unhook(HookNode* node,const bool errbreak);
HookErrCode HookClear();
HookErrCode GetLastHookErr();

inline unsigned long CalcHookOffset(const void* mem,const void* dest)
{
  return (unsigned long)dest - (unsigned long)mem - sizeof(unsigned long);
}
inline  BOOL  Hookit(LPVOID mem,LPCVOID hookcode,size_t len)
{
  return WriteProcessMemory(GetCurrentProcess(),mem,hookcode,len,NULL);
}
