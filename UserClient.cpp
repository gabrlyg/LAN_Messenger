#include "UserClient.h"
#include "stdafx.h"
#include "MainFrm.h"
#include <winsock2.h>
#include <string>

using namespace std;

#pragma comment(lib,"WS2_32.lib")

UserClient::UserClient() {}

UserClient::~UserClient() {}

// ��ʼ���ͻ���
BOOL UserClient::InitClient() {
	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// ����SOCKET
	m_ClientSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed socket()"));
		return FALSE;
	}

	// ���ù㲥ģʽ
	BOOL bBroadCast = true;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_BROADCAST, (char FAR*)&bBroadCast, sizeof(bool));
	
	return TRUE;
}

// �㲥����
BOOL UserClient::Broadcast()
{
	//��������

	USERBROADCAST  user = { 0 };
	user.header.dwVersion = 1;
	user.header.dwCmdID = NETCMDID_USERBROADCAST;  // �㲥��������
	user.header.dwDataLength = sizeof(user) - sizeof(NETHEADER);

	DWORD nLen = 128;
	GetComputerName(user.szName, &nLen);
	//strcpy(user.szSign, "Hello World");

	// ʹ��SendData()�㲥����
	SendData((CHAR*)&user, sizeof(user));

	return TRUE;
}

// ��������
BOOL UserClient::SendData(CHAR* psxData, UINT nLen, LPCSTR strIp)
{
	//AfxMessageBox((LPCTSTR)strIp);
	//���ù㲥��ַ
	struct sockaddr_in addr = { 0 };//ָ��Ŀ���׽��ֵĵ�ַ
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_USERSVR);

	if (strIp == NULL)
	{
		addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
		//���͹㲥����
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

// �û������˳�
BOOL UserClient::UserQuit() {
	USERQUIT quit = { 0 };
	quit.header.dwVersion = 1;
	quit.header.dwCmdID = NETCMDID_USERQUIT;
	quit.header.dwDataLength = sizeof(quit) - sizeof(USERQUIT);
	quit.dwExitCode = 0;

	SendData((CHAR*)&quit, sizeof(quit));

	return TRUE;
}

//����
BOOL UserClient::SendChat(CString strIP, CString strData)
{
	//��������
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
	// ��������
	SendData((LPSTR)&chat, sizeof(chat), strIP);

	//delete[] ptxtTemp;

	return TRUE;
}
