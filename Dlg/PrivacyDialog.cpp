// PrivacyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "PrivacyDialog.h"


// CPrivacyDialog 对话框

IMPLEMENT_DYNAMIC(CPrivacyDialog, CDialog)

CPrivacyDialog::CPrivacyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivacyDialog::IDD, pParent)
	, m_csPrivacyPassword(_T(""))
{

}

CPrivacyDialog::~CPrivacyDialog()
{
}

void CPrivacyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRIVACYPASSWORD, m_csPrivacyPassword);
}


BEGIN_MESSAGE_MAP(CPrivacyDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CPrivacyDialog::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPrivacyDialog 消息处理程序

BOOL CPrivacyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPrivacyDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString csPassword;
	GetPrivateProfileString(_T("Password"),_T("PrivacyPassword"),_T(""),csPassword.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	if( csPassword != m_csPrivacyPassword)
	{
		MessageBox(_T("隐私空间密码输入错误"),_T("提示！"),MB_OK|MB_ICONWARNING);
		return;
	}
	OnOK();
}

HBRUSH CPrivacyDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
