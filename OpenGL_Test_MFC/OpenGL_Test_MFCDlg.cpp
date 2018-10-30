
// OpenGL_Test_MFCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "OpenGL_Test_MFC.h"
#include "OpenGL_Test_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenGL_Test_MFCDlg ��ȭ ����



COpenGL_Test_MFCDlg::COpenGL_Test_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenGL_Test_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGL_Test_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENGL_VIEW, m_OpenGL_View);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(COpenGL_Test_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &COpenGL_Test_MFCDlg::OnBnClickedButton1)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON2, &COpenGL_Test_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &COpenGL_Test_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &COpenGL_Test_MFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &COpenGL_Test_MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &COpenGL_Test_MFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &COpenGL_Test_MFCDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &COpenGL_Test_MFCDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &COpenGL_Test_MFCDlg::OnBnClickedButton9)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON10, &COpenGL_Test_MFCDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &COpenGL_Test_MFCDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &COpenGL_Test_MFCDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &COpenGL_Test_MFCDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &COpenGL_Test_MFCDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &COpenGL_Test_MFCDlg::OnBnClickedButton15)
	ON_COMMAND(IDC_RADIO1, &COpenGL_Test_MFCDlg::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &COpenGL_Test_MFCDlg::OnRadio2)
	ON_BN_CLICKED(IDC_BUTTON16, &COpenGL_Test_MFCDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &COpenGL_Test_MFCDlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// COpenGL_Test_MFCDlg �޽��� ó����

BOOL COpenGL_Test_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	total_point = -1; // buffer�� ���ڿ��� �����ϱ� ���� �� �ڿ��� �׻� NULL���ڸ� ���� �ڸ��� ������ش�.
	floor_center_idx = -1;

	// ������ ����,���� ���̸� ���Ѵ�.
	RECT rt;
	GetClientRect(&rt);
	GLfloat cx = (GLfloat)rt.right;
	GLfloat cy = (GLfloat)rt.bottom;
	win_width = (int)cx;
	win_height = (int)cy;

	// ������ near, far �����Ѵ�.
	camera_near = 0.1f;
	camera_far = 10000.0f;

	Angle_index_Step = 10;
	Point_Step = 30; //  1;

	Cover_Visible_Flag = false;

	vertex_mode_flag = false;
	wireframe_mode_flag = false;
	normal_mode_flag = false;

	fov = 45.0f;

	flat_shading_mode_flag = false;

	Back_Face_flag = true;

	CButton*btn1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton*btn2 = (CButton*)GetDlgItem(IDC_RADIO2);
	if (btn1 && btn2)
	{
		btn1->SetCheck(1);
		btn2->SetCheck(0);
	}

	light_pos = glm::vec3(0.0f, 0.0f, 1.0f);

	m_OpenGL_View.Init_OpenGL();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void COpenGL_Test_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COpenGL_Test_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		m_OpenGL_View.Invalidate();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COpenGL_Test_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ----------------------
void COpenGL_Test_MFCDlg::Compute_Computing_Matrix(int win_width, int win_height, float camera_near, float camera_far)
{
	Computing_mat_info.cam_pos = glm::vec3(0.0f, 0.0f, 5.5f); // ī�޶� ��ġ
	Computing_mat_info.cam_view_dir = glm::vec3(0.0f, 0.0f, -1.0f); // ī�޶� ���� ����.
	Computing_mat_info.dist = 2.0f; // 1.0f;

	// ���� �߽���ġ ���ϱ�.
	glm::vec3 cup_pos = Computing_mat_info.cam_pos + Computing_mat_info.cam_view_dir * Computing_mat_info.dist;

	// �� ��� ���.
	Computing_mat_info.model_mat = glm::translate(glm::mat4(), cup_pos);

	// �� ��� ���.
	glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	Computing_mat_info.view_mat = glm::lookAt(Computing_mat_info.cam_pos, cup_pos, UP);

	// ���� ��� ���.
	FLOAT window_aspect = (FLOAT)win_width / (FLOAT)win_height;
	Computing_mat_info.proj_mat = glm::perspective(45.0f, window_aspect, camera_near, camera_far);

	return;
}

void COpenGL_Test_MFCDlg::Compute_Rendering_Matrix(int win_width, int win_height, float camera_near, float camera_far)
{
	Rendering_mat_info.cam_pos = Computing_mat_info.cam_pos;// glm::vec3(0.0f, 0.0f, 5.5f);  // glm::vec3(0.0f, 0.7f, 3.1f);
	Rendering_mat_info.cam_view_dir = Computing_mat_info.cam_view_dir; //  glm::vec3(0.0f, 0.0f, -1.0f);
	Rendering_mat_info.dist = 2.0f;

	// ���� �߽���ġ ���ϱ�.
	glm::vec3 cup_pos = Rendering_mat_info.cam_pos + Rendering_mat_info.cam_view_dir * Rendering_mat_info.dist;

	// �� ��� ���.
	Rendering_mat_info.model_mat = glm::translate(glm::mat4(), cup_pos);

	// �� ��� ���.
	glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	Rendering_mat_info.view_mat = glm::lookAt(Rendering_mat_info.cam_pos, cup_pos, UP);

	// ���� ��� ���.
	FLOAT window_aspect = (FLOAT)win_width / (FLOAT)win_height;
	Rendering_mat_info.proj_mat = glm::perspective(fov, window_aspect, camera_near, camera_far);

	return;
}

void COpenGL_Test_MFCDlg::Compute_LocalPos(int idx, int angle_index)
{
	glm::vec4 tmp_p = glm::vec4(
		data_Rendering_Data[idx].clip_pos_x,
		data_Rendering_Data[idx].clip_pos_y,
		0.0f,
		1.0f
		);

	// ������ ��İ��ؼ� ī�޶� �������� ����.
	tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
	data_Rendering_Data[idx].pos_in_view[angle_index] = tmp_p;

	// ��ī�޶� ��� ���ؼ� �𵨰������� ����. (x, y��)
	tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
	data_Rendering_Data[idx].pos_in_model[angle_index] = tmp_p;

	tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
	// -------------- ��������� 0���϶��� ��ġ. -------------------

	// ------------ ������ ������ ���� ��ġ�� ������� -------------
	// 1. ������ ����
	FLOAT Angle = (FLOAT)angle_index * (FLOAT)Angle_index_Step; // ȸ���� ����.
	FLOAT Rad_Angle = glm::radians(Angle); // ȸ���� ������ ȣ���� 

	// 2. ������ ������ ���� ȸ�� ���ʹϾ� ���.
	glm::vec3 cam_up_dir = glm::vec3(
		Computing_mat_info.view_mat[0].y,
		Computing_mat_info.view_mat[1].y,
		Computing_mat_info.view_mat[2].y
		);
	glm::quat Q = glm::angleAxis(Rad_Angle / 2.0f, cam_up_dir);

	// �����ʹϾ� ���.
	glm::quat Inverse_Q = glm::inverse(Q);

	// 3. ���ʹϾ��� ���ؼ� ȸ���� ��ġ�� ���Ѵ�.
	tmp_p = Q * tmp_p * Inverse_Q;
	// -------------------------------------------------------------

	// ȸ���� ��ġ�� �����Ѵ�.
	data_Rendering_Data[idx].pos_in_local[angle_index] = tmp_p;
	return;
}

void COpenGL_Test_MFCDlg::Create_Triangle_Data()
{
	sub_tri_index_info item[3];
	tri_index_info item2;
	int pi, ai;

	tri_index_info_list.clear();

	int angle_cnt = 360 / Angle_index_Step;
	int point_cnt = total_point / Point_Step;
	if (Point_Step == 1)
		point_cnt--;

	int Progress_cnt = angle_cnt * point_cnt;
	Progress_cnt += angle_cnt * 2;
	m_Progress.SetRange(1, Progress_cnt);

	int Progress_idx = 0;
	m_Progress.SetPos(Progress_idx);

	for (int num_p = 0; num_p < point_cnt; num_p++)
	{
		for (int num_a = 0; num_a < angle_cnt; num_a++)
		{
			pi = (0 + num_p); ai = (0 + num_a) % angle_cnt;
			item[0].point_index = pi; item[0].Angle_index = ai;
			pi = (1 + num_p); ai = (0 + num_a) % angle_cnt;
			item[1].point_index = pi; item[1].Angle_index = ai;
			pi = (0 + num_p); ai = (1 + num_a) % angle_cnt;
			item[2].point_index = pi; item[2].Angle_index = ai;

			item2.data[0] = item[0];
			item2.data[1] = item[1];
			item2.data[2] = item[2];
			tri_index_info_list.push_back(item2);
			m_Progress.SetPos(++Progress_idx);

			pi = (1 + num_p); ai = (0 + num_a) % angle_cnt;
			item[0].point_index = pi; item[0].Angle_index = ai;
			pi = (1 + num_p); ai = (1 + num_a) % angle_cnt;
			item[1].point_index = pi; item[1].Angle_index = ai;
			pi = (0 + num_p); ai = (1 + num_a) % angle_cnt;
			item[2].point_index = pi; item[2].Angle_index = ai;

			item2.data[0] = item[0];
			item2.data[1] = item[1];
			item2.data[2] = item[2];
			tri_index_info_list.push_back(item2);
			m_Progress.SetPos(++Progress_idx);
		}
	}

	// �ٴ� �� ���.
	angle_cnt = 360 / Angle_index_Step;
	float h = (float)total_point / (float)Point_Step;
	if (h - (int)h > 0.0f)
		h = (float)(int)h + 1.0f;

	for (int num_a = 0; num_a < angle_cnt; num_a++)
	{
		pi = (int)h + 1; ai = (0 + num_a) % angle_cnt;
		item[0].point_index = pi; item[0].Angle_index = ai;
		pi = (int)h + 1; ai = (1 + num_a) % angle_cnt;
		item[1].point_index = pi; item[1].Angle_index = ai;
		pi = (int)h + 0; ai = 0;
		item[2].point_index = pi; item[2].Angle_index = ai;

		item2.data[0] = item[0];
		item2.data[1] = item[1];
		item2.data[2] = item[2];
		tri_index_info_list.push_back(item2);
		m_Progress.SetPos(++Progress_idx);
	}

	// �Ѳ� �� ���.
	for (int num_a = 0; num_a < angle_cnt; num_a++)
	{
		pi = (int)h + 1 + 2; ai = (0 + num_a) % angle_cnt;
		item[0].point_index = pi; item[0].Angle_index = ai;
		pi = (int)h + 1 + 2; ai = (1 + num_a) % angle_cnt;
		item[1].point_index = pi; item[1].Angle_index = ai;
		pi = (int)h + 0 + 2; ai = 0;
		item[2].point_index = pi; item[2].Angle_index = ai;

		item2.data[0] = item[0];
		item2.data[1] = item[2];
		item2.data[2] = item[1];
		tri_index_info_list.push_back(item2);
		m_Progress.SetPos(++Progress_idx);
	}
	return;
}

void COpenGL_Test_MFCDlg::Create_Triangle_Normal()
{
	int tri_idx = -1;

	// �ﰢ�� ������ ������ŭ �ݺ�
	int tri_cnt = (int)tri_index_info_list.size();

	int Progress_idx = 0;
	m_Progress.SetRange(1, tri_cnt);

	for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
	{
		// �ﰢ�� �����͸� ��´�.
		tri_index_info tri = tri_index_info_list[tri_idx];

		// �ﰢ���� �̷�� �ִ°� ������ ��ġ�� ��´�.
		sub_tri_index_info v_loc0 = tri.data[0];
		sub_tri_index_info v_loc1 = tri.data[1];
		sub_tri_index_info v_loc2 = tri.data[2];

		// ���� ���� ��ġ�� ��´�.
		// ù��° ���� ù��° ���� ���Ѵ�.
		float x1, y1, z1;
		x1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x;
		y1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y;
		z1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z;
		// ù��° ���� �ι�° ���� ���Ѵ�.
		float x2, y2, z2;
		x2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x;
		y2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y;
		z2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z;
		// �ι�° ���� ù��° ���� ���Ѵ�.
		float x3, y3, z3;
		x3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x;
		y3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y;
		z3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z;

		glm::vec4 v1 = glm::vec4(x1, y1, z1, 1.0f);
		glm::vec4 v2 = glm::vec4(x2, y2, z2, 1.0f);
		glm::vec4 v3 = glm::vec4(x3, y3, z3, 1.0f);

		// ���û� ���⺤��1�� ���Ѵ� 
		glm::vec4 n_dir1 = v3 - v1;

		// ���û� ���⺤��2�� ���Ѵ�
		glm::vec4 n_dir2 = v3 - v2;

		// ���û� ������ ���Ѵ�
		glm::vec3 n_dir1_2 = glm::vec3(n_dir1.x, n_dir1.y, n_dir1.z);
		glm::vec3 n_dir2_2 = glm::vec3(n_dir2.x, n_dir2.y, n_dir2.z);
		glm::vec3 N = glm::cross(n_dir1_2, n_dir2_2);
		// ����ȭ �Ѵ�. 
		N = glm::normalize(N);

		tri_index_info_list[tri_idx].N = N;// *1.5f;
		m_Progress.SetPos(++Progress_idx);
	}
	return;
}

void COpenGL_Test_MFCDlg::Creaete_Vertex_Normal()
{
	int tri_cnt = (int)tri_index_info_list.size();
	sub_tri_index_info vertex;

	int Angle_index_cnt = 360;
	int Point_cnt = total_point;

	float total_cnt = (float)(Angle_index_cnt / Angle_index_Step) * (float)(Point_cnt / Point_Step);
	float current_cnt = 0.0f;

	int Progress_idx = 0;
	m_Progress.SetRange(1, total_cnt);

	for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
	{
		for (int i = 0; i < Point_cnt; i += Point_Step)
		{
			// ó���ϴ� ���� ��´�.
			vertex.point_index = i / Point_Step;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// �������� ������ �ʱ�ȭ
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// �������� �ʱ�ȭ.
			int N_cnt = 0;
			// �ﰢ�� ������ ������ŭ �ݺ�
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// �ﰢ�� �����͸� ��´�.
				tri_index_info tri = tri_index_info_list[tri_idx];

				//// �ﰢ�� ������ �� �ش� ���� ���Ե̳� ?
				//if (vertex.point_index == tri.data[0].point_index ||
				//	vertex.point_index == tri.data[1].point_index ||
				//	vertex.point_index == tri.data[2].point_index)
				//{ // ��
				//	if (vertex.Angle_index == tri.data[0].Angle_index ||
				//		vertex.Angle_index == tri.data[1].Angle_index ||
				//		vertex.Angle_index == tri.data[2].Angle_index)
				//	{ // ��
				//		// �ﰢ���� ������ �����Ѵ�.
				//		N += tri.N;
				//		// �������� 1 ����.
				//		N_cnt++;
				//	}
				//}

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // ��
					// �ﰢ���� ������ �����Ѵ�.
					N += tri.N;
					// �������� 1 ����.
					N_cnt++;
				}
			} // �ݺ�
			// �������� = �������� / ��������
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;
			m_Progress.SetPos(++Progress_idx);
		}
	} // �ݺ�

	// �� �ٴ�  �߽��� ���������� �����Ѵ�.
	data_Rendering_Data[floor_center_idx].vertex_Normal[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

	int Progresscnt = 1 + Angle_index_cnt / Angle_index_Step;
	Progress_idx = 0;
	for (int vi = floor_center_idx; vi <= (floor_center_idx + 1); vi++)
	{
		for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
		{
			// ó���ϴ� ���� ��´�.
			vertex.point_index = vi;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// �������� ������ �ʱ�ȭ
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// �������� �ʱ�ȭ.
			int N_cnt = 0;
			// �ﰢ�� ������ ������ŭ �ݺ�
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// �ﰢ�� �����͸� ��´�.
				tri_index_info tri = tri_index_info_list[tri_idx];

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // ��
					// �ﰢ���� ������ �����Ѵ�.
					N += tri.N;
					// �������� 1 ����.
					N_cnt++;
				}
			} // �ݺ�
			// �������� = �������� / ��������
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;

			m_Progress.SetPos(++Progress_idx);
			if (vi == floor_center_idx)
				break;
		} // �ݺ�
	}

	// �� �Ѳ� �߽��� ���������� �����Ѵ�.
	data_Rendering_Data[floor_center_idx+2].vertex_Normal[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

	Progresscnt = 1 + Angle_index_cnt / Angle_index_Step;
	Progress_idx = 0;
	for (int vi = floor_center_idx + 2; vi <= (floor_center_idx + 2 + 1); vi++)
	{
		for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
		{
			// ó���ϴ� ���� ��´�.
			vertex.point_index = vi;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// �������� ������ �ʱ�ȭ
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// �������� �ʱ�ȭ.
			int N_cnt = 0;
			// �ﰢ�� ������ ������ŭ �ݺ�
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// �ﰢ�� �����͸� ��´�.
				tri_index_info tri = tri_index_info_list[tri_idx];

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // ��
					// �ﰢ���� ������ �����Ѵ�.
					N += tri.N;
					// �������� 1 ����.
					N_cnt++;
				}
			} // �ݺ�
			// �������� = �������� / ��������
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;

			m_Progress.SetPos(++Progress_idx);
			if (vi == floor_center_idx + 2)
				break;
		} // �ݺ�
	}
	return;
}

