#pragma once

/*隐私空间弹窗的类*/
// CPrivacyDialog 对话框

class CPrivacyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrivacyDialog)

public:
	CPrivacyDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivacyDialog();

// 对话框数据
	enum { IDD = IDD_PRIVACYHOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csPrivacyPassword;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
