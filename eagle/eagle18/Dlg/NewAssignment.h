#pragma once
//////////////////////////////////////////////////////////////////
/*新建任务的类,已经不需要这个类的了！*/
// CNewAssignment 对话框
////////////////////////////////////////////////////////////////////
class CNewAssignment : public CDialog
{
	DECLARE_DYNAMIC(CNewAssignment)

public:
	CNewAssignment(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewAssignment();

// 对话框数据
	enum { IDD = IDD_NEWASSIGNMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