void COpenGL_Test_MFCDlg::Read_File()
{
	char buffer[256];
	int line_num;

	Cover_Visible_Flag = false; // ó�� �Ѳ� ���´� �Ⱥ���.

	FILE* fr = 0;
	FILE* fw = 0;
	bool find_flag = true;

	// �ɽ� ���̸� ���� �ϳ�?
	fopen_s(&fr, "data//contours2_chache.txt", "rb");
	if (fr == 0)
	{ // �ƴϿ� 
		find_flag = false;
		fopen_s(&fr, "data//contours2.txt", "rt");
		fopen_s(&fw, "data//contours2_chache.txt", "wb");
	}
	if (fr)
	{
		// �ɽ� ���̸� ���� �ϳ� ?
		if (find_flag == false)
		{ // �ƴϿ� 
			memset(buffer, 0, sizeof(char)* 256);
			fgets(buffer, 255, fr);
			sscanf_s(buffer, "total point = %d", &total_point, sizeof(int));

			fgets(buffer, 255, fr); // ���� ó��.

			// ----- ������ ���Ͽ��� ��ǥ�� ��´�. ---------------------------
			// ������ �߽� ���� ��ǥ�� ���Ѵ� 
			int center_x = win_width / 2;
			data_Read_Data = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)* total_point);
			// �� �κ��� ���Ͽ��� �д°��̹Ƿ� �׻� 195���� ������ �о�� �Ѵ�.
			// for (int i = 0; i < total_point; i++)
			int i = 0;
			while (1)
			{
				// if (i == total_point - 1) i = total_point - 1;
				memset(buffer, 0, sizeof(char)* 256);

				fgets(buffer, 255, fr);
				if (strlen(buffer) <= 0)
					break;
				sscanf_s(buffer, "%d    %d %d", &line_num, &data_Read_Data[i].pos_x, &data_Read_Data[i].pos_y, sizeof(int), sizeof(int), sizeof(int));

				// �� ��ǥ�� ���� ���̸� ���Ѵ� .
				// ������ ��ǥ�� Ŭ���� ��� �������� ����.
				data_Read_Data[i].clip_pos_x = (2.0f * data_Read_Data[i].pos_x / win_width) - 1.0f;
				data_Read_Data[i].clip_pos_y = (2.0f - (2.0f * data_Read_Data[i].pos_y / win_height)) - 1.0f;
				data_Read_Data[i].depth = (center_x > data_Read_Data[i].pos_x) ? center_x - data_Read_Data[i].pos_x : data_Read_Data[i].pos_x - center_x;
				i++;
			}
			// ----------------------------------------------------------------

			// ���� ������ Ʋ����?
			if (i != total_point)
			{ // ��
				// �޸𸮸� �����Ѵ� .
				Coord_Info_Read_Data*data_Read_Data_copy = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)*i);
				memcpy(data_Read_Data_copy, data_Read_Data, sizeof(Coord_Info_Read_Data)* i);
				delete[] data_Read_Data;
				data_Read_Data = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)*i);
				memcpy(data_Read_Data, data_Read_Data_copy, sizeof(Coord_Info_Read_Data)* i);
				total_point = i;
			}

			// -------------- ������ ��ǥ ���� ��� ���. -------------------
			Compute_Computing_Matrix(win_width, win_height, camera_near, camera_far);
			// ----------------------------------------------------------------

			// ------------- �������� ��ǥ�� ��ȯ�Ѵ�. ------------------------
			float h = (float)total_point / (float)Point_Step;
			if (h - (int)h > 0.0f)
				h = (float)(int)h + 1.0f;

			int loading_cnt = (int)h + 2 + 2;

			data_Rendering_Data = (Coord_Info_Rendering_Data*)malloc(sizeof(Coord_Info_Rendering_Data)* (int)loading_cnt);
			int step = Point_Step;
			int cur_idx = 0;
			for (int i2 = 0; i2 < total_point; i2 += step)
			{
				data_Rendering_Data[i2 / step].clip_pos_x = data_Read_Data[i2].clip_pos_x;
				data_Rendering_Data[i2 / step].clip_pos_y = data_Read_Data[i2].clip_pos_y;
				data_Rendering_Data[i2 / step].depth = data_Read_Data[i2].depth;

				int Angle_index_Step = 10;
				int Angle_index_cnt = 360;
				for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
					Compute_LocalPos(i2 / step, Angle_index / Angle_index_Step);
				cur_idx = i2 / step;
			}
			// ----------------------------------------------------------------

			// ------------ �� �عٴ� �߽����� ���� ��ǥ�� ����Ѵ�. ----------
			floor_center_idx = cur_idx + 1;
			int tmp_floor_center_idx = floor_center_idx;

			// �� �عٴ� �߽��� Ŭ���� ��ǥ ���
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[tmp_floor_center_idx - 1].clip_pos_y;

			glm::vec4 tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// ������ ��İ��ؼ� ī�޶� �������� ����.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// ��ī�޶� ��� ���ؼ� �𵨰������� ����. (x, y��)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// ȸ���� ��ġ�� �����Ѵ�.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// --------- �� �� �ٴ� ������ ���� �Ѵ�. -------------------------
			int angle_cnt = 360 / Angle_index_Step;

			// �� �ȿ��� �f���� ���� �޴� �� ����Ʈ 
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[tmp_floor_center_idx - 2].pos_in_local[num_a];
			}
			// ----------------------------------------------------------------

			// ----------------- �Ѳ� �߽����� ����Ѵ�.  ---------------------
			// �� �عٴ� �߽��� Ŭ���� ��ǥ ���
			data_Rendering_Data[++tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[0].clip_pos_y;

			tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// ������ ��İ��ؼ� ī�޶� �������� ����.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// ��ī�޶� ��� ���ؼ� �𵨰������� ����. (x, y��)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// ȸ���� ��ġ�� �����Ѵ�.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// �Ѳ������� �����Ѵ�.
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[0].pos_in_local[num_a];
			}

			fwrite(&total_point, sizeof(int), 1, fw);
			fwrite(&h, sizeof(float), 1, fw);
			fwrite(data_Rendering_Data, sizeof(Coord_Info_Rendering_Data), (int)loading_cnt, fw);

			fclose(fw);
		}
		else
		{ // ��
			// ĳ�������� �д´�.
			fread(&total_point, sizeof(int), 1, fr);
			float h;
			fread(&h, sizeof(float), 1, fr);
			int loading_cnt = (int)h + 2 + 2;
			data_Rendering_Data = (Coord_Info_Rendering_Data*)malloc(sizeof(Coord_Info_Rendering_Data)* (int)loading_cnt);
			fread(data_Rendering_Data, sizeof(Coord_Info_Rendering_Data), (int)loading_cnt, fr);

			Compute_Computing_Matrix(win_width, win_height, camera_near, camera_far);
			int step = Point_Step;
			int cur_idx = 0;
			for (int i2 = 0; i2 < total_point; i2 += step)
			{
				if (i2 == total_point - 1)
					i2 = total_point - 1;
				int Angle_index_cnt = 360;
				for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
					Compute_LocalPos(i2 / step, Angle_index / Angle_index_Step);
				cur_idx = i2 / step;
			}
			// ------------ �� �عٴ� �߽����� ���� ��ǥ�� ����Ѵ�. ----------
			floor_center_idx = cur_idx + 1;
			int tmp_floor_center_idx = floor_center_idx;

			glm::vec4 tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// ������ ��İ��ؼ� ī�޶� �������� ����.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// ��ī�޶� ��� ���ؼ� �𵨰������� ����. (x, y��)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// ȸ���� ��ġ�� �����Ѵ�.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// --------- �� �� �ٴ� ������ ���� �Ѵ�. -------------------------
			int angle_cnt = 360 / Angle_index_Step;
			float h2 = (float)total_point / (float)Point_Step;
			if (h2 - (int)h2 > 0.0f)
				h2 = (float)(int)h2 + 1.0f;

			// �� �ȿ��� �f���� ���� �޴� �� ����Ʈ 
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[tmp_floor_center_idx - 2].pos_in_local[num_a];
			}
			// ----------------------------------------------------------------

			// ----------------- �Ѳ� �߽����� ����Ѵ�.  ---------------------
			// �� �عٴ� �߽��� Ŭ���� ��ǥ ���
			data_Rendering_Data[++tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[0].clip_pos_y;

			tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// ������ ��İ��ؼ� ī�޶� �������� ����.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// ��ī�޶� ��� ���ؼ� �𵨰������� ����. (x, y��)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// ȸ���� ��ġ�� �����Ѵ�.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// �Ѳ������� �����Ѵ�.
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[0].pos_in_local[num_a];
			}
		}
		fclose(fr);

		// ������ ����.
		Create_Triangle_Data();
		Create_Triangle_Normal();
		Creaete_Vertex_Normal();

		Compute_Rendering_Matrix(win_width, win_height, camera_near, camera_far);
	}
	m_OpenGL_View.Invalidate();
	return;
}
// ----------------------

