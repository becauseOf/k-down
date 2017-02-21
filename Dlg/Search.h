#pragma once
#include "afxcmn.h"
#include"SendSocket.h"
#include "btnst.h"

// CSearch 对话框

class CSearch : public CDialog
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = NULL);   // 标准构造函数

	virtual ~CSearch();

// 对话框数据
	enum { IDD = IDD_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	
	afx_msg void OnLvnItemchangedListSearch(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
// 用于展示搜索内容的表
	CListCtrl m_SearchList;
	// 搜索的关键字
	CString m_csSearchMessage;
	afx_msg void OnBnClickedButtonSearch();
	// 用于发送的套接字
	CWnd* m_pParent;
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButtonST m_btnSearch;
	CButtonST m_btnDownload;
};
