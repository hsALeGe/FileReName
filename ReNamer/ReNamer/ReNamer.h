
// ReNamer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReNamerApp: 
// �йش����ʵ�֣������ ReNamer.cpp
//

class CReNamerApp : public CWinApp
{
public:
	CReNamerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReNamerApp theApp;