#pragma once
#include "stdafx.h"
#include "UserClient.h"
#include "Resource.h"

class CChatView : public CFormView
{
protected:
	CChatView();      
	DECLARE_DYNCREATE(CChatView)


public:
	enum { IDD = IDD_FORMVIEW };
	
	CListBox	m_wndChatList;
	CEdit		m_wndChatEdit;
	CButton		m_wndChatBtn;

// 特性
public:
	UserClient* m_pUserClient;

// 操作
public:
	// 添加聊天
	void AddChat(CString strChat, CString strIP);

// 重写
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

// 实现
protected:
	virtual ~CChatView();
	// 发送按钮
	afx_msg void OnBtnSend();
	// 文件按钮
	afx_msg void OnBtnFile();
	DECLARE_MESSAGE_MAP()
};