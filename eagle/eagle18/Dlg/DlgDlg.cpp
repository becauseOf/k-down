// DlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "DlgDlg.h"
#include "Feedback.h"
#include "NewAssignment.h"
#include "PrivacyDialog.h"
#include "PrivacyPassword.h"
#include "Setting.h"
#include "Search.h"
#include"SolveCode.h"
#include"SetIP.h"
#include"getMD5.h"
//#include "TipDelete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDlgDlg �Ի���




CDlgDlg::CDlgDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgDlg::IDD, pParent)
, m_pGetSocket(NULL)
, m_pSendSocket(NULL)
, m_csServerIP(_T(""))
, m_csIP(_T(""))
, m_csMAC(_T(""))
, m_pSearch(NULL)
, m_pGiveSocket(NULL)
, m_bDownloading(false)
, m_csGiveFilePath(_T(""))
, m_csSaveFilePath(_T(""))
, m_csSaveFileName(_T(""))
, m_iCount(0)
, m_bFinish(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_csServerIP=_T("127.0.0.1");
}

void CDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_MISSION, m_listShow);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOADPROGRESS, progress);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_btnSet);
	DDX_Control(pDX, IDC_BUTTON_FEEDBACK, m_btnFeedback);
	DDX_Control(pDX, IDC_BUTTON_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_BUTTON_SETIP, m_btnIP);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BUTTON_MYDOWNLOAD, m_btnMy);
	DDX_Control(pDX, IDC_BUTTON_NOWDOWNLOAD, m_btnNow);
	DDX_Control(pDX, IDC_BUTTON_PRIVACY, m_btnPrivacy);
	DDX_Control(pDX, IDC_BUTTON_RECYCLEBIN, m_btnCan);
	DDX_Control(pDX, IDC_BUTTON1, m_btnProgress);
}

BEGIN_MESSAGE_MAP(CDlgDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CDlgDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACK, &CDlgDlg::OnBnClickedButtonFeedback)
	ON_BN_CLICKED(IDC_BUTTON_PRIVACY, &CDlgDlg::OnBnClickedButtonPrivacy)
	ON_BN_CLICKED(IDC_BUTTON_NEWASSIGNMENT, &CDlgDlg::OnBnClickedButtonNewassignment)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgDlg::OnBnClickedButtonDelete)

	ON_BN_CLICKED(IDC_BUTTON_START, &CDlgDlg::OnBnClickedButtonStart)
	//	ON_BN_CLICKED(IDC_BUTTON1, &CDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_NOWDOWNLOAD, &CDlgDlg::OnBnClickedButtonNowdownload)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CDlgDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDC_BUTTON_SETIP, &CDlgDlg::OnBnClickedButtonSetip)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDlgDlg::OnBnClickedButtonPause)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_RECYCLEBIN, &CDlgDlg::OnBnClickedButtonRecyclebin)
END_MESSAGE_MAP()


// CDlgDlg ��Ϣ�������

