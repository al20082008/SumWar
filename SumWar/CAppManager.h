#pragma once
#include "common.h"
#include "struct.h"


//CMap����
typedef CMap<int, int, tagAppItem*, tagAppItem*> CMapApp;



class CAppManager
{
public:
	CAppManager();
	CString GetAppInfo();

public:
	CString m_strLDPath;
	CMapApp m_appMap;	//����CMap��������


};

