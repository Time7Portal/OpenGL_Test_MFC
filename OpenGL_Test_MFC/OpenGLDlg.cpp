// OpenGLDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "OpenGL_Test_MFC.h"
#include "OpenGLDlg.h"
#include "afxdialogex.h"


// COpenGLDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COpenGLDlg, CDialogEx)

COpenGLDlg::COpenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenGLDlg::IDD, pParent)
{

}

COpenGLDlg::~COpenGLDlg()
{
}

void COpenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COpenGLDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGLDlg 메시지 처리기입니다.
