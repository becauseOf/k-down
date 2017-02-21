// Setting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "Setting.h"
#include"PrivacyPassword.h"
#include "ChangePassword.h"

// CSetting �Ի���

IMPLEMENT_DYNAMIC(CSetting, CDialog)

CSetting::CSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CSetting::IDD, pParent)
	, m_csDownloadPath(_T(""))
{

}

CSetting::~CSetting()
{
}

void CSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SAVE, m_csDownloadPath);
	DDX_Control(pDX, IDC_CHECK_FIRSTBOOTDEVICE, m_autoStart);
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DOWNLOADLIST, &CSetting::OnCbnSelchangeComboDownloadlist)
	ON_BN_CLICKED(IDC_BUTTON_TOPRIVACY, &CSetting::OnBnClickedButtonToprivacy)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSetting::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDOK, &CSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_FIRSTBOOTDEVICE, &CSetting::OnBnClickedCheckFirstbootdevice)
END_MESSAGE_MAP()


// CSetting ��Ϣ�������

BOOL CSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSetting::OnCbnSelchangeComboDownloadlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CSetting::OnBnClickedButtonToprivacy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	CString csStr;
	CString csStr;
	GetPrivateProfileString(_T("Password"),_T("PrivacyPassword"),_T(""),csStr.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	if(csStr == _T(""))
	{
		CPrivacyPassword pp;
		pp.DoModal();
	}
	else
	{
		CChangePassword change1;
		change1.DoModal();
	}

}

void CSetting::OnBnClickedButtonScan()
{
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);   //Displays a dialog box enabling the user to select a Shell folder.
	TCHAR * path = new TCHAR[MAX_PATH];
	if(pidl != NULL)
	{
		SHGetPathFromIDList(pidl,path);      //Converts an item identifier list to a file system path
		SetDlgItemText(IDC_EDIT_SAVE,path);
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CSetting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	WritePrivateProfileString(_T("DownloadPath"),_T("DownloadPath"),m_csDownloadPath,_T("..//DownloadPath.xiangsong"));
	OnOK();
}

void CSetting::OnBnClickedCheckFirstbootdevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	HKEY hKey;
	CString strRegPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	//�ҵ�ϵͳ��������  
	if (m_autoStart.GetCheck())
	{
		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //��������       
		{
			TCHAR szModule[MAX_PATH];
			GetModuleFileName(NULL, szModule, MAX_PATH);//�õ������������ȫ·��  
			RegSetValueEx(hKey, _T("Demo"), 0, REG_SZ, (LPBYTE)szModule, (lstrlen(szModule) + 1)*sizeof(TCHAR));
			//���һ����Key,������ֵ��"Demo"��Ӧ�ó������֣����Ӻ�׺.exe��  
			RegCloseKey(hKey); //�ر�ע���
		}
		else
		{
			AfxMessageBox(_T("ϵͳ��������,������ϵͳ����"));
		}
	}
	else
	{
		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
		{
			RegDeleteValue(hKey, _T("eagle"));
			RegCloseKey(hKey);
		}
	}

}
