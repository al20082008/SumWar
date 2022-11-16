#pragma once
#include "common.h"
#include "scommon.h"

void mlclick(long x,long y,int =1);
CStringA GetRunPath();
CString inttoCString(int aa);
void Split_CString(CString strSrc, CStringArray& dstArray, CString strDiv);
int execmd(char* cmd, char* result);
