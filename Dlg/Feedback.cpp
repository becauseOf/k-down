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
	DDX_Control(pDX, IDC_BUTTON_FEEDBACKSUBMIT, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CFeedback, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACKSUBMIT, &CFeedback::OnBnClickedButtonFeedbacksubmit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFeedback 消息处理程序

BOOL CFeedback::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnOK.SetIcon(IDI_ICON_RIGHT1);
	m_btnOK.DrawTransparent(TRUE);

	m_btnCancel.SetIcon(IDI_ICON_CANCEL1);
	m_btnCancel.DrawTransparent(TRUE);

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

HBRUSH CFeedback::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if (pWnd == this)
	{
		HBRUSH b=CreateSolidBrush(RGB(255,255,255));
		return b;
	}
	if(nCtlColor ==CTLCOLOR_STATIC)
	{
		pDC ->SetBkColor(RGB(255,255,255));
		HBRUSH b = CreateSolidBrush(RGB(255,255,255));
		return b;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
