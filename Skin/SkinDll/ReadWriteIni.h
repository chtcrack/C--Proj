#pragma once

#ifndef __READWRITEINI__
#define __READWRITEINI__

class ReadWriteIni
{
public:
	ReadWriteIni(void);
	~ReadWriteIni(void);
};


/* Get Path */
CString L_path(char* filename);

CString L_Strpath(CString filename);


CString getini(CString filepath,CString key,CString duan);

void saveini(CString filepath,CString key,CString duan,CString word);

#endif