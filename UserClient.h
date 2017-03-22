#pragma once
#include "stdafx.h"
#include "UserView.h"

class UserClient {
public:
	UserClient();
	virtual ~UserClient();

public:
	//初始化客户端
	BOOL InitClient();
	//广播数据
	BOOL Broadcast();
	//发送数据
	BOOL SendData(CHAR* psxData, UINT nLen, LPCSTR strIP = NULL);

	//正常关闭退出程序
	BOOL UserQuit();

	//聊天
	BOOL SendChat(CString strIP, CString strData);

public:
	SOCKET m_ClientSocket;
};