
// DGameFrame.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDGameFrameApp:
// �йش����ʵ�֣������ DGameFrame.cpp
//

class CDGameFrameApp : public CWinApp
{
public:
	CDGameFrameApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDGameFrameApp theApp;