// PrivacyDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "PrivacyDialog.h"


// CPrivacyDialog �Ի���

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


// CPrivacyDialog ��Ϣ�������

BOOL CPrivacyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPrivacyDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CString csPassword;
	GetPrivateProfileString(_T("Password"),_T("PrivacyPassword"),_T(""),csPassword.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	if( csPassword != m_csPrivacyPassword)
	{
		MessageBox(_T("��˽�ռ������������"),_T("��ʾ��"),MB_OK|MB_ICONWARNING);
		return;
	}
	OnOK();
}

HBRUSH CPrivacyDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
