// PrivacyPassword.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "PrivacyPassword.h"


// CPrivacyPassword �Ի���

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


// CPrivacyPassword ��Ϣ�������

void CPrivacyPassword::OnEnChangeEditNewpassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CPrivacyPassword::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPrivacyPassword::OnEnChangeEditPrivacypassword()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CPrivacyPassword::OnEnChangeEditPasswordok()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CPrivacyPassword::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(m_csPrivacyPassword == "")
	{
		MessageBox(_T("����������˽����������д��˽����"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPrivacyPasswordOK == "")
	{
		MessageBox(_T("����ȷ����˽����������д��˽����"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_csPrivacyPassword != m_csPrivacyPasswordOK )
	{
		MessageBox(_T("���������ȷ�����벻һ������"),_T("���ѣ�"),MB_OK|MB_ICONWARNING);
		return;
	}

	INT_PTR iRes;
	iRes = MessageBox(_T("ȷ��Ҫ������˽��������"),_T("�ɻ�"),MB_OKCANCEL|MB_ICONQUESTION);
	
	if(iRes == IDOK)
	{
		SendMessage(WM_CLOSE);
		MessageBox(_T("��˽�����趨�ɹ���"),_T("��ϲ��"),MB_OK);
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
