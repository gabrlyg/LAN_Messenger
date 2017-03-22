#include "UserClient.h"
#include "stdafx.h"
#include "MainFrm.h"
#include <winsock2.h>
#include <string>

using namespace std;

#pragma comment(lib,"WS2_32.lib")

UserClient::UserClient() {}

UserClient::~UserClient() {}

// 初始化客户端
BOOL UserClient::InitClient() {
	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// 创建SOCKET
	m_ClientSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed socket()"));
		return FALSE;
	}

	// 设置广播模式
	BOOL bBroadCast = true;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_BROADCAST, (char FAR*)&bBroadCast, sizeof(bool));
	
	return TRUE;
}

// 广播数据
BOOL UserClient::Broadcast()
{
	//构造数据

	USERBROADCAST  user = { 0 };
	user.header.dwVersion = 1;
	user.header.dwCmdID = NETCMDID_USERBROADCAST;  // 广播数据类型
	user.header.dwDataLength = sizeof(user) - sizeof(NETHEADER);

	DWORD nLen = 128;
	GetComputerName(user.szName, &nLen);
	//strcpy(user.szSign, "Hello World");

	// 使用SendData()广播数据
	SendData((CHAR*)&user, sizeof(user));

	return TRUE;
}

// 发送数据
BOOL UserClient::SendData(CHAR* psxData, UINT nLen, LPCSTR strIp)
{
	//AfxMessageBox((LPCTSTR)strIp);
	//设置广播地址
	struct sockaddr_in addr = { 0 };//指向目的套接字的地址
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_USERSVR);

	if (strIp == NULL)
	{
		addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
		//发送广播数据
		if (sendto(m_ClientSocket, psxData, nLen, 0, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			AfxMessageBox(_T("Failed sendto()"));
		}
	}
	else
	{
		//AfxMessageBox((LPCTSTR)strIp);
		//SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		addr.sin_addr.S_un.S_addr = inet_addr(strIp);
		if (sendto(m_ClientSocket, psxData, nLen, 0, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
			AfxMessageBox(_T("Failed sendto()"));
		}
	}

	return TRUE;
}

// 用户正常退出
BOOL UserClient::UserQuit() {
	USERQUIT quit = { 0 };
	quit.header.dwVersion = 1;
	quit.header.dwCmdID = NETCMDID_USERQUIT;
	quit.header.dwDataLength = sizeof(quit) - sizeof(USERQUIT);
	quit.dwExitCode = 0;

	SendData((CHAR*)&quit, sizeof(quit));

	return TRUE;
}

//聊天
BOOL UserClient::SendChat(CString strIP, CString strData)
{
	//构造数据
	USERCHAT chat = { 0 };
	chat.header.dwVersion = 1;
	chat.header.dwCmdID = NETCMDID_USERCHAT;
	chat.header.dwDataLength = sizeof(chat) - sizeof(USERCHAT);
	// CString to char*
	//CString str1 = strData;
	//int len = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
	//char *ptxtTemp = str1.GetBuffer(str1.GetLength());
	//str1.ReleaseBuffer();
	//WideCharToMultiByte(CP_ACP, 0, str1, -1, ptxtTemp, len, NULL, NULL);
	strcpy(chat.szChat, strData);
	//delete[] ptxtTemp;

	// CString to char*
	//str1 = strIP;
	//len = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
	//ptxtTemp = str1.GetBuffer(str1.GetLength());
	//str1.ReleaseBuffer();
	//WideCharToMultiByte(CP_ACP, 0, str1, -1, ptxtTemp, len, NULL, NULL);
	// 发送数据
	SendData((LPSTR)&chat, sizeof(chat), strIP);

	//delete[] ptxtTemp;

	return TRUE;
}
