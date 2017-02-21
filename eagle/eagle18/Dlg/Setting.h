#pragma once
#include "afxwin.h"

/*设置的类*/
// CSetting 对话框

class CSetting : public CDialog
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetting();

// 对话框数据
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDownloadlist();
	afx_msg void OnBnClickedButtonToprivacy();
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedOk();
	CString m_csDownloadPath;
	afx_msg void OnBnClickedCheckFirstbootdevice();
	CButton m_autoStart;
};
