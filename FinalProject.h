
// FinalProject.h : FinalProject Ӧ�ó������ͷ�ļ�
//
#pragma once

#include "resource.h"       // ������


// CFinalProjectApp:
// �йش����ʵ�֣������ FinalProject.cpp
//

class CFinalProjectApp : public CWinApp
{
public:
	CFinalProjectApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFinalProjectApp theApp;
