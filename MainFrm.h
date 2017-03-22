
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
//#include "ChildView.h"
#include "UserClient.h"
#include "UserServer.h"
#include "UserView.h"
#include "FileServer.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 特性
public:
	// 分割主窗体
	CSplitterWnd mSplitter;
	// 服务端
	UserServer mUserServer;
	// 客户端
	UserClient mUserClient;

	CFileServer mFileServer;

// 操作
public:
	void Initialize();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// 实现
public:
	virtual ~CMainFrame();

// 生成的消息映射函数
protected:  // 控件条嵌入成员
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};


