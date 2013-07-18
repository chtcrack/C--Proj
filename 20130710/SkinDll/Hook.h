/*! \file hook.h
  \brief hook.h����ִ��ָ��hook��unhook����
*/
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "common_link.h"

//! Hook������
enum  HookErrCode
{
  HookErr_Success,           //!< Hook�ɹ����
  HookErr_HookSize_0,        //!< hooksizeΪ0
  HookErr_HookSize_OverFlow, //!< hooksize����(�������Ϊ0xFF)
  HookErr_HookMem_Read,      //!< hookmem���Զ�ȡʧ��(һ���ǵ�ַ�Ƿ�)
  HookErr_HookMem_Write,     //!< hookmem����д��ʧ��(һ����Ȩ�޲���)
  HookErr_Routin,            //!< Routin��ַ�Ƿ�
  HookErr_Del_NoExist,       //!< ɾ��ʱָ�����Ӳ�����
  HookErr_Hook_Write,        //!< д�빳��ʧ��(һ����Ȩ�޲���)
  HookErr_Hook_Cover,        //!< ���Ѵ��ڵĹ���λ���г�ͻ
  HookErr_UnHook_Restore,    //!< �����Ѿ�����ԭ
  HookErr_UnHook_BeCover,    //!< ����λ�ñ�����
  HookErr_UnHook_Write,      //!< ���ӻ�ԭʱдʧ��(һ����Ȩ�޲���)
  HookErr_Clear_UEF,         //!< ��ԭUEFʧ��(һ����UEF������)
  HookErr_Unkown,            //!< δ֪�쳣
};
//! CPU״̬��־�Ĵ���
/*!
Ӣ�ض�?64��IA-32�ܹ����developer��s�ֲ�,��1�������ܹ�[PDF]
�ļ���:25366521.pdf ��С:3170961�ֽ� ����:2006��9�� Vol.1 3-21
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
//! ��׼�ص�����ʹ�õ�CPU�ṹ
struct CPU_ST
{
  unsigned long regEdi;
  unsigned long regEsi;
  unsigned long regEbp;
  unsigned long regEsp;    //!< ע��esp�����޸ģ�����Ҳû����
  unsigned long regEbx;
  unsigned long regEdx;
  unsigned long regEcx;
  unsigned long regEax;
  CPU_EFLAGS regflag;
  unsigned long regEip;
};
//! �ص�������ʽ
typedef void (__stdcall *HookRoutine)(CPU_ST* cpu);
//! ���ӽ��ṹ��ǰ�������������Ŷ���
struct HookNode;
//! Hook����
/*!
  ָ���ڴ�λ����ص�������ִ��Hook������\n
  ��hooksize == 1~4������UEF��5������jmp XXX��
  6~0xFF������jmp dword ptr [XXX]\n
  ��hooksize <= 5ʱ����ǿ�ƹ��Ӹ����ж��������������й��ӷ�Χ��\n
  \param hookmem   ָ��hook�ڴ��λ��
  \param hooksize  hook����
  \param routine    ָ���Ļص�����(��ο�HookRoutin)
  \param docodeend true��������ڻص�ִ�У�false����������
  \return ���ӽ��ָ�룬����UnHook��\n
          ��ִ��ʧ��ʱ������NULL����ʱӦ�õ���GetLastHookErr�õ�ʧ��ԭ��
  \code
    #include "hook.h"
    void __stdcall Routin(CPU_ST* lpcpu)
    {
      return;
    }
    //��0x401000��5 byte JMP XXX���ӣ���������
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    //��0x401000��6 byte JMP [XXX]���ӣ���������
    HookNode* node = Hook((void*)0x401000,6,Routin,true);
    //��0x401000��1 byte UEF���ӣ���������
    HookNode* node = Hook((void*)0x401000,1,Routin,true);
    if(node == NULL)
    {
      cout<<"�¹��ӳ��������룺"<<GetLastHookErr();
    }
  \endcode
  ����˵����\n
  ����hookλ�ø���ʱ��ע�������Ҫ�ر�ע���Ⱥ��е�ѡ��\n
  ��Routine������Ƽ���ȫ�ϵĿ��ǣ�Espֵ�ĸı佫�����ԡ�
    �����ı䶼������ģ�����Ҫ��֤����ļ������У�������̱�����\n
  ����Routine�ڲ������޸�EIP�Դﵽ���̿���Ч��ʱ������ѡ��ǰ���У�
    �Ƽ�ʹ��"��������"�����򸲸Ǵ��뽫����ִ�С�\n
  ������쳣����ʵ�ִ���һ�����ա����ڣ��������쳣��������������ʱ��
    ���ӿ���ʧЧ��������ʱ�ָ����ӣ����ƻ���ǰ����(��Ȼ�����ʽ�С)\n
  �񺱼�ʹ�ã���ϣ��ʹ��UEFȴ����Ҫ����hooksize>=5ʱ��
    ���ڻص�����������Eipһ������ʵ��Ч����������ʹhooksize>=5ʵ��UEF��
*/
HookNode* Hook(void* hookmem,
               const unsigned int hooksize,
               HookRoutine routine,
               const bool docodeend
               );
