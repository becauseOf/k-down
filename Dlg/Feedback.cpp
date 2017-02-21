// Feedback.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dlg.h"
#include "Feedback.h"


// CFeedback �Ի���

IMPLEMENT_DYNAMIC(CFeedback, CDialog)

CFeedback::CFeedback(CWnd* pParent /*=NULL*/)
	: CDialog(CFeedback::IDD, pParent)
	, m_csFeedback(_T(""))
{

}

CFeedback::~CFeedback()
{
}

void CFeedback::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FEEDBACK, m_csFeedback);
	DDX_Control(pDX, IDC_BUTTON_FEEDBACKSUBMIT, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CFeedback, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FEEDBACKSUBMIT, &CFeedback::OnBnClickedButtonFeedbacksubmit)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFeedback ��Ϣ�������

BOOL CFeedback::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnOK.SetIcon(IDI_ICON_RIGHT1);
	m_btnOK.DrawTransparent(TRUE);

	m_btnCancel.SetIcon(IDI_ICON_CANCEL1);
	m_btnCancel.DrawTransparent(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFeedback::OnBnClickedButtonFeedbacksubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(m_csFeedback == "")
	{
		MessageBox(_T("�㲢û�����뷴�����ݰ�"),_T("����"),MB_OK|MB_ICONQUESTION);
		return;
	}
	INT_PTR iRes;
	iRes = MessageBox(_T("��ȷ��Ҫ�ύ�����������"),_T("����"),MB_OKCANCEL);
	if (iRes == IDOK)
	{
		MessageBox(_T("��л����֧��,���ķ�������Ѿ��ɹ��ύ"));
		OnOK();
	}
	else
	{
		return;
	}

}

HBRUSH CFeedback::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
