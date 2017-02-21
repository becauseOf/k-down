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
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BUTTON_SCAN, m_btnScan);
	DDX_Control(pDX, IDC_BUTTON_TOPRIVACY, m_btnSet);
}


BEGIN_MESSAGE_MAP(CSetting, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_DOWNLOADLIST, &CSetting::OnCbnSelchangeComboDownloadlist)
	ON_BN_CLICKED(IDC_BUTTON_TOPRIVACY, &CSetting::OnBnClickedButtonToprivacy)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSetting::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDOK, &CSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_FIRSTBOOTDEVICE, &CSetting::OnBnClickedCheckFirstbootdevice)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSetting 消息处理程序

BOOL CSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnScan.SetIcon(IDI_ICON_SEARCH3);
	m_btnScan.DrawTransparent(TRUE);

	m_btnOK.SetIcon(IDI_ICON_RIGHT1);
	m_btnOK.DrawTransparent(TRUE);

	m_btnCancel.SetIcon(IDI_ICON_CANCEL1);
	m_btnCancel.DrawTransparent(TRUE);

	m_btnSet.SetIcon(IDI_ICON_SET3);
	m_btnSet.DrawTransparent(TRUE);

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

HBRUSH CSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
