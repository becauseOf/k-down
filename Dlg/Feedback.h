#pragma once
#include "btnst.h"

/*�û���������*/
// CFeedback �Ի���

class CFeedback : public CDialog
{
	DECLARE_DYNAMIC(CFeedback)

public:
	CFeedback(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFeedback();

// �Ի�������
	enum { IDD = IDD_FEEDBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// //�û�����������
	CString m_csFeedback;
	afx_msg void OnBnClickedButtonFeedbacksubmit();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButtonST m_btnOK;
	CButtonST m_btnCancel;
};
