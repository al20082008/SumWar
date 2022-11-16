
// SumWarDlg.h: 標頭檔
//

#pragma once
#include "common.h"
#include "CAppManager.h"
#include "TraceService.h"
#include "WHDataQueue.h"

// CSumWarDlg 對話方塊
class CSumWarDlg : public CDialogEx
{
// 建構
public:
	CSumWarDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUMWAR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLvnColumnclickListInfo(NMHDR* pNMHDR, LRESULT* pResult);
public:
	CListCtrl m_lstApp;
	CAppManager m_appManager;		//創造CAppManager對象
	CTraceServiceControl m_TraceServiceControl;
};

