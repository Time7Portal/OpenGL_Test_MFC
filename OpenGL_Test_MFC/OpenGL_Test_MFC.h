
// OpenGL_Test_MFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COpenGL_Test_MFCApp:
// �� Ŭ������ ������ ���ؼ��� OpenGL_Test_MFC.cpp�� �����Ͻʽÿ�.
//

class COpenGL_Test_MFCApp : public CWinApp
{
public:
	COpenGL_Test_MFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern COpenGL_Test_MFCApp theApp;