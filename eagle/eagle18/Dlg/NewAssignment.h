#pragma once
//////////////////////////////////////////////////////////////////
/*�½��������,�Ѿ�����Ҫ�������ˣ�*/
// CNewAssignment �Ի���
////////////////////////////////////////////////////////////////////
class CNewAssignment : public CDialog
{
	DECLARE_DYNAMIC(CNewAssignment)

public:
	CNewAssignment(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewAssignment();

// �Ի�������
	enum { IDD = IDD_NEWASSIGNMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_csDownload;
	CString m_csFileName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonSave();
	CString m_csDownloadPath;
	CString m_csFileSize;
};
