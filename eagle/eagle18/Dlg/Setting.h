#pragma once
#include "afxwin.h"

/*���õ���*/
// CSetting �Ի���

class CSetting : public CDialog
{
	DECLARE_DYNAMIC(CSetting)

public:
	CSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetting();

// �Ի�������
	enum { IDD = IDD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
