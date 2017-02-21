#pragma once


// CSetIP 对话框

class CSetIP : public CDialog
{
	DECLARE_DYNAMIC(CSetIP)

public:
	CSetIP(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetIP();

// 对话框数据
	enum { IDD = IDD_SETIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 服务器IP地址
	CString m_csIP;
	afx_msg void OnBnClickedOk();
};