void COpenGL_Test_MFCDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Read_File();;
	return;

	wchar_t temp_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, temp_path);
	wcscat_s(temp_path, sizeof(wchar_t)* MAX_PATH, L"\\data");

	CFileDialog ins_dlg(
		TRUE, NULL, 
		L"my_file.txt", 
		OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
		L"Modelling Files (*.txt)|*.txt||"
	);

	ins_dlg.m_ofn.nFilterIndex = 1;
	ins_dlg.m_ofn.lpstrInitialDir = temp_path;
	if (ins_dlg.DoModal() == IDOK) // ���ϼ����߳�?
	{ // ��
		// ���� �б�.
		Read_File();
	}
	return;
}


void COpenGL_Test_MFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (!(nFlags & MK_LBUTTON))
		return;

	CPoint pt;
	GetCursorPos(&pt);

	CRect rt;
	m_OpenGL_View.GetWindowRect(&rt);

	LONG X = pt.x - rt.left;
	LONG Y = pt.y - rt.top;

	if (X < 0 || Y < 0)
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	if (X >= (GLint)tbi.width || Y >= (GLint)tbi.height)
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	// ���� ��ǥ ���.
	tbi.X = (GLfloat)X;
	tbi.Y = (GLfloat)Y;

	// ���� ��ǥ��[2,2] ���簢���� ���� �Ѵ�.
	// w : 2 = X : ?
	tbi.X = tbi.X * 2.0f / tbi.width;
	tbi.Y = tbi.Y * 2.0f / tbi.height;
	tbi.Y = 2.0f - tbi.Y;

	// [-1, 1]�� �ٽ� �����Ѵ�.
	tbi.X = tbi.X - 1.0f;
	tbi.Y = tbi.Y - 1.0f;

	// if (abs(tbi.X) >= 1.0f || abs(tbi.Y) >= 1.0f)
	if (sqrt(tbi.X * tbi.X + tbi.Y * tbi.Y) > 1.0f)
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	// �������� 1�� ���������� ��ǥ�� �����.
	tbi.pos.x = tbi.X;
	tbi.pos.y = tbi.Y;
	tbi.pos.z = 1.0f - tbi.pos.x * tbi.pos.x - tbi.pos.y * tbi.pos.y;
	tbi.pos.z = (abs(tbi.pos.z) > 0.0001f) ? sqrt(tbi.pos.z) : 0.0f;

	if (glm::isnan(tbi.prev_pos.z))
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	if (glm::isnan(tbi.pos.z))
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	// �ι��⺤�� �� �����Ͽ� ȸ������ �����.
	glm::vec3 axis = glm::cross(tbi.prev_pos, tbi.pos);
	// axis = glm::vec3(0.0f, 0.0f, 0.0f);
	if (glm::length2(axis) < 0.0001f * 0.0001f) // ���� 0 ���ͷ� ���ǳ�?
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	axis = glm::normalize(axis);

	// �ι��⺤�� �� �����Ͽ� �ڻ��ΰ��� ���Ѵ�.
	GLfloat cos_term = glm::dot(tbi.prev_pos, tbi.pos);

	// ���ڻ��� ����Ͽ� ���� Ÿ�� ������ �˾Ƴ���.
	GLfloat rad_angle = glm::acos(cos_term);
	// ���� Ÿ�� ������ 60�й����� ����Ѵ�.
	GLfloat angle = rad_angle;

	// ȸ������� ����Ѵ�.
	glm::mat4 axis_matR = glm::rotate(glm::mat4(), angle, axis);

	// ��ü ȸ�� ��Ŀ� ��������Ѵ�.
	Rendering_mat_info.model_Rotate_mat = axis_matR * Rendering_mat_info.model_Rotate_mat;

	// ������ǥ <--- ������ǥ
	tbi.prev_pos = tbi.pos;

	m_OpenGL_View.Invalidate(); // �ٽ� �׸���.
	
	CDialogEx::OnMouseMove(nFlags, point);
	return;
}


