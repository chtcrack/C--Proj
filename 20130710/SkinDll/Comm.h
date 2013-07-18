#pragma once



char* UnicodeToBIG5(const wchar_t* szUnicodeString);
char* UnicodeToGB2312(const wchar_t* szUnicodeString);
wchar_t* GB2312ToUnicode(const char* szGBString);
char* GB2312ToBIG5(const char* szGBString);
char* BIG5ToGB2312(const char* szBIG5String);
char* GB2312ToBIG5(const char* szGBString);

