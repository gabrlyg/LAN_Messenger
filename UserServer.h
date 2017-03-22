#pragma once

#include "UserView.h"
#include "ChatView.h"
#include "stdafx.h"

class UserServer{
public:
	UserServer();
	virtual ~UserServer();

public:
	//��ʼ��User������
	BOOL InitServer();
	//�������ݵ��߳�
	static UINT UserThread(LPVOID pParam);
	//�����û��㲥���������� ����˰�������ʾ�� UserView��ͼ��������
	BOOL OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, CHAR* pszIP);

	//�����û������˳� ����˰�UserView��ͼ�� list�б������Ӧ���û�ɾ��
	BOOL OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIP);

	//������������
	BOOL OnUserChat(LPUSERCHAT pUserChat, CHAR* pszIP);

public:
	SOCKET			m_svrSocket; // �����socket
	UserView*		m_pUserView; // �û��б�
	CChatView*		m_pChatView; // ��������
};