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

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.cx = 1020;
	cs.cy = 910;

	cs.style = cs.style & (~WS_THICKFRAME);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~(WS_MAXIMIZEBOX); // 禁用最大化
	cs.lpszClass = AfxRegisterWndClass(0);
	

	return TRUE;
}

// CMainFrame 消息处理程序

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// 切分窗口， 上面部分为UserView, 下面部分为ChatView
	mSplitter.CreateStatic(this, 2, 1);
	mSplitter.CreateView(0, 0, RUNTIME_CLASS(UserView), CSize(1000, 300), pContext);
	mSplitter.CreateView(1, 0, RUNTIME_CLASS(CChatView), CSize(1000, 400), pContext);

	// 获取UserView地址
	mUserServer.m_pUserView = (UserView*)mSplitter.GetPane(0, 0);

	// 获取ChatView地址
	CChatView* pChatView = (CChatView*)mSplitter.GetPane(1, 0);

	mUserServer.m_pChatView = pChatView;

	pChatView->m_pUserClient = &mUserClient;

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

// 初始化
void CMainFrame::Initialize()
{
	if (mUserServer.InitServer() != TRUE) {
		AfxMessageBox(_T("用户创建服务端失败！"));
	}
	if (mUserClient.InitClient() != TRUE) {
		AfxMessageBox(_T("用户创建客户端失败！"));
	}
	if (mFileServer.InitServer() != TRUE) {
		AfxMessageBox(_T("文件服务器创建失败！"));
	}


	mUserClient.Broadcast();

	SetTimer(1, 1000 * 10, NULL);
}

// 计时器
void CMainFrame::OnTimer(UINT nIDEvent)
{
	mUserClient.Broadcast();
	//mUserClient.SendData("123",3,"192.168.43.223");

	CFrameWnd::OnTimer(nIDEvent);
}

// 关闭程序，用户正常退出
void CMainFrame::OnClose()
{
	mUserClient.UserQuit();

	CFrameWnd::OnClose();
}