BOOL CDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���ñ���ͼƬ
	CBitmap bmp;
	bmp.LoadBitmapW(IDB_BK2);
	m_brBK.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	//������ť
	m_btnSearch.SetIcon(IDI_ICON_SEARCH2,IDI_ICON_SEARCH1);
	m_btnSearch.DrawTransparent(TRUE);

	//���ð�ť
	m_btnSet.SetIcon(IDI_ICON_SET2,IDI_ICON_SET1);
	m_btnSet.DrawTransparent(TRUE);

	//������ť
	m_btnFeedback.SetIcon(IDI_ICON_FEEDBACK2,IDI_ICON_FEEDBACK);
	m_btnFeedback.DrawTransparent(TRUE);

	//�ϴ���ť
	m_btnUpload.SetIcon(IDI_ICON_UPLOAD2,IDI_ICON_UPLOAD1);
	m_btnUpload.DrawTransparent(TRUE);

	//����IP��ť
	m_btnIP.SetIcon(IDI_ICON_IP2,IDI_ICON_IP1);
	m_btnIP.DrawTransparent(TRUE);

	//��ʼ��ť
	m_btnStart.SetIcon(IDI_ICON_START1,IDI_ICON_OK);
	m_btnStart.DrawTransparent(TRUE);

	//��ͣ��ť
	m_btnPause.SetIcon(IDI_ICON_PAUSE1,IDI_ICON_PAUSE2);
	m_btnPause.DrawTransparent(TRUE);

	//ɾ����ť
	m_btnDelete.SetIcon(IDI_ICON_DELETE2,IDI_ICON_DELETE1);
	m_btnDelete.DrawTransparent(TRUE);

	//�ҵ����ذ�ť
	m_btnMy.SetIcon(IDI_ICON_MY);
	m_btnMy.DrawTransparent(TRUE);

	//�������ذ�ť
	m_btnNow.SetIcon(IDI_ICON_NOW);
	m_btnNow.DrawTransparent(TRUE);

	//��˽�ռ䰴ť
	m_btnPrivacy.SetIcon(IDI_ICON_PRIVACY);
	m_btnPrivacy.DrawTransparent(TRUE);

	//����վ��ť
	m_btnCan.SetIcon(IDI_ICON_CAN);
	m_btnCan.DrawTransparent(TRUE);

	//���ؽ��Ȱ�ť
	m_btnProgress.DrawTransparent(TRUE);
	m_btnProgress.DrawBorder(FALSE);


	//Ϊ�����б������ͷ
	m_listShow.InsertColumn(1,_T("�ļ���"),0,200,-1);
	m_listShow.InsertColumn(2,_T("�ļ���С"),0,68,-1);
	m_listShow.InsertColumn(3,_T("����"),0,68,-1);
	m_listShow.InsertColumn(4,_T("�ٶ�"),0,90,-1);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_listShow.SetExtendedStyle(m_listShow.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	m_bDownloading = false;
	//��ȡĬ�ϱ����·��
	GetPrivateProfileString(_T("DownloadPath"),_T("DownloadPath"),_T(""),m_csSaveFilePath.GetBuffer(MAX_PATH),MAX_PATH,_T("..//DownloadPath.xiangsong"));
	m_bFinish = false;
	UpdateData(false);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�������ý���
void CDlgDlg::OnBnClickedButtonSetting()
{
	CSetting set2;
	set2.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//���뷴������
void CDlgDlg::OnBnClickedButtonFeedback()
{
	CFeedback feedback;
	feedback.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgDlg::OnBnClickedButtonPrivacy()
{
	CPrivacyDialog privacy;
	privacy.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//�½������Ѿ�����Ҫ���������
void CDlgDlg::OnBnClickedButtonNewassignment()
{
	INT_PTR iRes;
	CNewAssignment new1;
	iRes = new1.DoModal();
	if(iRes == IDCANCEL)
	{
		return;
	}
	//��ȡ�½�������ļ���
	CString newFileName = new1.m_csFileName;
	//������
	m_csFilePath=new1.m_csDownloadPath+_T("1.zip");

	//��ȡ��ǰ����
	int nRowCount = m_listShow.GetItemCount();
	LPCTSTR fileSize;
	fileSize = _T("8TB");

	m_listShow.InsertItem(nRowCount,newFileName);//��һ�������Ǵ�0��ʼ��
	m_listShow.SetItemText(nRowCount,1,fileSize);//��һ������ͬ�ϣ��ڶ���������������Ҳ�Ǵ�0��ʼ��

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//ɾ������
void CDlgDlg::OnBnClickedButtonDelete()
{
	/*	INT_PTR iRes;
	CTipDelete tip;
	iRes = tip.DoModal();
	if(iRes == IDCANCEL)
	{
	return;
	}
	*/
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR iRes;
	iRes = MessageBox(_T("ȷ��ɾ������"),_T("��ʾ"),MB_OKCANCEL|MB_ICONQUESTION);
	if(iRes == IDCANCEL)
		return;
	//ɾ���б��е���
	//���ȵõ��ж�����
	int nRowCount = m_listShow.GetItemCount();
	//û���оͲ���ɾ
	if(nRowCount < 1)
		return;

	//ûѡ��Ҳ��ɾ
	POSITION pos = m_listShow.GetFirstSelectedItemPosition();
	if(pos == NULL){
		AfxMessageBox(_T("δѡ�У�"));
		return;
	}
	/*//ɾ��һ����¼
	m_listShow.DeleteItem(int(pos)-1);
	*/
	//����ѡ�м�¼��ɾ�������ܴ�ǰ�濪ʼɾ����Ҫ�Ӻ���Ŷ
	for(int i = nRowCount-1; i >= 0;i--){
		if(m_listShow.GetItemState(i,LVIS_SELECTED))
			m_listShow.DeleteItem(i);
	}
	//����������أ���Ͽ�����
	if(m_bDownloading)
	{
		m_pGetSocket->Close();
	}

}

// ���ڽ���socket��Ϣ����Ϣ�������ļ�������ȡ���
void CDlgDlg::RevMsg(CSendSocket* pSocket)
{
	STRUCT_MSG revMsg;
	memset(&revMsg,0,sizeof(revMsg));
	pSocket->Receive((char*)&revMsg,sizeof(revMsg)+1);

	switch(revMsg.iMsgType)
	{
		//�յ������ļ�����
	case MT_SENDFILE:
		{
			CFile file;
			if(!file.Open(m_csSaveFilePath+m_csSaveFileName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite)){
				AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
				return;
			}
			file.Seek(revMsg.iIndex * SEND_BLOCK,CFile::begin);
			file.Write(revMsg.cFileContent,revMsg.iFileSize); 
			bBlock[revMsg.iIndex]='1';
			file.Close();
			progress.SetPos(revMsg.iIndex); //���õ�ǰ��������λ��
			AskForFile();
			break;
		}
		//�յ�����Ҫ���͵��ļ����ƫ����
	case MT_SENDFILE_REQUEST:
		{
			CFile file;
			if(!file.Open(m_csGiveFilePath,CFile::modeRead))
			{
				AfxMessageBox(_T("�����ļ�ʧ�ܣ�"));
				return;
			}
			STRUCT_MSG sendMsg;
			memset(&sendMsg,0,sizeof(sendMsg));
			sendMsg.iMsgType = MT_SENDFILE;
			sendMsg.iIndex = revMsg.iIndex;


			file.Seek(sendMsg.iIndex * SEND_BLOCK,CFile::begin);

			int iSize = file.Read(sendMsg.cFileContent,SEND_BLOCK);
			sendMsg.iFileSize = iSize;
			pSocket->Send((char*)&sendMsg,sizeof(sendMsg)+1);
			file.Close();
			Sleep(10);
			break;
		}
		/*//�յ����Ǵ��ļ���ʼ��Ҫ��
		case MT_SENDFILE_INIT:
		{
		bBlock = new bool[revMsg.iCount];
		for(int i =0 ; i <revMsg.iCount ; i++)
		bBlock[i]=false;
		iCount = revMsg.iCount;
		break;
		}*/
		//�յ������������ص��ļ��б�
	case MT_SEARCH_RETURN:
		{
			int iZiYuanShu = revMsg.iCount;
			int iFileSize = revMsg.iFileSize;
			CString csFileSize;
			csFileSize.Format(_T("%d"),iFileSize);
			CString csZiYuanShu;
			csZiYuanShu.Format(_T("%d"),iZiYuanShu);
			CString csFileName = CA2W(revMsg.cFileName);
			CString csMD5 = CA2W(revMsg.cMD5);
			int iRow = m_pSearch->m_SearchList.GetItemCount();
			//����б�
			m_pSearch->m_SearchList.InsertItem(iRow,csFileName);
			m_pSearch->m_SearchList.SetItemText(iRow,1,csFileSize);
			m_pSearch->m_SearchList.SetItemText(iRow,2,csZiYuanShu);
			m_pSearch->m_SearchList.SetItemText(iRow,3,csMD5);
			break;
		}
	case MT_GIVEFILE:
		{
			CString csIP = CA2W(revMsg.cIP);

			//AfxMessageBox(csIP);//������
			m_pGiveSocket = new CSendSocket(this);
			m_pGiveSocket->Create();
			if(!m_pGiveSocket->Connect(csIP,MYPORT))
			{
				AfxMessageBox(_T("���ӽ����ļ��ͻ���ʧ�ܣ�"));
				return;
			}
			//֮��Ϳ�ʼ���ļ���
			//����Ҫ�����ļ���·��
			GetPrivateProfileString(CA2W(revMsg.cMD5),_T("FilePath"),_T(""),m_csGiveFilePath.GetBuffer(MAX_PATH),MAX_PATH,_T("..//Upload.wrc"));
			AfxMessageBox(_T("��")+csIP+_T("��")+m_csGiveFilePath);
			break;
		}
	}

}

// ���û������ˣ������������ɾ�����ͷ��ڴ棬��������������
void CDlgDlg::ClientQuit(CSendSocket* pSocket)
{
}


// ���ڽ��ܿͻ������ӣ���������ӦSocket�������������
void CDlgDlg::AddClient(void)
{
	CSendSocket* pSocket = new CSendSocket(this);
	if(!m_pGetSocket->Accept(*pSocket)){
		AfxMessageBox(_T("���ӿͻ���ʧ�ܣ�"));
		delete pSocket;
		pSocket = NULL;
	}else{
		m_listClient.AddTail(pSocket);
		//AfxMessageBox(_T("�ɹ�����ͻ��ˣ�"));
		//������Ϳ���������ͻ���askforfile��
		AskForFile();
		m_bDownloading= true;
	}
}

// ����������Socket�����ö˿ڲ���ʼ����
bool CDlgDlg::CreateServer(void)
{
	//����Socket
	m_pGetSocket = new CGetSocket(this);
	//��������
	if(!m_pGetSocket->Create(MYPORT)){
		AfxMessageBox(_T("����������ʧ�ܣ�"));
		return false;
	}


	//����
	m_pGetSocket->Listen();
	return true;
}

void CDlgDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����������أ������κθı�
	if(m_bDownloading)
	{
		return;
	}
	//����������أ����ȡ�ļ�����MD5�Լ�������Ȼ���͸���������������
	CString csCount;
	GetPrivateProfileString(_T("Downloading"),_T("FileName"),_T(""),m_csSaveFileName.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	GetPrivateProfileString(_T("Downloading"),_T("MD5"),_T(""),m_csMD5.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	GetPrivateProfileString(_T("Downloading"),_T("Count"),_T(""),csCount.GetBuffer(MAX_PATH),MAX_PATH,_T("..\\Downloading.lyt"));
	m_iCount = _ttoi(csCount);
	if ( m_csSaveFileName!=_T("") )
	{
		//���¿�ʼ������
		CreateServer();
		STRUCT_MSG downloadMsg;
		memset(&downloadMsg,0,sizeof(downloadMsg));
		downloadMsg.iMsgType = MT_DOWNREQUEST;
		GetIP(m_csIP);
		CStringToCharP(m_csIP,downloadMsg.cIP);
		CStringToCharP(m_csMD5,downloadMsg.cMD5);//��MD5���÷����������ݿ�������Ӧ����
		CFile file;
		file.Open(m_csSaveFilePath + m_csMD5 , CFile::modeRead);
		file.Read(bBlock,m_iCount);
		file.Close();
		//��ʼ��������
		progress.SetRange(0,m_iCount);//�趨��������ʼλ�úͽ���λ��,��������ò���ʮ�ֺ�����Ϊ������short���������ֻ�ܷ�65535��
		progress.SetStep(1);//�趨ÿ�����ӵĴ�С	
		m_pSendSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
	}
}

//����
void CDlgDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSearch s(this);
	m_pSearch = &s;
	m_pSearch->DoModal();
}
//�Ѿ�����Ҫ���������
void CDlgDlg::OnBnClickedButtonNowdownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ע���ǲ������ã�����ʧ�ܡ���
	/*m_pSendSocket = m_listClient.GetHead();
	//m_listShow.DeleteAllItems();
	STRUCT_MSG init;
	init.iMsgType = MT_SENDFILE_INIT;
	CFile file;
	file.Open(m_csFilePath,CFile::modeRead);

	init.iCount = (DWORD)file.GetLength()/SEND_BLOCK;
	m_pSendSocket->Send((char*)&init,sizeof(init)+1);
	STRUCT_MSG first;
	first.iMsgType = MT_SENDFILE_REQUEST;
	first.iIndex = 0;
	first.iCount = (DWORD)file.GetLength();
	first.iFileSize = (DWORD)file.GetLength();
	m_pSendSocket->Send((char*)&first,sizeof(first)+1);*/
}

//�ϴ�����
void CDlgDlg::OnBnClickedButtonUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ɵ���GetPrivateProfileString��..//Download.ini�л�ȡ �ļ����ļ���С�ʹ��·��
	//if(!m_pSendSocket)
	//{
	//	AfxMessageBox(_T("δ���ӷ�������"));
	//	return;
	//}

	TCHAR szFilter[] = (_T("�����ļ�(*.*)|*.*||"));
	CFileDialog filedialog(true,_T("0"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,this);
	CString csFilePath;
	CString csFileName;
	int iFileSize;
	if( IDOK == filedialog.DoModal())
	{
		csFilePath = filedialog.GetPathName();
		csFileName = filedialog.GetFileName();
	}
	else
	{
		return;
	}
	CFile file;
	file.Open(csFilePath,CFile::modeRead);
	iFileSize = file.GetLength();
	file.Close();
	CString csMD5 = getMd5(csFilePath);//������дMD5����
	STRUCT_MSG upLoadMsg;
	memset(&upLoadMsg,0,sizeof(upLoadMsg));
	upLoadMsg.iMsgType = MT_UPLOAD;
	//ת���ͺ�ֵ
	CStringToCharP(csFileName,upLoadMsg.cFileName);
	CStringToCharP(csFilePath,upLoadMsg.cFileContent);
	CStringToCharP(m_csIP,upLoadMsg.cIP);
	CStringToCharP(m_csMAC,upLoadMsg.cMAC);
	CStringToCharP(csMD5,upLoadMsg.cMD5);
	upLoadMsg.iFileSize = iFileSize;
	m_pSendSocket->Send((char*)&upLoadMsg,sizeof(upLoadMsg)+1);

	WritePrivateProfileString(csMD5,_T("FilePath"),csFilePath,_T("..\\Upload.wrc"));


}

// ���ӵ�������
bool CDlgDlg::ConnectServer(void)
{
	m_pSendSocket = new CSendSocket(this);
	m_pSendSocket->Create();
	if(!m_pSendSocket->Connect(m_csServerIP,SERVERPORT))
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return false;
	}
	return true;
}

void CDlgDlg::OnBnClickedButtonSetip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSetIP ci;
	ci.DoModal();
	m_csServerIP = ci.m_csIP;
	if(!ConnectServer())
		return;
	Sleep(500);

	STRUCT_MSG sendMsg;
	memset(&sendMsg,0,sizeof(sendMsg));
	sendMsg.iMsgType = MT_LOGIN;

	GetIP(m_csIP);
	m_csMAC=GetMAC();
	CStringToCharP(m_csIP,sendMsg.cIP);
	CStringToCharP(m_csMAC,sendMsg.cMAC);
	m_pSendSocket->Send((char*)&sendMsg,sizeof(sendMsg)+1);
}

// ��ñ���MAC��ַ
CString CDlgDlg::GetMAC(void)
{
	int i=0;
	CString str;
	PIP_ADAPTER_INFO pAdapterInfo;ULONG ulOutbufLen = sizeof(IP_ADAPTER_INFO);//ע����ULONG����,����PULONG����
	pAdapterInfo = ( IP_ADAPTER_INFO *)malloc( sizeof(IP_ADAPTER_INFO) );//Ϊ�䶯̬�����ڴ�,����С����,������е���

	if ( ERROR_BUFFER_OVERFLOW == GetAdaptersInfo( pAdapterInfo, &ulOutbufLen) )
	{//MSDN�Ͻ���,��Ϊ��ȡ����Ϣ,���ܳ���Ԥ�����õĻ���������,��ɷ���,��һ�����ػ�ȡ�����Ͻ�Ϊ��,�˴�Ϊ��ֹ�����������,
		free(pAdapterInfo);//���Բ���һ�½��,ȥ���ⲿ�ִ����,����ֵΪ��.�˴��ع�,ֱ���ɹ�
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutbufLen); //��1�δ�С����,��2�η������賤��
	}
	if ( ERROR_SUCCESS == GetAdaptersInfo( pAdapterInfo, &ulOutbufLen ))//MSDN��������д,Ҳ��д��NO_ERROR,����ȷ



		str.Format(_T("%02x-%02x-%02x-%02x-%02x-%02x\n"),
		pAdapterInfo->Address[0], //ע��˴��������ʽ,�����е�û��[0][1]��,str.Format��ʽ����sprintf��MFC��
		pAdapterInfo->Address[1],
		pAdapterInfo->Address[2],
		pAdapterInfo->Address[3],
		pAdapterInfo->Address[4],
		pAdapterInfo->Address[5]);//,pAdapterInfo->Address[6],�������֪����7���Ǹ�ʲôֵ?����һ��,����ֵΪ00(����ֵ)

	//m_Mac.SetWindowText(str);

	return str;
}

// ��ȡ����IP��ַ
bool CDlgDlg::GetIP(CString &IP)
{
	WSADATA wsadata;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsadata))   //��ʼ��
	{
		//AfxMessageBox("��ʼ�����绷��ʧ��!");
		return false;
	}
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);  //�õ��������
	hostent *p = gethostbyname(szHostName); //�Ӽ�������õ�������Ϣ
	if(p == NULL)
	{
		//AfxMessageBox("�õ�����������Ϣʧ��!");
		return false;
	}
	//m_strName = szHostName;       //����������
	//int nCount = 0;                 //����������ַ
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);//��32λIPת��Ϊ�ַ���IP
	//CString m_strAddr = pIP;             //��������IP��ַ
	//AfxMessageBox(m_strAddr);
	IP = pIP;
	//UpdateData(FALSE);          //��ʾ��������
	WSACleanup();               //�ͷ�Winsock API
	return true;
}

