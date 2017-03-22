
// FinalProject.h : FinalProject 应用程序的主头文件
//
#pragma once

#include "resource.h"       // 主符号


// CFinalProjectApp:
// 有关此类的实现，请参阅 FinalProject.cpp
//

class CFinalProjectApp : public CWinApp
{
public:
	CFinalProjectApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFinalProjectApp theApp;
