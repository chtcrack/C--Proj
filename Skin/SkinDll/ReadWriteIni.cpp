#include "StdAfx.h"
#include "ReadWriteIni.h"
//#include "../UdpSend.h"

ReadWriteIni::ReadWriteIni(void)
{
}


ReadWriteIni::~ReadWriteIni(void)
{
}


/* Get Path */
CString L_path(char* filename)
{

	CString   str,path; 
	path=AfxGetApp()-> m_pszHelpFilePath; 
	str=AfxGetApp()-> m_pszExeName; 
	path=path.Left(path.GetLength()-str.GetLength()-4);
	path.Format("%s%s",path,filename);

	return path;
}

CString L_Strpath(CString filename)
{

	CString   str,path; 
	path=AfxGetApp()-> m_pszHelpFilePath; 
	str=AfxGetApp()-> m_pszExeName; 
	path=path.Left(path.GetLength()-str.GetLength()-4);
	path.Format("%s%s",path,filename);
	return path;
}


CString getini(CString filepath,CString key,CString duan)
{

	CString file = filepath;
	char* cfile  = (LPSTR)(LPCSTR)file;

	

	int count=0;
	char buf[1024];
	CString Str;
	CString	csMapFilePath=	L_path(cfile);

	count = GetPrivateProfileString(key,duan,"", buf,sizeof(buf),csMapFilePath);
	Str.Format("%s",buf);
	return Str;
}

void saveini(CString filepath,CString key,CString duan,CString word)
{
	CString file = filepath;
	char* cfile  = (LPSTR)(LPCSTR)file;

	CString strFilename;
	CString	csMapFilePath=	L_path(cfile);
	WritePrivateProfileString(key,duan,word,csMapFilePath);
	return;
}