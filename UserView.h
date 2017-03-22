#pragma once

#include "stdafx.h"

class UserView :
	public CListView
{
protected:
	UserView();
	DECLARE_DYNCREATE(UserView)

// ����
public:
	BOOL m_bHit; // �ж��ǵ���������ǲ������
				 // �ñ�����ʼ��FALSE�����������itemʱ��TRUE
				 // ������Ƿ���CheckBox����������¸�λΪFALSE

// ����
public:
	// ����û�
	void AddUser(CString strName, CString strIp);
	// �����û�
	int FindUser(CString strIp);
	// ɾ���û�
	void DelUser(CString strIp);
	// �жϸ�ѡ���¼�
	//void OnNMClickCheckbox(NMHDR *pNMHDR, LRESULT *pResult);
	//void OnLvnItemchangedCheckbox(NMHDR *pNMHDR, LRESULT *pResult);
	// ��¼���б���ѡ���к�
	//int* GetNumber();

// ��д
protected:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	virtual ~UserView();

protected:
	
	// ��������������ơ�����IP��ַ����Ŀ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// �жϸ��̵߳�heartbeat
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};

