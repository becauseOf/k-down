#pragma once

/*��˽�ռ����õ���*/
// CPrivacyPassword �Ի���

class CPrivacyPassword : public CDialog
{
	DECLARE_DYNAMIC(CPrivacyPassword)

public:
	CPrivacyPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrivacyPassword();

// �Ի�������
	enum { IDD = IDD_PRIVACYPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
