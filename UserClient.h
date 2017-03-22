#pragma once
#include "stdafx.h"
#include "UserView.h"

class UserClient {
public:
	UserClient();
	virtual ~UserClient();

public:
	//��ʼ���ͻ���
	BOOL InitClient();
	//�㲥����
	BOOL Broadcast();
	//��������
	BOOL SendData(CHAR* psxData, UINT nLen, LPCSTR strIP = NULL);

	//�����ر��˳�����
	BOOL UserQuit();

	//����
	BOOL SendChat(CString strIP, CString strData);

public:
	SOCKET m_ClientSocket;
};