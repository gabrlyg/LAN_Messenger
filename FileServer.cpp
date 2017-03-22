// FileServer.cpp: implementation of the CFileServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileServer.h"
#include "FileThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileServer::CFileServer()
{

}

CFileServer::~CFileServer()
{

}

BOOL CFileServer::InitServer()
{
	//����socket
	m_svrSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_svrSocket)
	{
		AfxMessageBox("������׽��ִ��� ʧ��");

		return FALSE;
	}
	//��IP�˿�
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESVR);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	bind(m_svrSocket, (struct sockaddr*)&addr, sizeof(addr));

	//����״̬
	listen(m_svrSocket, 5);

	//�����Ⱥ�ͻ��˵��̣߳���Ϊ�Ⱥ�����������
	AfxBeginThread(FileThread, this);


	return TRUE;

}


UINT CFileServer::FileThread(LPVOID pParam)
{
	CFileServer* pThis = (CFileServer*)pParam;

	while (1)
	{
		//�Ⱥ�ͻ������ӣ��ͻ���socket����
		SOCKADDR_IN clientAddr = { 0 };
		int nLen = sizeof(clientAddr);
		//��������  �ŵ�һ���߳�����
		SOCKET clientSocket = accept(pThis->m_svrSocket,
			(SOCKADDR*)&clientAddr,
			&nLen);

		if (INVALID_SOCKET == clientSocket)
		{
			continue;
		}

		//�õ�clientSocket �Ϳ��ԺͿͻ���ͨ��
		CHAR*  pszIP = inet_ntoa(clientAddr.sin_addr);

		pThis->OnConnect(clientSocket, pszIP);
	}
}

void CFileServer::OnConnect(SOCKET clientSocket, LPSTR pszIP)
{
	//����һ�������߳�(������Ϣѭ��)  ����
	CFileThread* pFileThread = (CFileThread*)
		AfxBeginThread(RUNTIME_CLASS(CFileThread),
			THREAD_PRIORITY_NORMAL,
			0,
			CREATE_SUSPENDED);

	//���ò����� socket �� ip����
	pFileThread->SetSocket(clientSocket, pszIP);

	//��ʼ�߳�
	pFileThread->ResumeThread();

}