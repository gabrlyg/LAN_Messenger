// FileClient.h: interface for the CFileClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECLIENT_H__1ED57A4A_6C8A_4635_AB08_853DF3DBA067__INCLUDED_)
#define AFX_FILECLIENT_H__1ED57A4A_6C8A_4635_AB08_853DF3DBA067__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileClient
{
public:
	CFileClient();
	virtual ~CFileClient();
public:
	//��ʼ���ļ��ͻ���
	BOOL InitClient();
	BOOL ConnectServer(LPCTSTR pszSvrIP);
	//�����ļ�
	BOOL SendFile(LPCTSTR pszFilePath, CProgressCtrl* pWndProgress = NULL);
	//��������
	BOOL SendData(LPVOID pData, DWORD nLen);

public:
	//�ͻ���socket
	SOCKET m_ClientSocket;
};

#endif // !defined(AFX_FILECLIENT_H__1ED57A4A_6C8A_4635_AB08_853DF3DBA067__INCLUDED_)
