#pragma once


// CSetIP �Ի���

class CSetIP : public CDialog
{
	DECLARE_DYNAMIC(CSetIP)

public:
	CSetIP(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetIP();

// �Ի�������
	enum { IDD = IDD_SETIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ������IP��ַ
	CString m_csIP;
	afx_msg void OnBnClickedOk();
};
