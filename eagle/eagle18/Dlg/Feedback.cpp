// Feedback.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "Feedback.h"


// CFeedback 对话框

IMPLEMENT_DYNAMIC(CFeedback, CDialog)

CFeedback::CFeedback(CWnd* pParent /*=NULL*/)
	: CDialog(CFeedback::IDD, pParent)
	, m_csFeedback(_T(""))
{

}

CFeedback::~CFeedback()
{
}

void CFeedback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FEEDBACK, m_csFeedback);
}


BEGIN_MESSAGE_MAP(CFeedback, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACKSUBMIT, &CFeedback::OnBnClickedButtonFeedbacksubmit)
END_MESSAGE_MAP()


// CFeedback 消息处理程序

BOOL CFeedback::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFeedback::OnBnClickedButtonFeedbacksubmit()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(m_csFeedback == "")
	{
		MessageBox(_T("你并没有输入反馈内容啊"),_T("提醒"),MB_OK|MB_ICONQUESTION);
		return;
	}
	INT_PTR iRes;
	iRes = MessageBox(_T("您确定要提交反馈内容了嘛？"),_T("反馈"),MB_OKCANCEL);
	if (iRes == IDOK)
	{
		MessageBox(_T("感谢您的支持,您的反馈意见已经成功提交"));
		OnOK();
	}
	else
	{
		return;
	}

}
