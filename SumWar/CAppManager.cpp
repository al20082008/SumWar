#include "pch.h"		//MFC
#include "common.h"






CAppManager::CAppManager()
{
    m_strLDPath = _T("A:\\leidian\\LDPlayer4\\ldconsole.exe");
}

CString CAppManager::GetAppInfo()
{
    CString ldcmdcode = _T(" list2");
    CString cmdpath = m_strLDPath+= ldcmdcode;
    
    CString exeret=ExeCmd(cmdpath);


    CStringArray ldresult;
    CString ldsign;

    ldsign = _T("\r\n");
    Split_CString(exeret, ldresult, ldsign);

    for (int i = 0; i < ldresult.GetCount(); i++)
    {
        CString strVm = ldresult[i];
        CString strTmp;


        /* e.g. strTmp={a,b,c}
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 0, _T(',') 
        代表以","分割第0個放入strTmp
        */

        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 0, _T(','));
        int id = _ttoi(strTmp);
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 1, _T(','));
        CString strName = strTmp;
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 2, _T(','));
        HWND hTop = (HWND)_ttoi(strTmp);
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 3, _T(','));
        HWND hBind = (HWND)_ttoi(strTmp);
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 4, _T(','));
        bool bAndroid = _ttoi(strTmp) == 1 ? true : false;
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 5, _T(','));
        int iProcessID = _ttoi(strTmp);
        AfxExtractSubString(strTmp, (LPCTSTR)strVm, 6, _T(','));
        int iVBoxProcessID = _ttoi(strTmp);

        tagAppItem* pItem = NULL;
        m_appMap.Lookup(id, pItem);
        if (pItem == NULL)
        {
            pItem = new tagAppItem;

            pItem->id = id;
            pItem->strName = strName;

            m_appMap[id] = pItem;
        }

        pItem->hTop = hTop;
        pItem->hBind = hBind;
        pItem->bAndroid = bAndroid;
        pItem->iProcessID = iProcessID;
        pItem->iVBoxProcessID = iVBoxProcessID;

        TRACE(ldresult[i]+= _T("\r\n"));
    }

    return CString();
}