BOOL CDlgDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pGetSocket)
	{
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}

	if(m_bDownloading)
	{
		//д�����ļ�
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();

	}
	if(m_pGiveSocket)
	{
		m_pGiveSocket->Close();
		delete m_pGiveSocket;
		m_pGiveSocket = NULL;
	}
	if(m_pSendSocket)
	{
		m_pSendSocket->Close();
		delete m_pSendSocket;
		m_pSendSocket = NULL;
	}
	return CDialog::DestroyWindow();
}

// �����������е��ļ���������������
void CDlgDlg::DealSearch(CString FileName)
{
	if(!m_pSendSocket)
	{
		AfxMessageBox(_T("δ���ӷ�������"));
		return;
	}
	STRUCT_MSG searchMsg;
	memset(&searchMsg,0,sizeof(searchMsg));
	searchMsg.iMsgType = MT_SEARCH;
	CStringToCharP(FileName,searchMsg.cFileName);
	m_pSendSocket->Send((char*)&searchMsg,sizeof(searchMsg)+1);
}

// ������������
void CDlgDlg::DealDownload(CString FileName,CString MD5,int iFileSize)
{
	//�Լ��ȴ���һ���׽������ڽӷ��ļ��Ŀͻ���
	CreateServer();
	//��ʼ������
	InitDownload(iFileSize,MD5);
	//����Ҫ���ص��ļ���
	m_csSaveFileName = FileName;//������ļ����ǽ��տͻ��˵��ļ��������Ƿ��Ϳͻ��˵ģ��������·���Ƿ��Ϳͻ��˵�
	//֮����Ϣ�����������÷���������Ϣ�������ͻ��ˣ�Ҫ�����Ƿ��ļ�
	STRUCT_MSG downloadMsg;
	memset(&downloadMsg,0,sizeof(downloadMsg));
	downloadMsg.iMsgType = MT_DOWNREQUEST;
	//CStringToCharP(FilePath,downloadMsg.cFileContent);//��·����ȥ���������ͻ���ֱ�Ӵ����·�����ļ����ɣ����ٹ�����.�������ڸ�Ϊ�������ļ���
	CStringToCharP(m_csIP,downloadMsg.cIP);
	CStringToCharP(MD5,downloadMsg.cMD5);//��MD5���÷����������ݿ�������Ӧ����
	//CStringToCharP(FileName,downloadMsg.cFileName);//������ļ����ǽ��տͻ��˵��ļ��������Ƿ��Ϳͻ��˵ģ��������·���Ƿ��Ϳͻ��˵�
	m_pSendSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);

}

