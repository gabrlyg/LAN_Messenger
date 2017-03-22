#include "stdafx.h"
#include "FinalProject.h"
#include "ChatView.h"
#include "UserView.h"
#include "MainFrm.h"
#include "UserClient.h"
#include "UserServer.h"

IMPLEMENT_DYNCREATE(CChatView, CFormView)

// ���캯��
CChatView::CChatView()
	: CFormView(CChatView::IDD)
{
	m_pUserClient = NULL;
}

CChatView::~CChatView() {}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAT, m_wndChatList);
	DDX_Control(pDX, IDC_EDIT_CHAT, m_wndChatEdit);
	//DDX_Control(pDX, IDC_BTN_SEND, m_wndChatBtn);
}


BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_FILE, OnBtnFile)
END_MESSAGE_MAP()

// ���Ͱ�ť
void CChatView::OnBtnSend()
{
	if (m_pUserClient == NULL)
	{
		return;
	}
	CString strData;
	m_wndChatEdit.GetWindowText(strData);

	//AfxMessageBox(_T("AAAAA"));

	// ��ȡUserView�ĵ�ַ
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	UserView* uv = (UserView*)pMain->mSplitter.GetPane(0, 0);

	CListCtrl& theCtrl = uv->GetListCtrl();
	int iCount = theCtrl.GetItemCount();
	AddChat(strData, _T("My word"));

	for (int iItem = 0; iItem < iCount; ++iItem) {
		if (theCtrl.GetCheck(iItem)) {
			//AfxMessageBox(strData);
			CString strIP = theCtrl.GetItemText(iItem, 2);
			//AfxMessageBox(strIP);
			m_pUserClient->SendChat(strIP, strData);
		}
	}
}

//������ʾ����
void CChatView::AddChat(CString strChat, CString strIP)
{
	//AfxMessageBox(strChat);
	CString strData = strIP + _T(":") + strChat;

	int nItem = m_wndChatList.AddString(strData);
	m_wndChatList.SetCurSel(nItem);
}

// ��ʼ��
void CChatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}


#include "FileThread.h"
// ���ļ�
void CChatView::OnBtnFile()
{
	//ѡ���͵��ļ�
	CFileDialog dlg(TRUE);
	if (IDOK != dlg.DoModal())
	{
		return;
	}
	CString strFilePath = dlg.GetPathName();

	// ��ȡUserView�ĵ�ַ
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	UserView* uv = (UserView*)pMain->mSplitter.GetPane(0, 0);

	CListCtrl& theCtrl = uv->GetListCtrl();
	int SendThreadNum = theCtrl.GetItemCount();

	for (int iItem = 0; iItem < SendThreadNum; ++iItem)
	{
		if (theCtrl.GetCheck(iItem)) {
			//AfxMessageBox("dsfsdfsdf");
			CString strIP = theCtrl.GetItemText(iItem, 2);
			//����һ�������߳�  ����
			CFileThread* pFileThread = (CFileThread*)
				AfxBeginThread(RUNTIME_CLASS(CFileThread),
					THREAD_PRIORITY_NORMAL,
					0,
					CREATE_SUSPENDED);

			//���ò��� �� socket �� ip ����
			//��m_bSendDlg=TRUE;
			//	strIP = _T("127.0.0.1");
			pFileThread->SetSocket(strFilePath, strIP, TRUE);
			//��ʼ�߳�
			pFileThread->ResumeThread();
		}
		
	}
}
