#pragma once

#include "pch.h"
#include "common.h"


struct tagAppItem {
	int id;
	CString strName;

	HWND hTop;
	HWND hBind;
	bool bAndroid;;
	int iProcessID;
	int iVBoxProcessID;
	CRect rtTopWnd;
	CRect rtBindWnd;
};
