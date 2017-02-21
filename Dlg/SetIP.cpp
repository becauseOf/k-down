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
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CSetIP, CDialog)
	ON_BN_CLICKED(IDOK, &CSetIP::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_IP, &CSetIP::OnEnChangeEditIp)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetIP ��Ϣ�������

void CSetIP::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	OnOK();
}

void CSetIP::OnEnChangeEditIp()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

HBRUSH CSetIP::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
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

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CSetIP::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnOK.SetIcon(IDI_ICON_RIGHT1);
	m_btnOK.DrawTransparent(TRUE);

	m_btnCancel.SetIcon(IDI_ICON_CANCEL1);
	m_btnCancel.DrawTransparent(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
