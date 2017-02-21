#pragma once

/*隐私空间设置的类*/
// CPrivacyPassword 对话框

class CPrivacyPassword : public CDialog
{
	DECLARE_DYNAMIC(CPrivacyPassword)

public:
	CPrivacyPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivacyPassword();

// 对话框数据
	enum { IDD = IDD_PRIVACYPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csPrivacyPassword;
	CString m_csNewPassword;
	CString m_csPassword;
	CString m_csLastPassword;
	afx_msg void OnEnChangeEditNewpassword();
	virtual BOOL OnInitDialog();
	CString m_csPrivacyPasswordOK;
	afx_msg void OnEnChangeEditPrivacypassword();
	afx_msg void OnEnChangeEditPasswordok();
	CString m_csPasswordOK;
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
