#pragma once

/*��˽�ռ䵯������*/
// CPrivacyDialog �Ի���

class CPrivacyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPrivacyDialog)

public:
	CPrivacyDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrivacyDialog();

// �Ի�������
	enum { IDD = IDD_PRIVACYHOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_csPrivacyPassword;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
