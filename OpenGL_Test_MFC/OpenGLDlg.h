#pragma once


// COpenGLDlg ��ȭ �����Դϴ�.

class COpenGLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COpenGLDlg)

public:
	COpenGLDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~COpenGLDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OPENGL_TEST_MFC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
