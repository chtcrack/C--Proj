/*! \file common_link.h
  \brief  Ϊ��̬���ṩ�Զ����ӻ��ơ�

  ע�⣺��ͷ�ļ�����������Σ����û�а���������

  ���Ը��ݵ�ǰ���̵ı���ѡ�����ӵ���ȷ�汾�ľ�̬�⡣
  ������������ϵ���ߣ����ǲο�boost����Զ����ӻ��ơ�

  \code
  #include "common_link.h" //���ݵ�ǰ���̵ı���ѡ�����ӵ�"CommonMT.lib","CommonMTd.lib","CommonMD.lib","CommonMDd.lib"��4����̬�������һ����
  \endcode

  \author   uni
  \date     2011-4-8
*/
#ifndef COMMON_LIB_ALREADY_LINK
#  define COMMON_LIB_ALREADY_LINK

#  define COMMON_VER "(ver 1.0.1111.1111)"

#  if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG)
#    pragma message("ʹ�� /RTC ѡ�����ָ��һ�����԰汾������ʱ��ᵼ�����Ӵ���")
#    pragma message("��ʾ�� �ڴ���������ѡ��һ�����԰汾������ʱ��")
#    error "�����ݵı���ѡ��"
#  endif

#  ifdef _DLL

#    if defined(_DEBUG)
#      define AUTO_LINK_RUNTIME_OPTION "MDd"
#    else
#      define AUTO_LINK_RUNTIME_OPTION "MD"
#    endif

#  else

#    if defined(_DEBUG)
#      define AUTO_LINK_RUNTIME_OPTION "MTd"
#    else
#      define AUTO_LINK_RUNTIME_OPTION "MT"
#    endif

#  endif    //#ifdef _DLL

#  pragma message("���ӵ�lib�ļ�: Common"AUTO_LINK_RUNTIME_OPTION".lib "COMMON_VER)
#  pragma comment(lib,"Common"AUTO_LINK_RUNTIME_OPTION)

#  undef COMMON_VER
#  undef AUTO_LINK_RUNTIME_OPTION

#endif  //#ifndef COMMON_LIB_ALREADY_LINK