void CDlgDlg::OnBnClickedButtonPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����������أ���Ͽ�����
	if(m_bDownloading)
	{
		m_pGetSocket->Close();
		m_listClient.RemoveAll();
		//д�����ļ�
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();
		m_bDownloading = false;
		//д�����ļ��������ļ�����MD5���Լ��ܵĿ���
		CString csCount;
		csCount.Format(_T("%d"),m_iCount);
		WritePrivateProfileString(_T("Downloading"),_T("FileName"),m_csSaveFileName,_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("MD5"),m_csMD5,_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("Count"),csCount,_T("..\\Downloading.lyt"));
		 m_bFinish = false;
	}


}

// ��ʼ�����أ���ʼ��bBlock����
void CDlgDlg::InitDownload(int iFileSize,CString MD5)
{
	int iCount = iFileSize / SEND_BLOCK;
	if(iFileSize % SEND_BLOCK > 0)
	{
		iCount++;
	}
	m_iCount = iCount;
	m_csMD5=MD5;
	bBlock = new char[iCount];
	for(int i = 0; i<iCount;i++)
	{
		bBlock[i] = '0';
	}
	bBlock[iCount] = '\0'; 
	CFile file;
	file.Open(m_csSaveFilePath+MD5,CFile::modeCreate|CFile::modeWrite);
	file.Write(bBlock,iCount+1);
	file.Close();
	//��ʼ��������
	progress.SetRange(0,m_iCount);//�趨��������ʼλ�úͽ���λ��,��������ò���ʮ�ֺ�����Ϊ������short���������ֻ�ܷ�65535��
	progress.SetStep(1);//�趨ÿ�����ӵĴ�С	

}

