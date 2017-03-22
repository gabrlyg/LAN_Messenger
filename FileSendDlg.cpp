// FileSendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileSendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileSendDlg dialog


CFileSendDlg::CFileSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSendDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bDownSend = FALSE;
}


void CFileSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSendDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_wndSendProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileSendDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSendDlg)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CFileSendDlg::OnBnClickedButton1)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CFileSendDlg::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSendDlg message handlers

void CFileSendDlg::OnBtnSend()
{
	if (m_bDownSend == FALSE)
	{
		if (FALSE == m_FileClient.InitClient())
		{
			AfxMessageBox("��ʼ���ļ��ͻ���ʧ��!");
			return;
		}
		if (FALSE == m_FileClient.ConnectServer(m_strIP))
		{
			AfxMessageBox(_T("���ӷ����ʧ��"));
			return;
		}

		//���������߳�
		AfxBeginThread(SendThread, this);
		m_bDownSend = TRUE;
	}
	else
	{
		AfxMessageBox("��ȴ���ǰ�ļ��������");
		return;
	}

	GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);

}

BOOL CFileSendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bDownSend = FALSE;
	// TODO: Add extra initialization here

	OnBtnSend();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CFileSendDlg::SendThread(LPVOID pParam)
{
	CFileSendDlg* pThis = (CFileSendDlg*)pParam;
	pThis->m_FileClient.SendFile(pThis->m_strFile,
		&pThis->m_wndSendProgress);

	return 0;
}

void CFileSendDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileSendDlg::OnOK();
}


/*void CFileSendDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
// TODO: �ڴ���ӿؼ�֪ͨ����������
*pResult = 0;
}*/
