#pragma once

#include "stdafx.h"

class UserView :
	public CListView
{
protected:
	UserView();
	DECLARE_DYNCREATE(UserView)

// 属性
public:
	BOOL m_bHit; // 判断是点击操作还是插入操作
				 // 该变量初始赋FALSE，当有鼠标点击item时赋TRUE
				 // 检测完是否有CheckBox被点击后重新复位为FALSE

// 操作
public:
	// 添加用户
	void AddUser(CString strName, CString strIp);
	// 查找用户
	int FindUser(CString strIp);
	// 删除用户
	void DelUser(CString strIp);
	// 判断复选框事件
	//void OnNMClickCheckbox(NMHDR *pNMHDR, LRESULT *pResult);
	//void OnLvnItemchangedCheckbox(NMHDR *pNMHDR, LRESULT *pResult);
	// 记录所有被勾选的行号
	//int* GetNumber();

// 重写
protected:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	virtual ~UserView();

protected:
	
	// 创建“计算机名称”，“IP地址”栏目
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 判断各线程的heartbeat
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};

