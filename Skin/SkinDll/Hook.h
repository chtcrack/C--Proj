

////////////////////////////////////////Hook����////////////////////////////////////
/*!
  ָ���ڴ�λ����ص�������ִ��Hook������\n
  ��hooksize == 1~4������UEF��5������jmp XXX��6~0xFF������jmp dword ptr [XXX]\n
  ��hooksize <= 5ʱ����ǿ�ƹ��Ӹ����ж��������������й��ӷ�Χ��\n
  ��hookλ�ø���ʱ��ע�������Ҫ�ر�ע���Ⱥ��е�ѡ��\n
  ����ʹ�ã���ϣ��ʹ��UEFȴ����Ҫ����hooksize>=5ʱ�����ڻص�����������Eipһ������ʵ��Ч����������ʹhooksize>=5ʵ��UEF��
  \param hookmem   ָ��hook�ڴ��λ��
  \param hooksize  hook����
  \param routin    ָ���Ļص�����(��ο�HookRoutin)
  \param docodeend true�����ǵĴ�����ڻص�ִ�У�false�����ǵĴ������ڻص�ִ��
  \return ���ӽ��ָ�룬����UnHook��\n
          ��ִ��ʧ��ʱ������kErrHookNode����ʱӦ�õ���GetLastHookErr�õ�ʧ��ԭ��



  ����:
    #include "hook.h"
    void __stdcall Routin(CPU_ST* lpcpu)
    {
      return;
    }
    HookNode* node = Hook((void*)0x401000,5,Routin,false);  //��0x401000��5 byte JMP XXX���ӣ���������
    HookNode* node = Hook((void*)0x401000,6,Routin,true);   //��0x401000��6 byte JMP [XXX]���ӣ���������
    HookNode* node = Hook((void*)0x401000,1,Routin,true);   //��0x401000��1 byte UEF���ӣ���������
    if(node == kErrHookNode)
    {
      cout<<"�¹��ӳ��������룺"<<GetLastHookErr();
    }
*/



////////////////////////////////////////UnHook����////////////////////////////////////
/*!
  ָ��HookNode���ָ�룬ִ��UnHook������\n
  ע�⣺UnHook����ֱ�ӷ���Hook�����룬��Ӱ��GetLastHookErr\n
  ��Ϊж�ع��ӻ���һЩ�쳣�����ǿ��ж�ؼ����ܻ���ɱ��������Կ���ָ������ֹͣ��
  \param node      ָ��HookNode���ָ��
  \param errbreak  ָ����ж�ع�����������ʱ���Ƿ�ֹͣж��
  \return HookErr_Success��      �����ɹ����\n
          HookErr_UnHook_Restore ����λ���Ѿ�����ԭ(ע����ֻ��һ��Warning��Ӱ��ж�صİ�ȫ��)\n
          HookErr_UnHook_BeCover ����λ�ñ�����(ǿ��ж���з��գ���ֹͣж��)\n
          HookErr_UnHook_Write   ��ԭ����ʱ��д��ʧ��(һ����Ȩ�޲���)\n
          HookErr_Del_NoExist    ���Ӳ�����������\n
          HookErr_Unkown         δ֪�쳣(�����Ǹ��Ƿ���HookNode)
  
  ����:
    #include "hook.h"
    HookNode* node = Hook((void*)0x401000,5,Routin,false);
    if(node == kErrHookNode) return;
    cout<<"ж�ع��ӣ�"<<Unhook(node,false);
*/


#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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

#pragma warning(push)
#pragma warning(disable:4510)  //warning C4510: ��cpu_st��: δ������Ĭ�Ϲ��캯��
#pragma warning(disable:4512)  //warning C4512: ��cpu_st��: δ�����ɸ�ֵ�����
#pragma warning(disable:4610)  //warning C4610: struct��cpu_st����Զ����ʵ���� - ��Ҫ�û�����Ĺ��캯��
//! ��׼�ص�����ʹ�õ�CPU�ṹ
struct CPU_ST
{
  unsigned long regEdi;
  unsigned long regEsi;
  unsigned long regEbp;
  const unsigned long regEsp;    //!< ע��esp�����޸ģ�����Ҳû����
  unsigned long regEbx;
  unsigned long regEdx;
  unsigned long regEcx;
  unsigned long regEax;
  unsigned long regf;
  unsigned long regEip;
};
#pragma warning(pop)
//! �ص�������ʽ
typedef void (__stdcall *HookRoutin)(CPU_ST* cpu);
//! ���ӽ��ṹ��ǰ�������������Ŷ���
struct HookNode;
//! �Ƿ����ӽ�㶨�壬���ڱ�ʶHookʧ��
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