// ������ͻ�����ȡ�ļ�
void CDlgDlg::AskForFile(void)
{
	m_bDownloading= false;
	POSITION pos=m_listClient.GetHeadPosition();
	while(pos!=NULL)
	{
		CSendSocket* pSocket=m_listClient.GetAt(pos);
		for(int i = 0; i< m_iCount;i++)
		{
			if('0' == bBlock[i])//��������û�о���Ҫ
			{
				STRUCT_MSG downloadMsg;
				memset(&downloadMsg,0,sizeof(downloadMsg));
				downloadMsg.iMsgType = MT_SENDFILE_REQUEST;
				downloadMsg.iIndex = i;
				pSocket->Send((char*)&downloadMsg,sizeof(downloadMsg)+1);
				//bBlock[i]='1';//��֪��˳��������䲻֪���費��Ҫ
				Sleep(10);
				m_bDownloading = true;
				break;
			}
			m_bFinish = true;
		}
		m_listClient.GetNext(pos);
	}
	
	if((!m_bDownloading)&& (m_bFinish == true))
	{
		Sleep(1000);
		CFile file;
		file.Open(m_csSaveFilePath+m_csMD5,CFile::modeWrite|CFile::modeNoTruncate);
		file.Write(bBlock,m_iCount+1);
		file.Close();
		WritePrivateProfileString(_T("Downloading"),_T("FileName"),_T(""),_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("MD5"),_T(""),_T("..\\Downloading.lyt"));
		WritePrivateProfileString(_T("Downloading"),_T("Count"),_T(""),_T("..\\Downloading.lyt"));
		AfxMessageBox(_T("Done"));
		m_bFinish = true;
		if(!m_pGetSocket)
			return;
		m_pGetSocket->Close();
		delete m_pGetSocket;
		m_pGetSocket = NULL;
	}

}

HBRUSH CDlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(pWnd == this)
	{
		return m_brBK;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CDlgDlg::OnBnClickedButtonRecyclebin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
