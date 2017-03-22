#pragma once
#include "stdafx.h"
#include "UserClient.h"
#include "Resource.h"

class CChatView : public CFormView
{
protected:
	CChatView();      
	DECLARE_DYNCREATE(CChatView)


public:
	enum { IDD = IDD_FORMVIEW };
	
	CListBox	m_wndChatList;
	CEdit		m_wndChatEdit;
	CButton		m_wndChatBtn;

// ����
public:
	UserClient* m_pUserClient;

// ����
public:
	// �������
	void AddChat(CString strChat, CString strIP);

// ��д
public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

// ʵ��
protected:
	virtual ~CChatView();
	// ���Ͱ�ť
	afx_msg void OnBtnSend();
	// �ļ���ť
	afx_msg void OnBtnFile();
	DECLARE_MESSAGE_MAP()
};