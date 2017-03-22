#include "stdafx.h"
#include "FinalProject.h"
#include "ChatView.h"
#include "MainFrm.h"

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CFrameWnd::OnCreate(lpcs) == -1) {
		return -1;
	}

	Initialize();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.cx = 1020;
	cs.cy = 910;

	cs.style = cs.style & (~WS_THICKFRAME);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~(WS_MAXIMIZEBOX); // �������
	cs.lpszClass = AfxRegisterWndClass(0);
	

	return TRUE;
}

// CMainFrame ��Ϣ�������

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// �зִ��ڣ� ���沿��ΪUserView, ���沿��ΪChatView
	mSplitter.CreateStatic(this, 2, 1);
	mSplitter.CreateView(0, 0, RUNTIME_CLASS(UserView), CSize(1000, 300), pContext);
	mSplitter.CreateView(1, 0, RUNTIME_CLASS(CChatView), CSize(1000, 400), pContext);

	// ��ȡUserView��ַ
	mUserServer.m_pUserView = (UserView*)mSplitter.GetPane(0, 0);

	// ��ȡChatView��ַ
	CChatView* pChatView = (CChatView*)mSplitter.GetPane(1, 0);

	mUserServer.m_pChatView = pChatView;

	pChatView->m_pUserClient = &mUserClient;

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

// ��ʼ��
void CMainFrame::Initialize()
{
	if (mUserServer.InitServer() != TRUE) {
		AfxMessageBox(_T("�û����������ʧ�ܣ�"));
	}
	if (mUserClient.InitClient() != TRUE) {
		AfxMessageBox(_T("�û������ͻ���ʧ�ܣ�"));
	}
	if (mFileServer.InitServer() != TRUE) {
		AfxMessageBox(_T("�ļ�����������ʧ�ܣ�"));
	}


	mUserClient.Broadcast();

	SetTimer(1, 1000 * 10, NULL);
}

// ��ʱ��
void CMainFrame::OnTimer(UINT nIDEvent)
{
	mUserClient.Broadcast();
	//mUserClient.SendData("123",3,"192.168.43.223");

	CFrameWnd::OnTimer(nIDEvent);
}

// �رճ����û������˳�
void CMainFrame::OnClose()
{
	mUserClient.UserQuit();

	CFrameWnd::OnClose();
}