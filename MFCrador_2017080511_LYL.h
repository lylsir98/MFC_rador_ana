
// MFCrador_2017080511_LYL.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCrador_2017080511_LYLApp: 
// �йش����ʵ�֣������ MFCrador_2017080511_LYL.cpp
//

class CMFCrador_2017080511_LYLApp : public CWinApp
{
public:
	CMFCrador_2017080511_LYLApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCrador_2017080511_LYLApp theApp;