// ChangePassword.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "ChangePassword.h"
#include "PrivacyPassword.h"


// CChangePassword 对话框

IMPLEMENT_DYNAMIC(CChangePassword, CDialog)

CChangePassword::CChangePassword(CWnd* pParent /*=NULL*/)
	: CDialog(CChangePassword::IDD, pParent)
	, m_csChangePassword(_T(""))
	, m_csLastPassword(_T(""))
	, m_csPasswordOK(_T(""))
{

}

CChangePassword::~CChangePassword()
{
}

void CChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRIVACYPASSWORD, m_csChangePassword);
	DDX_Text(pDX, IDC_EDIT_LASTPASSWORD, m_csLastPassword);
	DDX_Text(pDX, IDC_EDIT_PASSWORDOK, m_csPasswordOK);
}


BEGIN_MESSAGE_MAP(CChangePassword, CDialog)
	ON_BN_CLICKED(IDOK2, &CChangePassword::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &CChangePassword::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CChangePassword::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChangePassword 消息处理程序

void CChangePassword::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CChangePassword::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CChangePassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(true);
	if(m_csChangePassword == "")
	{
		MessageBox(_T("请填写修改后的密码"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csLastPassword == "")
	{
		MessageBox(_T("请填写原密码"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPasswordOK == "")
	{
		MessageBox(_T("请确认修改密码"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csChangePassword != m_csPasswordOK)
	{
		MessageBox(_T("确认密码输入错误，两次密码输入不同，请确认"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	CString csStr;
	GetPrivateProfileString(_T("Password"),_T("PrivacyPassword"),_T(""),csStr.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	if ( csStr != m_csLastPassword )
	{
		MessageBox(_T("原密码匹配失败，请确认是否输入正确"),_T("提醒！"),MB_OK|MB_ICONWARNING);
		return;
	}
	INT_PTR iRes;
	iRes = MessageBox(_T("确定要修改密码了吗？"),_T("疑惑"),MB_OKCANCEL|MB_ICONQUESTION);
	if(iRes == IDCANCEL)
		return;
	WritePrivateProfileString(_T("Password"),_T("PrivacyPassword"),m_csChangePassword,_T("..//PasswordConfig.ini"));
	MessageBox(_T("密码修改成功！"),_T("提醒"),MB_OK);
	OnOK();
}

HBRUSH CChangePassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
