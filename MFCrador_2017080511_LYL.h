
// MFCrador_2017080511_LYL.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMFCrador_2017080511_LYLApp: 
// 有关此类的实现，请参阅 MFCrador_2017080511_LYL.cpp
//

class CMFCrador_2017080511_LYLApp : public CWinApp
{
public:
	CMFCrador_2017080511_LYLApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFCrador_2017080511_LYLApp theApp;