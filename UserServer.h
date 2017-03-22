#pragma once

#include "UserView.h"
#include "ChatView.h"
#include "stdafx.h"

class UserServer{
public:
	UserServer();
	virtual ~UserServer();

public:
	//初始化User服务器
	BOOL InitServer();
	//接受数据的线程
	static UINT UserThread(LPVOID pParam);
	//处理用户广播过来的数据 服务端把数据显示到 UserView视图窗口上面
	BOOL OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, CHAR* pszIP);

	//处理用户正常退出 服务端把UserView视图中 list列表里面对应的用户删除
	BOOL OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIP);

	//处理聊天数据
	BOOL OnUserChat(LPUSERCHAT pUserChat, CHAR* pszIP);

public:
	SOCKET			m_svrSocket; // 服务端socket
	UserView*		m_pUserView; // 用户列表
	CChatView*		m_pChatView; // 聊天内容
};