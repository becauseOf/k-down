// PrivacyPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "PrivacyPassword.h"


// CPrivacyPassword 对话框

IMPLEMENT_DYNAMIC(CPrivacyPassword, CDialog)

CPrivacyPassword::CPrivacyPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivacyPassword::IDD, pParent)
	, m_csPrivacyPassword(_T(""))
	//, m_csNewPassword(_T(""))
	//, m_csPassword(_T(""))
	//, m_csLastPassword(_T(""))
	, m_csPrivacyPasswordOK(_T(""))
	//, m_csPasswordOK(_T(""))
{

}

CPrivacyPassword::~CPrivacyPassword()
{
}

void CPrivacyPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRIVACYPASSWORD, m_csPrivacyPassword);
	//DDX_Text(pDX, IDC_EDIT_NEWPASSWORD, m_csNewPassword);
	//DDX_Text(pDX, IDC_EDIT_PASSWORDOK, m_csPassword);
	//DDX_Text(pDX, IDC_EDIT_LASTPASSWORD, m_csLastPassword);
	DDX_Text(pDX, IDC_EDIT_PRIVACYPASSWORDOK, m_csPrivacyPasswordOK);
	//DDX_Text(pDX, IDC_EDIT_PASSWORDOK, m_csPasswordOK);
}


BEGIN_MESSAGE_MAP(CPrivacyPassword, CDialog)
	ON_EN_CHANGE(IDC_EDIT_NEWPASSWORD, &CPrivacyPassword::OnEnChangeEditNewpassword)
	ON_EN_CHANGE(IDC_EDIT_PRIVACYPASSWORD, &CPrivacyPassword::OnEnChangeEditPrivacypassword)
	ON_EN_CHANGE(IDC_EDIT_PASSWORDOK, &CPrivacyPassword::OnEnChangeEditPasswordok)
	ON_BN_CLICKED(IDOK, &CPrivacyPassword::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPrivacyPassword 消息处理程序

void CPrivacyPassword::OnEnChangeEditNewpassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

BOOL CPrivacyPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPrivacyPassword::OnEnChangeEditPrivacypassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CPrivacyPassword::OnEnChangeEditPasswordok()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CPrivacyPassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(m_csPrivacyPassword == "")
	{
		MessageBox(_T("请在设置隐私密码栏中填写隐私密码"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPrivacyPasswordOK == "")
	{
		MessageBox(_T("请在确认隐私密码栏中填写隐私密码"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPrivacyPassword != m_csPrivacyPasswordOK )
	{
		MessageBox(_T("设置密码跟确认密码不一样的嘞"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}

	INT_PTR iRes;
	iRes = MessageBox(_T("确定要设置隐私密码了吗？"),_T("疑惑？"),MB_OKCANCEL|MB_ICONQUESTION);
	
	if(iRes == IDOK)
	{
		SendMessage(WM_CLOSE);
		MessageBox(_T("隐私密码设定成功！"),_T("恭喜！"),MB_OK);
		LPCWSTR passwordPath;
		passwordPath = _T("..\\PasswordConfig.ini");
		WritePrivateProfileString(_T("Password"),_T("PrivacyPassword"),m_csPrivacyPassword,passwordPath);
	}
	else
	{
		return;
	}
}
HBRUSH CPrivacyPassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
