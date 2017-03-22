#pragma once

#include "stdafx.h"

#define PORT_USERSVR 8989
#define PORT_FILESVR 8990

// ���ݰ��İ�ͷ
typedef struct _tagNetHeader
{
	DWORD  dwVersion;
	DWORD  dwCmdID;
	DWORD  dwDataLength;
}NETHEADER, *LPNETHEADER;

// UDP���ݱ�
typedef struct _tagUDPPacket
{
	NETHEADER	header;
	CHAR		szData[256];
}UDPPACKET, *LPUDPPACKET;

// �û��㲥���ݰ�
#define NETCMDID_USERBROADCAST 1
typedef struct _tagUserBroadcast
{
	NETHEADER	header;
	CHAR		szName[128];
	//CHAR		szSign[128];
}USERBROADCAST, *LPUSERBROADCAST;

// �û������˳����ݰ�
#define NETCMDID_USERQUIT 2
typedef struct _tagUserQuit
{
	NETHEADER	header;
	DWORD		dwExitCode;
}USERQUIT, *LPUSERQUIT;

// ��������
#define NETCMDID_USERCHAT 3
typedef struct _tagUserChat
{
	NETHEADER	header;
	char		szChat[256];
}USERCHAT, *LPUSERCHAT;

// �����ļ�  
#define  NETCMDID_SENDFILE  4
typedef struct  _tagSendFile
{
	CHAR  szFileName[256];
	DWORD dwFileLength;
}SENDFILE, *LPSENDFILE;