//! ȡ��Hook����ִ�д�����
/*!
  ��Hook��������NULLʱ�����ڻ�ȡ��ϸ������Ϣ
  \return �ο�HookErrCode��˵��
*/
HookErrCode GetLastHookErr();
//! UnHook����
/*!
  ָ��HookNode���ָ�룬ִ��UnHook������\n
  ע�⣺UnHook����ֱ�ӷ���Hook�����룬��Ӱ��GetLastHookErr\n
  ��Ϊж�ع��ӻ���һЩ�쳣�����ǿ��ж�ؼ����ܻ���ɱ�����
  ��������ָ������ֹͣ��
  \param node      ָ��HookNode���ָ��
  \param errbreak  ָ����ж�ع�����������ʱ���Ƿ�ֹͣж��
  \return HookErr_Success��      �����ɹ����\n
          HookErr_UnHook_Restore ����λ���Ѿ�����ԭ
          (ע����ֻ��һ��Warning��Ӱ��ж�صİ�ȫ��)\n
          HookErr_UnHook_BeCover ����λ�ñ�����(ǿ��ж���з��գ���ֹͣж��)\n
          HookErr_UnHook_Write   ��ԭ����ʱ��д��ʧ��(һ����Ȩ�޲���)\n
          HookErr_Del_NoExist    ���Ӳ�����������\n
          HookErr_Unkown         δ֪�쳣(�����Ǹ��Ƿ���HookNode)
  \code
    #include "hook.h"
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    if(node == NULL) return;
    cout<<"ж�ع��ӣ�"<<UnHook(node,false);
  \endcode
*/
HookErrCode Unhook(HookNode* node,const bool errbreak);
//! ��ԭȫ������
/*!
  ע��HookClearִ�е���ǿ��ж�ز������᳢��ж�������е�ÿ������\n
  ע�⣺HookClear����Ҳֱ�ӷ���Hook�����룬��Ӱ��GetLastHookErr\n
  һ��Ӧ���ڶ�̬��ж�ص����������С�
  \return HookClear���ص������һ��ж�ش�����\n
          HookErr_Clear_UEF ����UEFʱ������UEF������\n
          ������������ο�UnHook�ķ���ֵ˵��
*/
HookErrCode HookClear();
//! ƫ�Ƽ���
/*!
  �������������ڼ���ƫ��ֵ
  \param mem   ��Ҫƫ�ƴ���ַ
  \param dest  ��תĿ�괦��ַ
  \return ƫ��ֵ
*/
inline unsigned long CalcHookOffset(const void* mem,const void* dest)
{
  return (unsigned long)dest - (unsigned long)mem - sizeof(unsigned long);
}
//! д�ڴ�ķ�װ
/*!
  ����������ָ����ַ�Լ���������д���ڴ�
  \param mem        ָ����ַ
  \param hookcode   ������
  \param len        ��������С
  \return д������ִ�н��
*/
inline  BOOL  Hookit(LPVOID mem,LPCVOID hookcode,size_t len)
{
  return WriteProcessMemory(GetCurrentProcess(),mem,hookcode,len,NULL);
}