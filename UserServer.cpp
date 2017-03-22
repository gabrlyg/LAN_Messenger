#include "UserServer.h"
#include "stdafx.h"
#include "FinalProject.h"
#include "MainFrm.h"
#include <winsock2.h>
#include <string>
#include <sstream>
using namespace std;

#pragma comment(lib,"WS2_32.lib")

UserServer::UserServer() {
	m_pUserView = NULL;
	m_svrSocket = NULL;
}

UserServer::~UserServer(){}

//��ʼ��User������
BOOL UserServer::InitServer() {
	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// ����UDP������  IPV4 ������ UDP
	m_svrSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// �쳣���
	if (m_svrSocket == INVALID_SOCKET) {
		AfxMessageBox(_T("Failed socket()"));
		//WSACleanup();
		return FALSE;
	}
	// �󶨶˿ں�IP
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_USERSVR);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	if (bind(m_svrSocket, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		AfxMessageBox(_T("Failed bind()"));
		//WSACleanup();
		return FALSE;
	}
	// �����������߳�
	AfxBeginThread(UserThread, this);

	return TRUE;
	
}

//�������ݵ��߳�
UINT UserServer::UserThread(LPVOID pParam) {

	UserServer* pThis = (UserServer*)pParam;
	// ���ܿͻ������ݣ�UDP��
	while (TRUE) {
		UDPPACKET packet = { 0 };
		sockaddr_in addr = { 0 };
		int iLen = sizeof(addr);
		//�ж��쳣
		if (recvfrom(pThis->m_svrSocket, (char*)&packet,
			sizeof(packet), 0, (struct sockaddr*)&addr, &iLen) == SOCKET_ERROR) {
			AfxMessageBox(_T("Failed recvfrom()"));
		}
		// ת����ַΪchar*
		char* pszIp = inet_ntoa(addr.sin_addr);

		switch (packet.header.dwCmdID)
		{
		case NETCMDID_USERBROADCAST: // �㲥
			//AfxMessageBox(_T("AAAAAAA"));
			pThis->OnUserBroadcast((LPUSERBROADCAST)&packet, pszIp);
			break;
		case NETCMDID_USERQUIT: // �˳�
			pThis->OnUserQuit((LPUSERQUIT)&packet, pszIp);
			break;
		case NETCMDID_USERCHAT: // ����
			//AfxMessageBox(_T("123123123"));
			pThis->OnUserChat((LPUSERCHAT)&packet, pszIp);
			break;
		default:
			break;
		}
	}

	return 0;
}

//�����û��㲥���������� ����˰�������ʾ�� UserView��ͼ��������
BOOL UserServer::OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, CHAR* pszIp) {
	// �û��б���ڣ������AddUser����
	if (m_pUserView != NULL) {
		//AfxMessageBox((LPCTSTR)(pUserBroadcast->szName));
		
		char* str = pUserBroadcast->szName;
		CString tmp;
		tmp.Format(_T("%s"), str);
		//AfxMessageBox(tmp);
		m_pUserView->AddUser(tmp, CString(pszIp));
	}
	return TRUE;
}

//�����û������˳� ����˰�UserView��ͼ�� list�б������Ӧ���û�ɾ��
BOOL UserServer::OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIp) {
	// �û��б���ڣ������DelUser����
	if (m_pUserView)
	{
		m_pUserView->DelUser(CString(pszIp));
	}
	return TRUE;
}

//������������
BOOL UserServer::OnUserChat(LPUSERCHAT pUserChat, CHAR* pszIP)
{
	if (pUserChat != NULL)
	{
		if (pUserChat != NULL) {
			m_pChatView->AddChat(pUserChat->szChat, pszIP);
		}
	}
	return TRUE;
}