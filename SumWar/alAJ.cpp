
#include "pch.h"			//MFC的頭文件
#include "alAJ.h"
#include <stdio.h>
#include <string.h>


void mlclick(long x, long y, int t)
{
	for (int i = 0; i < t; i++)
	{
	al->MoveTo(x, y);
	al->LeftClick();	
	}
}

CStringA GetRunPath()
{
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//刪除檔名，只獲得路徑 字串
	CStringA strPath;
	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\\\");
		}
	}
	return strPath;
}

//將int轉為CString
CString inttoCString(int aa)
{
	CString str;
	str.Format(_T("%d"), aa);
	return str;
}


void Split_CString(CString strSrc, CStringArray& dstArray, CString strDiv)
{
	int iPos = 0;
	CString strTmp;
	strTmp = strSrc.Tokenize(strDiv, iPos);
	while (strTmp.Trim() != _T(""))
	{
		dstArray.Add(strTmp);
		strTmp = strSrc.Tokenize(strDiv, iPos);
	}
}

int execmd(char* cmd, char* result) {
	char buffer[128];
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return 0;
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe)) {
			strcat(result, buffer);
		}
	}
	_pclose(pipe);
	return 1;
}

