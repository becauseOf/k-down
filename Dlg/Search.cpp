// Search.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg.h"
#include "Search.h"
#include"DlgDlg.h"


// CSearch 对话框

IMPLEMENT_DYNAMIC(CSearch, CDialog)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CSearch::IDD, pParent)
	, m_csSearchMessage(_T(""))
	, m_pParent(NULL)
{
	m_pParent=pParent;
}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SEARCH, m_SearchList);
	DDX_Text(pDX, IDC_EDIT_SEARCHMESSAGE, m_csSearchMessage);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDOK, m_btnDownload);
}


BEGIN_MESSAGE_MAP(CSearch, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SEARCH, &CSearch::OnLvnItemchangedListSearch)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CSearch::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDOK, &CSearch::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSearch 消息处理程序

void CSearch::OnLvnItemchangedListSearch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

BOOL CSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnSearch.SetIcon(IDI_ICON_SEARCH3);
	m_btnSearch.DrawTransparent(TRUE);

	m_btnDownload.SetIcon(IDI_ICON_DOWNLOAD);
	m_btnDownload.DrawTransparent(TRUE);
	CRect rect;
	m_SearchList.GetClientRect(&rect);
	m_SearchList.SetExtendedStyle(m_SearchList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_SearchList.InsertColumn(0,_T("文件名"),LVCFMT_CENTER,rect.Width()/3,0);
	m_SearchList.InsertColumn(1,_T("文件大小"),LVCFMT_CENTER,rect.Width()/3,1);
	m_SearchList.InsertColumn(2,_T("可获取资源"),LVCFMT_CENTER,rect.Width()/3,2);
	//m_SearchList.InsertColumn(3,_T("路径"),LVCFMT_CENTER,-1,3);
	m_SearchList.InsertColumn(3,_T("MD5"),LVCFMT_CENTER,-1,3);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSearch::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	((CDlgDlg*)m_pParent)->DealSearch(m_csSearchMessage);
}
//这是下载按钮
void CSearch::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_SearchList.GetSelectedCount()== 0)
	{
		AfxMessageBox(_T("没有选中！"));
		return;
	}
	int iRow = m_SearchList.GetSelectionMark();
	//CString csFilePath= m_SearchList.GetItemText(iRow,3);
	CString csFileName = m_SearchList.GetItemText(iRow,0);
	CString csMD5 = m_SearchList.GetItemText(iRow,3);
	int iFileSize = _ttoi(m_SearchList.GetItemText(iRow,1));
	((CDlgDlg*)m_pParent)->DealDownload(csFileName,csMD5,iFileSize);
	OnOK();
}

HBRUSH CSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
