#pragma once


// CChangePassword �Ի���

class CChangePassword : public CDialog
{
	DECLARE_DYNAMIC(CChangePassword)

public:
	CChangePassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePassword();

// �Ի�������
	enum { IDD = IDD_CHANGEPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
