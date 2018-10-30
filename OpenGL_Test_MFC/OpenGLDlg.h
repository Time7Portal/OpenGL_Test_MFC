#pragma once


// COpenGLDlg 대화 상자입니다.

class COpenGLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COpenGLDlg)

public:
	COpenGLDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COpenGLDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPENGL_TEST_MFC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
