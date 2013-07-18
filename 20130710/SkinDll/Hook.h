/*! \file hook.h
  \brief hook.h用于执行指定hook、unhook操作
*/
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "common_link.h"

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
//! CPU状态标志寄存器
/*!
英特尔?64和IA-32架构软件developer’s手册,第1卷、基本架构[PDF]
文件名:25366521.pdf 大小:3170961字节 日期:2006年9月 Vol.1 3-21
O  one        Z  zero
S  Indicates a Status Flag
C  Indicates a Control Flag
X  Indicates a System Flag
*/
struct CPU_EFLAGS
{
  unsigned long CF:1;   //!< S  Carry Flag
  unsigned long O1:1;
  unsigned long PF:1;   //!< S  Parity Flag
  unsigned long Z3:1;

  unsigned long AF:1;   //!< S  Auxiliary Carry Flag
  unsigned long Z5:1;
  unsigned long ZF:1;   //!< S  Zero Flag
  unsigned long SF:1;   //!< S  Sign Flag

  unsigned long TF:1;   //!< X  Trap Flag
  unsigned long IF:1;   //!< X  Interrupt Enable Flag
  unsigned long DF:1;   //!< C  Direction Flag
  unsigned long OF:1;   //!< S  Overflow Flag

  unsigned long IOPL:2; //!< X  I/O Privilege Level
  unsigned long NT:1;   //!< X  Nested Task (NT)
  unsigned long Z15:1;

  unsigned long RF:1;   //!< X  Resume Flag
  unsigned long VM:1;   //!< X  Virtual-8086 Mode
  unsigned long AC:1;   //!< X  Alignment Check
  unsigned long VIF:1;  //!< X  Virtual Interrupt Flag

  unsigned long VIP:1;  //!< X  Virtual Interrupt Pending
  unsigned long ID:1;   //!< X  ID Flag
  unsigned long Z22:1;
  unsigned long Z23:1;

  unsigned long Z24:1;
  unsigned long Z25:1;
  unsigned long Z26:1;
  unsigned long Z27:1;

  unsigned long Z28:1;
  unsigned long Z29:1;
  unsigned long Z30:1;
  unsigned long Z31:1;
};
//! 标准回调函数使用的CPU结构
struct CPU_ST
{
  unsigned long regEdi;
  unsigned long regEsi;
  unsigned long regEbp;
  unsigned long regEsp;    //!< 注意esp不能修改，改了也没意义
  unsigned long regEbx;
  unsigned long regEdx;
  unsigned long regEcx;
  unsigned long regEax;
  CPU_EFLAGS regflag;
  unsigned long regEip;
};
//! 回调函数格式
typedef void (__stdcall *HookRoutine)(CPU_ST* cpu);
//! 钩子结点结构，前置声明，不开放定义
struct HookNode;
//! Hook函数
/*!
  指定内存位置与回调函数，执行Hook操作。\n
  当hooksize == 1~4：采用UEF；5：采用jmp XXX；
  6~0xFF：采用jmp dword ptr [XXX]\n
  当hooksize <= 5时，有强制钩子覆盖判定，不可下在已有钩子范围内\n
  \param hookmem   指定hook内存的位置
  \param hooksize  hook长度
  \param routine    指定的回调函数(请参考HookRoutin)
  \param docodeend true：代码后于回调执行，false：代码先行
  \return 钩子结点指针，用于UnHook。\n
          当执行失败时，返回NULL。此时应该调用GetLastHookErr得到失败原因
  \code
    #include "hook.h"
    void __stdcall Routin(CPU_ST* lpcpu)
    {
      return;
    }
    //在0x401000下5 byte JMP XXX钩子，代码先行
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    //在0x401000下6 byte JMP [XXX]钩子，代码先行
    HookNode* node = Hook((void*)0x401000,6,Routin,true);
    //在0x401000下1 byte UEF钩子，代码先行
    HookNode* node = Hook((void*)0x401000,1,Routin,true);
    if(node == NULL)
    {
      cout<<"下钩子出错，错误码："<<GetLastHookErr();
    }
  \endcode
  额外说明：\n
  ●在hook位置复用时，注意根据需要特别注意先后行的选择\n
  ●Routine由于设计及安全上的考虑，Esp值的改变将被忽略。
    其它改变都是允许的，但需要保证程序的继续运行，否则进程崩溃。\n
  ●在Routine内部期望修改EIP以达到流程控制效果时，谨慎选择前后行，
    推荐使用"代码先行"，否则覆盖代码将不被执行。\n
  ●采用异常处理实现存在一定风险。在于：当顶层异常处理被其它处理覆盖时，
    钩子可能失效，并且这时恢复钩子，将破坏当前处理。(当然，概率较小)\n
  ●罕见使用：当希望使用UEF却又需要覆盖hooksize>=5时，
    请在回调函数中设置Eip一样可以实现效果，而不能使hooksize>=5实现UEF。
*/
HookNode* Hook(void* hookmem,
               const unsigned int hooksize,
               HookRoutine routine,
               const bool docodeend
               );
//! 取得Hook函数执行错误码
/*!
  当Hook函数返回NULL时，用于获取详细错误信息
  \return 参考HookErrCode的说明
*/
HookErrCode GetLastHookErr();
//! UnHook函数
/*!
  指定HookNode结点指针，执行UnHook操作。\n
  注意：UnHook函数直接返回Hook错误码，不影响GetLastHookErr\n
  因为卸载钩子会有一些异常情况，强制卸载极可能会造成崩溃，
  所以允许指定错误停止。
  \param node      指定HookNode结点指针
  \param errbreak  指定在卸载钩子遭遇错误时，是否停止卸载
  \return HookErr_Success　      操作成功完成\n
          HookErr_UnHook_Restore 钩子位置已经被还原
          (注意这只是一个Warning不影响卸载的安全性)\n
          HookErr_UnHook_BeCover 钩子位置被覆盖(强制卸载有风险，可停止卸载)\n
          HookErr_UnHook_Write   还原钩子时，写入失败(一般是权限不足)\n
          HookErr_Del_NoExist    钩子不存在于链表\n
          HookErr_Unkown         未知异常(可能是个非法的HookNode)
  \code
    #include "hook.h"
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    if(node == NULL) return;
    cout<<"卸载钩子："<<UnHook(node,false);
  \endcode
*/
HookErrCode Unhook(HookNode* node,const bool errbreak);
//! 还原全部钩子
/*!
  注意HookClear执行的是强制卸载操作，会尝试卸载链表中的每个钩子\n
  注意：HookClear函数也直接返回Hook错误码，不影响GetLastHookErr\n
  一般应用于动态库卸载的清理流程中。
  \return HookClear返回的是最后一个卸载错误码\n
          HookErr_Clear_UEF 清理UEF时，发现UEF被覆盖\n
          其它错误码请参考UnHook的返回值说明
*/
HookErrCode HookClear();
//! 偏移计算
/*!
  内联函数，用于计算偏移值
  \param mem   需要偏移处地址
  \param dest  跳转目标处地址
  \return 偏移值
*/
inline unsigned long CalcHookOffset(const void* mem,const void* dest)
{
  return (unsigned long)dest - (unsigned long)mem - sizeof(unsigned long);
}
//! 写内存的封装
/*!
  内联函数，指定地址以及缓冲区，写入内存
  \param mem        指定地址
  \param hookcode   缓冲区
  \param len        缓冲区大小
  \return 写操作的执行结果
*/
inline  BOOL  Hookit(LPVOID mem,LPCVOID hookcode,size_t len)
{
  return WriteProcessMemory(GetCurrentProcess(),mem,hookcode,len,NULL);
}