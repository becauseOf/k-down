#pragma once


// CChangePassword 对话框

class CChangePassword : public CDialog
{
	DECLARE_DYNAMIC(CChangePassword)

public:
	CChangePassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangePassword();

// 对话框数据
	enum { IDD = IDD_CHANGEPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csChangePassword;
	CString m_csLastPassword;
	CString m_csPasswordOK;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
