#pragma once

/*用户反馈的类*/
// CFeedback 对话框

class CFeedback : public CDialog
{
	DECLARE_DYNAMIC(CFeedback)

public:
	CFeedback(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFeedback();

// 对话框数据
	enum { IDD = IDD_FEEDBACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// //用户反馈的内容
	CString m_csFeedback;
	afx_msg void OnBnClickedButtonFeedbacksubmit();
};
