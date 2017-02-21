// Search.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "Search.h"
#include"DlgDlg.h"


// CSearch �Ի���

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


// CSearch ��Ϣ�������

void CSearch::OnLvnItemchangedListSearch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

BOOL CSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnSearch.SetIcon(IDI_ICON_SEARCH3);
	m_btnSearch.DrawTransparent(TRUE);

	m_btnDownload.SetIcon(IDI_ICON_DOWNLOAD);
	m_btnDownload.DrawTransparent(TRUE);
	CRect rect;
	m_SearchList.GetClientRect(&rect);
	m_SearchList.SetExtendedStyle(m_SearchList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_SearchList.InsertColumn(0,_T("�ļ���"),LVCFMT_CENTER,rect.Width()/3,0);
	m_SearchList.InsertColumn(1,_T("�ļ���С"),LVCFMT_CENTER,rect.Width()/3,1);
	m_SearchList.InsertColumn(2,_T("�ɻ�ȡ��Դ"),LVCFMT_CENTER,rect.Width()/3,2);
	//m_SearchList.InsertColumn(3,_T("·��"),LVCFMT_CENTER,-1,3);
	m_SearchList.InsertColumn(3,_T("MD5"),LVCFMT_CENTER,-1,3);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSearch::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	((CDlgDlg*)m_pParent)->DealSearch(m_csSearchMessage);
}
//�������ذ�ť
void CSearch::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_SearchList.GetSelectedCount()== 0)
	{
		AfxMessageBox(_T("û��ѡ�У�"));
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
