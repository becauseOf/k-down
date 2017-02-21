// ChangePassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "ChangePassword.h"
#include "PrivacyPassword.h"


// CChangePassword �Ի���

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


// CChangePassword ��Ϣ�������

void CChangePassword::OnBnClickedOk2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void CChangePassword::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CChangePassword::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		UpdateData(true);
	if(m_csChangePassword == "")
	{
		MessageBox(_T("����д�޸ĺ������"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csLastPassword == "")
	{
		MessageBox(_T("����дԭ����"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPasswordOK == "")
	{
		MessageBox(_T("��ȷ���޸�����"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csChangePassword != m_csPasswordOK)
	{
		MessageBox(_T("ȷ������������������������벻ͬ����ȷ��"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	CString csStr;
	GetPrivateProfileString(_T("Password"),_T("PrivacyPassword"),_T(""),csStr.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	if ( csStr != m_csLastPassword )
	{
		MessageBox(_T("ԭ����ƥ��ʧ�ܣ���ȷ���Ƿ�������ȷ"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	INT_PTR iRes;
	iRes = MessageBox(_T("ȷ��Ҫ�޸���������"),_T("�ɻ�"),MB_OKCANCEL|MB_ICONQUESTION);
	if(iRes == IDCANCEL)
		return;
	WritePrivateProfileString(_T("Password"),_T("PrivacyPassword"),m_csChangePassword,_T("..//PasswordConfig.ini"));
	MessageBox(_T("�����޸ĳɹ���"),_T("����"),MB_OK);
	OnOK();
}

HBRUSH CChangePassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