void COpenGL_Test_MFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CPoint pt;
	GetCursorPos(&pt);

	CRect rt;
	m_OpenGL_View.GetWindowRect(&rt);

	LONG X = pt.x - rt.left;
	LONG Y = pt.y - rt.top;

	if (X < 0 || Y < 0)
	{
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}

	if (X >= (GLint)tbi.width || Y >= (GLint)tbi.height)
	{
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}

	// ���� ��ǥ ���.
	tbi.X = (GLfloat)X;
	tbi.Y = (GLfloat)Y;

	// ���� ��ǥ <--- ���� ��ǥ
	tbi.prev_X = (GLfloat)X;
	tbi.prev_Y = (GLfloat)Y;

	// ���� ��ǥ��[2,2] ���簢���� ���� �Ѵ�.
	// w : 2 = X : ?
	tbi.prev_X = tbi.prev_X * 2.0f / tbi.width;
	tbi.prev_Y = tbi.prev_Y * 2.0f / tbi.height;
	tbi.prev_Y = 2.0f - tbi.prev_Y;

	// [-1, 1]�� �ٽ� �����Ѵ�.
	tbi.prev_X = tbi.prev_X - 1.0f;
	tbi.prev_Y = tbi.prev_Y - 1.0f;

	if (sqrt(tbi.prev_X * tbi.prev_X + tbi.prev_Y * tbi.prev_Y) > 1.0f)
	{
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}

	// �������� 1�� ���������� ��ǥ�� �����.
	tbi.prev_pos.x = tbi.prev_X;
	tbi.prev_pos.y = tbi.prev_Y;
	tbi.prev_pos.z = 1.0f - tbi.prev_pos.x * tbi.prev_pos.x - tbi.prev_pos.y * tbi.prev_pos.y;
	tbi.prev_pos.z = (abs(tbi.prev_pos.z) > 0.0001f) ? sqrt(tbi.prev_pos.z) : 0.0f;

	if (glm::isnan(tbi.prev_pos.z))
	{
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
	return;
}


