// SetIP.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "SetIP.h"


// CSetIP 对话框

IMPLEMENT_DYNAMIC(CSetIP, CDialog)

CSetIP::CSetIP(CWnd* pParent /*=NULL*/)
	: CDialog(CSetIP::IDD, pParent)
	, m_csIP(_T(""))
{

}

CSetIP::~CSetIP()
{
}

void CSetIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
}


BEGIN_MESSAGE_MAP(CSetIP, CDialog)
	ON_BN_CLICKED(IDOK, &CSetIP::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetIP 消息处理程序

void CSetIP::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	OnOK();
}
