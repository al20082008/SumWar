#pragma once
#include "common.h"
#include "struct.h"


//CMapÈİÆ÷
typedef CMap<int, int, tagAppItem*, tagAppItem*> CMapApp;



class CAppManager
{
public:
	CAppManager();
	CString GetAppInfo();

public:
	CString m_strLDPath;
	CMapApp m_appMap;	//„“ÔìCMapÈİÆ÷Œ¦Ïó


};

