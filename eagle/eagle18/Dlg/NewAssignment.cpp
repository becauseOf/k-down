// NewAssignment.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "NewAssignment.h"


// CNewAssignment 对话框

IMPLEMENT_DYNAMIC(CNewAssignment, CDialog)

CNewAssignment::CNewAssignment(CWnd* pParent /*=NULL*/)
	: CDialog(CNewAssignment::IDD, pParent)
	, m_csDownload(_T(""))
	, m_csFileName(_T(""))
	, m_csDownloadPath(_T(""))
	, m_csFileSize(_T(""))
{

}

CNewAssignment::~CNewAssignment()
{
}

void CNewAssignment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD, m_csDownload);
	DDX_Text(pDX, IDC_EDIT_FILE, m_csFileName);
	DDX_Text(pDX, IDC_EDIT_SAVE, m_csDownloadPath);
	DDX_Text(pDX, IDC_EDIT_FILESIZE, m_csFileSize);
}


BEGIN_MESSAGE_MAP(CNewAssignment, CDialog)
	ON_BN_CLICKED(IDOK, &CNewAssignment::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewAssignment::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CNewAssignment::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNewAssignment::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CNewAssignment 消息处理程序

BOOL CNewAssignment::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_csFileSize = _T("8TB");
	GetPrivateProfileString(_T("DownloadPath"),_T("DownloadPath"),_T(""),m_csDownloadPath.GetBuffer(MAX_PATH),MAX_PATH,_T("..//PasswordConfig.ini"));
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewAssignment::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_csFileName == "")
	{
	MessageBox(_T("请输入正确的文件名称"),_T("提醒！"),MB_OK|MB_ICONWARNING);
	return;
	}
	//WritePrivateProfileString(_T("Download"),_T("FileName"),m_csFileName,_T("..//Download.ini"));
	//WritePrivateProfileString(_T("Download"),_T("FileSize"),m_csFileSize,_T("..//Download.ini"));
	//WritePrivateProfileString(_T("Download"),_T("DownloadPath"),m_csDownloadPath,_T("..//Download.ini"));
	int iNum;
	CString csNum;
	GetPrivateProfileString(_T("Num"),_T("DownloadNum"),_T("1"),csNum.GetBuffer(MAX_PATH),MAX_PATH,_T("..//Download.ini"));
	iNum = _ttoi(csNum);
	csNum.Format(_T("%d"),iNum);
	csNum = _T("Download") + csNum;
	WritePrivateProfileString(csNum , _T("FileName") , m_csFileName , _T("..//Download.ini"));
	WritePrivateProfileString(csNum , _T("FileSize") , m_csFileSize , _T("..//Download.ini"));
	WritePrivateProfileString(csNum , _T("DownloadPath") , m_csDownloadPath , _T("..//Download.ini"));
	iNum = iNum + 1;
	csNum.Format(_T("%d"),iNum);
	WritePrivateProfileString(_T("Num") , _T("DownloadNum") , csNum , _T("..//Download.ini"));
	
	OnOK();
}

void CNewAssignment::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CNewAssignment::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = (_T("BT种子文件(*.torrent)|*,torrent||"));
	CFileDialog filedialog(true,_T(".torrent"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	CString filePath;
	if( IDOK == filedialog.DoModal())
	{
	filePath = filedialog.GetPathName();
	SetDlgItemText(IDC_EDIT_SEED,filePath);
	}
	else
	{
		return;
	}
}

void CNewAssignment::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	BROWSEINFO bi;
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);   //Displays a dialog box enabling the user to select a Shell folder.
	TCHAR * path = new TCHAR[MAX_PATH];
	if(pidl != NULL)
	{
		SHGetPathFromIDList(pidl,path);      //Converts an item identifier list to a file system path
		SetDlgItemText(IDC_EDIT_SAVE,path);
	}
}
