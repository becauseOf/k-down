// SetIP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "SetIP.h"


// CSetIP �Ի���

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


// CSetIP ��Ϣ�������

void CSetIP::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	OnOK();
}
