#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS
// SumWarDlg.cpp: 實作檔案
//
#include "pch.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




CSumWarDlg::CSumWarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUMWAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSumWarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_lstApp);
	DDX_Control(pDX, IDC_TRACE_MESSAGE, m_TraceServiceControl);
}

BEGIN_MESSAGE_MAP(CSumWarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_INFO, &CSumWarDlg::OnLvnColumnclickListInfo)
END_MESSAGE_MAP()

#define UPDATE_APPINFO_ID 1

// CSumWarDlg 訊息處理常式




BOOL CSumWarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此加入額外的初始設定

	//AllocConsole();						//MFC控制台
	//freopen("CONOUT$", "w", stdout);



	//m_lstApp是窗口List Control(IDC_LIST_INFO)的關聯變數
	//下面是調整它的屬性
	DWORD dwStyle = m_lstApp.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_CHECKBOXES;
	m_lstApp.SetExtendedStyle(dwStyle);
	m_lstApp.InsertColumn(0, _T("序列"), LVCFMT_CENTER, 80);
	m_lstApp.InsertColumn(1, _T("模拟器"), LVCFMT_CENTER, 110);
	m_lstApp.InsertColumn(2, _T("模拟器句柄"), LVCFMT_CENTER, 100);
	m_lstApp.InsertColumn(3, _T("..."), LVCFMT_CENTER, 300);


	SetTimer(UPDATE_APPINFO_ID, 1000, NULL);
	
	//CAppManager appManager;
	//appManager.GetAppInfo();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CSumWarDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CSumWarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSumWarDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	LogN(_T("Test"));
	if (nIDEvent == UPDATE_APPINFO_ID)
	{
		
		m_appManager.GetAppInfo();

		int iItemIndex = 0L;
		tagAppItem* pItem = NULL;
		POSITION Position = m_appManager.m_appMap.GetStartPosition();
		while (Position != NULL)
		{
			m_appManager.m_appMap.GetNextAssoc(Position, iItemIndex, pItem);

			bool bExist = false;
			for (int i = 0; i < m_lstApp.GetItemCount(); i++)
			{
				if (_ttoi(m_lstApp.GetItemText(i, 0)) == pItem->id)
				{
					bExist = true;

					CString strBind;
					strBind.Format(_T("0x%x"), pItem->hBind);
					m_lstApp.SetItemText(i, 2, strBind);
				}
			}

			if (!bExist)
			{
				int iRow = m_lstApp.GetItemCount();
				m_lstApp.InsertItem(iRow, _T(""));

				CString strId;
				strId.Format(_T("%d"), pItem->id);

				m_lstApp.SetItemText(iRow, 0, strId);
				m_lstApp.SetItemText(iRow, 1, pItem->strName);

				CString strBind;
				strBind.Format(_T("0x%x"), pItem->hBind);
				m_lstApp.SetItemText(iRow, 2, strBind);
			}
		}


	}



	CDialogEx::OnTimer(nIDEvent);
}


//點擊標排序
DWORD dwSelColID = 0;
bool bASC = true;
int static CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*)lParamSort;
	LVFINDINFO findInfo;
	findInfo.flags = LVFI_PARAM;
	findInfo.lParam = lParam1;
	int iItem1 = pListCtrl->FindItem(&findInfo, -1);

	findInfo.lParam = lParam2;
	int iItem2 = pListCtrl->FindItem(&findInfo, -1);

	CString strItem1 = pListCtrl->GetItemText(iItem1, dwSelColID);
	CString strItem2 = pListCtrl->GetItemText(iItem2, dwSelColID);

	int iItem1Value = _ttoi(strItem1);
	int iItem2Value = _ttoi(strItem2);

	if (bASC)
		return iItem1Value > iItem2Value;
	else
		return iItem1Value < iItem2Value;
}


void CSumWarDlg::OnLvnColumnclickListInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼


	
//////////////////////////////////////////////////////

	//點擊標排序
	
	//if (pNMLV->iSubItem != 0) //只排序指定列
	//{
	//	return;
	//}

	if (dwSelColID != pNMLV->iSubItem)
	{
		dwSelColID = pNMLV->iSubItem;
		bASC = bASC;
	}
	else
		bASC = !bASC;

	int count = m_lstApp.GetItemCount();
	for (int i = 0; i < count; i++)
		m_lstApp.SetItemData(i, i);

	m_lstApp.SortItems(CompareFunc, (LPARAM)(&m_lstApp));
///////////////////////////////////////////////////////////

	*pResult = 0;
}


