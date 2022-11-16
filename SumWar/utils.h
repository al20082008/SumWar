#pragma once

#include "common.h"


void mlclick(long x, long y, int = 1);
CStringA GetRunPath();
CString inttoCString(int aa);
void Split_CString(CString strSrc, CStringArray& dstArray, CString strDiv);
int execmd(char* cmd, char* result);
CString ExeCmd(CString pszCmd);

