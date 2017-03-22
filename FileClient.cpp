// FileClient.cpp: implementation of the CFileClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileClient::CFileClient()
{
	m_ClientSocket = INVALID_SOCKET;
}

CFileClient::~CFileClient()
{
	//�Զ��ر�socket
	if (INVALID_SOCKET != m_ClientSocket)
	{
		closesocket(m_ClientSocket);
	}
}


BOOL CFileClient::InitClient()
{
	//����socket
	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_ClientSocket)
	{
		AfxMessageBox(_T("��ʼ���ļ��ͻ��˷�������"));
		return FALSE;
	}
	return TRUE;
}

BOOL CFileClient::ConnectServer(LPCTSTR pszSvrIP)
{

	//���ӷ�������
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESVR);
	addr.sin_addr.S_un.S_addr = inet_addr(pszSvrIP);
	if (SOCKET_ERROR == connect(m_ClientSocket, (SOCKADDR*)&addr, sizeof(addr)))
	{
		/*int a = GetLastError();
		CString aa;
		aa.Format("%d",a);
		AfxMessageBox(aa);*/
		AfxMessageBox(_T("�ͻ������ӷ���˷�������"));
		return FALSE;

	}
	return TRUE;
}

BOOL CFileClient::SendFile(LPCTSTR pszFilePath, CProgressCtrl* pWndProgress)
{
	//��������ͷ
	NETHEADER header = { 0 };
	header.dwVersion = 1;
	header.dwCmdID = NETCMDID_SENDFILE;
	header.dwDataLength = sizeof(SENDFILE);
	SendData(&header, sizeof(header));



	//�����ļ���Ϣ
	CFile file;
	if (FALSE == file.Open(pszFilePath, CFile::modeRead))
	{
		return FALSE;
	}

	SENDFILE sendFile = { 0 };
	strcpy(sendFile.szFileName, file.GetFileName());
	sendFile.dwFileLength = file.GetLength();
	SendData(&sendFile, sizeof(sendFile));


	if (pWndProgress != NULL)
	{
		//������
		pWndProgress->SetRange32(0, sendFile.dwFileLength);
	}
	//�����ļ�����
	CHAR szBuf[4096] = { 0 };//ÿ�η���4K�ֽ�
	DWORD nLeft = file.GetLength();
	while (nLeft  > 0)
	{
		//���㱾�ζ�ȡ��������
		int nSend = 4096;
		if (nLeft < nSend)
		{
			nSend = nLeft;
		}
		//��ȡ����
		file.Read(szBuf, nSend);

		//���Խ���ȡ����szBuf���м��ܣ������ܺ�����ݷ���
		//�Է����յ����ݺ���н���

		//��������
		SendData(szBuf, nSend);
		//����ʣ��������
		nLeft = nLeft - nSend;

		if (pWndProgress != NULL)
		{
			pWndProgress->SetPos(sendFile.dwFileLength - nLeft);
		}

	}

	//�ر��ļ�
	file.Close();
	return TRUE;
}

BOOL CFileClient::SendData(LPVOID pData, DWORD nLen)
{
	LPSTR pTmpData = (LPSTR)pData;
	int   nLeft = nLen;

	while (nLeft > 0)
	{
		int nSend = send(m_ClientSocket, pTmpData, nLeft, 0);
		if (SOCKET_ERROR == nSend)
		{
			return FALSE;
		}
		nLeft = nLeft - nSend;
		pTmpData = pTmpData + nSend;
	}
	return TRUE;
}

