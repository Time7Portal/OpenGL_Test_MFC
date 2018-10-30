
// OpenGL_Test_MFCDlg.h : ��� ����
//

#pragma once

#include "glut/glut.h"
#include <gl/glu.h>

#include "glm//vec3.hpp" // glm::vec3
#include "glm//vec4.hpp" // glm::vec4
#include "glm//mat4x4.hpp" // glm::mat4
#include "glm//gtc//matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm//gtc//quaternion.hpp"
#include "glm//gtx//quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <stdio.h>
#include <conio.h>
#include <vector>
#include "afxwin.h"

#include "OpenGL_Static.h"
#include "afxcmn.h"

#include "resource.h"
using namespace std;

struct Track_Ball_Info {
	GLfloat width;
	GLfloat height;
	GLfloat prev_X;
	GLfloat prev_Y;
	GLfloat X;
	GLfloat Y;
	glm::vec3 prev_pos;
	glm::vec3 pos;
};

// ----------- ������ ������ ������ ����ü ------------
struct sub_tri_index_info { // �� ���� ��ġ
	int point_index;
	int Angle_index;
};

struct tri_index_info { // ���� 3���� ��Ƽ� �ٰ����� �ﰢ������ ����.
	sub_tri_index_info data[3];
	glm::vec3 N; // �ﰢ�� �� ����
};
// ----------------------------------------------------

// --------- ������ ���Ͽ��� ���� ��ǥ��. -------------
struct Coord_Info_Read_Data {
	int pos_x, pos_y, depth;
	FLOAT clip_pos_x, clip_pos_y;
};
// ----------------------------------------------------

// --------- �������� ��ǥ��. -------------------------
struct Coord_Info_Rendering_Data {
	int depth;
	FLOAT clip_pos_x, clip_pos_y;
	glm::vec4 pos_in_view[360], pos_in_model[360], pos_in_local[360];
	glm::vec4 prev_rotate_cup_surface_pos_in_model[360], cup_surface_pos_in_model[360];
	glm::vec3 vertex_Normal[360];
};
// ----------------------------------------------------

// ----------- ��ǥ���ó� �������ÿ� ���̴� ��� ���� ������ ����ü --------------------
struct matrix_info
{
	glm::vec3 cam_pos;
	glm::vec3 cam_view_dir;
	GLfloat dist;
	glm::mat4 model_mat;
	glm::mat4 inv_model_mat;
	glm::mat4 view_mat;
	glm::mat4 inv_view_mat;
	glm::mat4 proj_mat;
	glm::mat4 inv_proj_mat;

	glm::mat4 model_Rotate_mat;
};
// ----------------------------------------------------------------------------------------

// COpenGL_Test_MFCDlg ��ȭ ����
class COpenGL_Test_MFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COpenGL_Test_MFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OPENGL_TEST_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	// ------------------
	void Read_File();
	void Compute_Computing_Matrix(int win_width, int win_height, float camera_near, float camera_far);
	void Compute_Rendering_Matrix(int win_width, int win_height, float camera_near, float camera_far);
	void Compute_LocalPos(int idx, int angle_index);
	void Create_Triangle_Data();
	void Create_Triangle_Normal();
	void Creaete_Vertex_Normal();
	// ------------------

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int total_point; // buffer�� ���ڿ��� �����ϱ� ���� �� �ڿ��� �׻� NULL���ڸ� ���� �ڸ��� ������ش�.
	int floor_center_idx;

	// ������ ����,���� ���̸� ���Ѵ�.
	int win_width;
	int win_height;

	// ������ near, far �����Ѵ�.
	float camera_near;
	float camera_far;

	int Angle_index_Step;
	int Point_Step;

	bool Cover_Visible_Flag;

	bool vertex_mode_flag;
	bool wireframe_mode_flag;
	bool normal_mode_flag;
	bool flat_shading_mode_flag;
	bool Back_Face_flag;

	GLfloat fov;

	GLUquadric *sphere; // object ����
	glm::vec3 light_pos;

	Track_Ball_Info tbi;
	vector < tri_index_info > tri_index_info_list; // ��ü �ﰢ�� ����Ʈ.
	vector < tri_index_info > floor_tri_list;
	Coord_Info_Read_Data* data_Read_Data = 0;
	Coord_Info_Rendering_Data* data_Rendering_Data = 0;
	Coord_Info_Rendering_Data cup_down_floor_center;
	matrix_info Computing_mat_info; // ��ǥ ����
	matrix_info Rendering_mat_info; // ��������

	afx_msg void OnBnClickedButton1();
	COpenGL_Static m_OpenGL_View;
	CProgressCtrl m_Progress;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
};
