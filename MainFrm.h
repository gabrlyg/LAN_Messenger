
// MainFrm.h : CMainFrame ��Ľӿ�
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

// ����
public:
	// �ָ�������
	CSplitterWnd mSplitter;
	// �����
	UserServer mUserServer;
	// �ͻ���
	UserClient mUserClient;

	CFileServer mFileServer;

// ����
public:
	void Initialize();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// ʵ��
public:
	virtual ~CMainFrame();

// ���ɵ���Ϣӳ�亯��
protected:  // �ؼ���Ƕ���Ա
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};


