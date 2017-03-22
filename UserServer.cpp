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

//初始化User服务器
BOOL UserServer::InitServer() {
	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// 创建UDP服务器  IPV4 数据流 UDP
	m_svrSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// 异常监测
	if (m_svrSocket == INVALID_SOCKET) {
		AfxMessageBox(_T("Failed socket()"));
		//WSACleanup();
		return FALSE;
	}
	// 绑定端口和IP
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_USERSVR);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	if (bind(m_svrSocket, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		AfxMessageBox(_T("Failed bind()"));
		//WSACleanup();
		return FALSE;
	}
	// 创建服务器线程
	AfxBeginThread(UserThread, this);

	return TRUE;
	
}

//接受数据的线程
UINT UserServer::UserThread(LPVOID pParam) {

	UserServer* pThis = (UserServer*)pParam;
	// 接受客户端数据（UDP）
	while (TRUE) {
		UDPPACKET packet = { 0 };
		sockaddr_in addr = { 0 };
		int iLen = sizeof(addr);
		//判断异常
		if (recvfrom(pThis->m_svrSocket, (char*)&packet,
			sizeof(packet), 0, (struct sockaddr*)&addr, &iLen) == SOCKET_ERROR) {
			AfxMessageBox(_T("Failed recvfrom()"));
		}
		// 转换地址为char*
		char* pszIp = inet_ntoa(addr.sin_addr);

		switch (packet.header.dwCmdID)
		{
		case NETCMDID_USERBROADCAST: // 广播
			//AfxMessageBox(_T("AAAAAAA"));
			pThis->OnUserBroadcast((LPUSERBROADCAST)&packet, pszIp);
			break;
		case NETCMDID_USERQUIT: // 退出
			pThis->OnUserQuit((LPUSERQUIT)&packet, pszIp);
			break;
		case NETCMDID_USERCHAT: // 聊天
			//AfxMessageBox(_T("123123123"));
			pThis->OnUserChat((LPUSERCHAT)&packet, pszIp);
			break;
		default:
			break;
		}
	}

	return 0;
}

//处理用户广播过来的数据 服务端把数据显示到 UserView视图窗口上面
BOOL UserServer::OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, CHAR* pszIp) {
	// 用户列表存在，则进行AddUser操作
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

//处理用户正常退出 服务端把UserView视图中 list列表里面对应的用户删除
BOOL UserServer::OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIp) {
	// 用户列表存在，则进行DelUser操作
	if (m_pUserView)
	{
		m_pUserView->DelUser(CString(pszIp));
	}
	return TRUE;
}

//处理聊天数据
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