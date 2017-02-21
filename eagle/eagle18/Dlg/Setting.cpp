// Setting.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "Setting.h"
#include"PrivacyPassword.h"
#include "ChangePassword.h"

// CSetting 对话框

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


// CSetting 消息处理程序

BOOL CSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetting::OnCbnSelchangeComboDownloadlist()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CSetting::OnBnClickedButtonToprivacy()
{
	// TODO: 在此添加控件通知处理程序代码	CString csStr;
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
	// TODO: 在此添加控件通知处理程序代码
}

void CSetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	WritePrivateProfileString(_T("DownloadPath"),_T("DownloadPath"),m_csDownloadPath,_T("..//DownloadPath.xiangsong"));
	OnOK();
}

void CSetting::OnBnClickedCheckFirstbootdevice()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	HKEY hKey;
	CString strRegPath = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	//找到系统的启动项  
	if (m_autoStart.GetCheck())
	{
		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //打开启动项       
		{
			TCHAR szModule[MAX_PATH];
			GetModuleFileName(NULL, szModule, MAX_PATH);//得到本程序自身的全路径  
			RegSetValueEx(hKey, _T("Demo"), 0, REG_SZ, (LPBYTE)szModule, (lstrlen(szModule) + 1)*sizeof(TCHAR));
			//添加一个子Key,并设置值，"Demo"是应用程序名字（不加后缀.exe）  
			RegCloseKey(hKey); //关闭注册表
		}
		else
		{
			AfxMessageBox(_T("系统参数错误,不能随系统启动"));
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
