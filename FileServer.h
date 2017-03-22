// FileServer.h: interface for the CFileServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESERVER_H__4B87C854_435F_41B2_8659_EAC23A157D8C__INCLUDED_)
#define AFX_FILESERVER_H__4B87C854_435F_41B2_8659_EAC23A157D8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileServer
{
public:
	CFileServer();
	virtual ~CFileServer();

public:
	//��ʼ��������
	BOOL InitServer();
	//���տͻ������ӵ��߳�
	static UINT FileThread(LPVOID pParam);

	//��������
	void OnConnect(SOCKET clientSocket, LPSTR pszIP);

public:
	SOCKET m_svrSocket;

};

#endif // !defined(AFX_FILESERVER_H__4B87C854_435F_41B2_8659_EAC23A157D8C__INCLUDED_)