void COpenGL_Test_MFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	tbi.prev_pos = tbi.pos;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void COpenGL_Test_MFCDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Cover_Visible_Flag = true;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Cover_Visible_Flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton4() // X+
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.x += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton5() // X-
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.x -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton6() // Y+
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.y += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton7() // Y-
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.y -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton8() // Z+
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.z += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton9() // Z-
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	light_pos.z -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (data_Read_Data) free(data_Read_Data);
	if (data_Rendering_Data) free(data_Rendering_Data);
}


void COpenGL_Test_MFCDlg::OnBnClickedButton10()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	vertex_mode_flag = true;
	wireframe_mode_flag = false;
	normal_mode_flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton11()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	vertex_mode_flag = false;
	wireframe_mode_flag = !wireframe_mode_flag;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton12()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	vertex_mode_flag = false;
	normal_mode_flag = !normal_mode_flag;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton13()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	vertex_mode_flag = false;
	wireframe_mode_flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton14()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	fov -= 0.01f;
	Compute_Rendering_Matrix(win_width, win_height, camera_near, camera_far);
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton15()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	fov += 0.01f;
	Compute_Rendering_Matrix(win_width, win_height, camera_near, camera_far);
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnRadio1()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CButton*btn1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton*btn2 = (CButton*)GetDlgItem(IDC_RADIO2);
	if (btn1 && btn2)
	{
		btn1->SetCheck(1);
		btn2->SetCheck(0);
	}
	flat_shading_mode_flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnRadio2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CButton*btn1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton*btn2 = (CButton*)GetDlgItem(IDC_RADIO2);
	if (btn1 && btn2)
	{
		btn1->SetCheck(0);
		btn2->SetCheck(1);
	}
	flat_shading_mode_flag = true;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton16()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Back_Face_flag = true;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton17()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Back_Face_flag = false;
	m_OpenGL_View.Invalidate();
}
