/*! \file common_link.h
  \brief  为静态库提供自动链接机制。

  注意：该头文件允许被包含多次，因此没有包含保护。

  可以根据当前工程的编译选项连接到正确版本的静态库。
  具体作用请联系作者，或是参考boost库的自动链接机制。

  \code
  #include "common_link.h" //根据当前工程的编译选项连接到"CommonMT.lib","CommonMTd.lib","CommonMD.lib","CommonMDd.lib"这4个静态库的其中一个。
  \endcode

  \author   uni
  \date     2011-4-8
*/
#ifndef COMMON_LIB_ALREADY_LINK
#  define COMMON_LIB_ALREADY_LINK

#  define COMMON_VER "(ver 1.0.1111.1111)"

#  if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG)
#    pragma message("使用 /RTC 选项而不指定一个调试版本的运行时库会导致连接错误")
#    pragma message("提示： 在代码生成中选择一个调试版本的运行时库")
#    error "不兼容的编译选项"
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

#  pragma message("连接到lib文件: Common"AUTO_LINK_RUNTIME_OPTION".lib "COMMON_VER)
#  pragma comment(lib,"Common"AUTO_LINK_RUNTIME_OPTION)

#  undef COMMON_VER
#  undef AUTO_LINK_RUNTIME_OPTION

#endif  //#ifndef COMMON_LIB_ALREADY_LINK
