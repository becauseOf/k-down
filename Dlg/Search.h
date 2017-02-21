#pragma once
#include "afxcmn.h"
#include"SendSocket.h"
#include "btnst.h"

// CSearch �Ի���

class CSearch : public CDialog
{
	DECLARE_DYNAMIC(CSearch)

public:
	CSearch(CWnd* pParent = NULL);   // ��׼���캯��

	virtual ~CSearch();

// �Ի�������
	enum { IDD = IDD_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	
	afx_msg void OnLvnItemchangedListSearch(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
// ����չʾ�������ݵı�
	CListCtrl m_SearchList;
	// �����Ĺؼ���
	CString m_csSearchMessage;
	afx_msg void OnBnClickedButtonSearch();
	// ���ڷ��͵��׽���
	CWnd* m_pParent;
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButtonST m_btnSearch;
	CButtonST m_btnDownload;
};
