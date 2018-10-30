
// OpenGL_Test_MFCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "OpenGL_Test_MFC.h"
#include "OpenGL_Test_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// COpenGL_Test_MFCDlg 대화 상자



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


// COpenGL_Test_MFCDlg 메시지 처리기

BOOL COpenGL_Test_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	total_point = -1; // buffer에 문자열을 구성하기 위해 맨 뒤에는 항상 NULL문자를 위한 자리를 만들어준다.
	floor_center_idx = -1;

	// 윈도우 가로,세로 길이를 정한다.
	RECT rt;
	GetClientRect(&rt);
	GLfloat cx = (GLfloat)rt.right;
	GLfloat cy = (GLfloat)rt.bottom;
	win_width = (int)cx;
	win_height = (int)cy;

	// 윈도우 near, far 결정한다.
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COpenGL_Test_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		m_OpenGL_View.Invalidate();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR COpenGL_Test_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ----------------------
void COpenGL_Test_MFCDlg::Compute_Computing_Matrix(int win_width, int win_height, float camera_near, float camera_far)
{
	Computing_mat_info.cam_pos = glm::vec3(0.0f, 0.0f, 5.5f); // 카메라 위치
	Computing_mat_info.cam_view_dir = glm::vec3(0.0f, 0.0f, -1.0f); // 카메라 보는 방향.
	Computing_mat_info.dist = 2.0f; // 1.0f;

	// 컵의 중심위치 구하기.
	glm::vec3 cup_pos = Computing_mat_info.cam_pos + Computing_mat_info.cam_view_dir * Computing_mat_info.dist;

	// 모델 행렬 계산.
	Computing_mat_info.model_mat = glm::translate(glm::mat4(), cup_pos);

	// 뷰 행렬 계산.
	glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	Computing_mat_info.view_mat = glm::lookAt(Computing_mat_info.cam_pos, cup_pos, UP);

	// 투영 행렬 계산.
	FLOAT window_aspect = (FLOAT)win_width / (FLOAT)win_height;
	Computing_mat_info.proj_mat = glm::perspective(45.0f, window_aspect, camera_near, camera_far);

	return;
}

void COpenGL_Test_MFCDlg::Compute_Rendering_Matrix(int win_width, int win_height, float camera_near, float camera_far)
{
	Rendering_mat_info.cam_pos = Computing_mat_info.cam_pos;// glm::vec3(0.0f, 0.0f, 5.5f);  // glm::vec3(0.0f, 0.7f, 3.1f);
	Rendering_mat_info.cam_view_dir = Computing_mat_info.cam_view_dir; //  glm::vec3(0.0f, 0.0f, -1.0f);
	Rendering_mat_info.dist = 2.0f;

	// 컵의 중심위치 구하기.
	glm::vec3 cup_pos = Rendering_mat_info.cam_pos + Rendering_mat_info.cam_view_dir * Rendering_mat_info.dist;

	// 모델 행렬 계산.
	Rendering_mat_info.model_mat = glm::translate(glm::mat4(), cup_pos);

	// 뷰 행렬 계산.
	glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
	Rendering_mat_info.view_mat = glm::lookAt(Rendering_mat_info.cam_pos, cup_pos, UP);

	// 투영 행렬 계산.
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

	// 역투영 행렬곱해서 카메라 공간으로 변형.
	tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
	data_Rendering_Data[idx].pos_in_view[angle_index] = tmp_p;

	// 역카메라 행렬 곱해서 모델공간으로 변형. (x, y만)
	tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
	data_Rendering_Data[idx].pos_in_model[angle_index] = tmp_p;

	tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
	// -------------- 여기까지는 0도일때의 위치. -------------------

	// ------------ 누적된 각도에 대한 위치를 계산하자 -------------
	// 1. 누적된 각도
	FLOAT Angle = (FLOAT)angle_index * (FLOAT)Angle_index_Step; // 회전할 각도.
	FLOAT Rad_Angle = glm::radians(Angle); // 회전할 각도의 호도법 

	// 2. 누적된 각도에 대한 회전 쿼터니언 계산.
	glm::vec3 cam_up_dir = glm::vec3(
		Computing_mat_info.view_mat[0].y,
		Computing_mat_info.view_mat[1].y,
		Computing_mat_info.view_mat[2].y
		);
	glm::quat Q = glm::angleAxis(Rad_Angle / 2.0f, cam_up_dir);

	// 역쿼터니언 계산.
	glm::quat Inverse_Q = glm::inverse(Q);

	// 3. 쿼터니언을 곱해서 회전된 위치를 구한다.
	tmp_p = Q * tmp_p * Inverse_Q;
	// -------------------------------------------------------------

	// 회전된 위치를 저장한다.
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

	// 바닥 면 계산.
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

	// 뚜껑 면 계산.
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

	// 삼각형 데이터 갯수만큼 반복
	int tri_cnt = (int)tri_index_info_list.size();

	int Progress_idx = 0;
	m_Progress.SetRange(1, tri_cnt);

	for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
	{
		// 삼각형 데이터를 얻는다.
		tri_index_info tri = tri_index_info_list[tri_idx];

		// 삼각형을 이루고 있는각 정점의 위치를 얻는다.
		sub_tri_index_info v_loc0 = tri.data[0];
		sub_tri_index_info v_loc1 = tri.data[1];
		sub_tri_index_info v_loc2 = tri.data[2];

		// 실제 정점 위치를 얻는다.
		// 첫번째 선의 첫번째 점을 정한다.
		float x1, y1, z1;
		x1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x;
		y1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y;
		z1 = data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z;
		// 첫번째 선의 두번째 점을 정한다.
		float x2, y2, z2;
		x2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x;
		y2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y;
		z2 = data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z;
		// 두번째 선의 첫번째 점을 정한다.
		float x3, y3, z3;
		x3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x;
		y3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y;
		z3 = data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z;

		glm::vec4 v1 = glm::vec4(x1, y1, z1, 1.0f);
		glm::vec4 v2 = glm::vec4(x2, y2, z2, 1.0f);
		glm::vec4 v3 = glm::vec4(x3, y3, z3, 1.0f);

		// 로컬상 방향벡터1를 구한다 
		glm::vec4 n_dir1 = v3 - v1;

		// 로컬상 방향벡터2를 구한다
		glm::vec4 n_dir2 = v3 - v2;

		// 로컬상 외적를 구한다
		glm::vec3 n_dir1_2 = glm::vec3(n_dir1.x, n_dir1.y, n_dir1.z);
		glm::vec3 n_dir2_2 = glm::vec3(n_dir2.x, n_dir2.y, n_dir2.z);
		glm::vec3 N = glm::cross(n_dir1_2, n_dir2_2);
		// 정규화 한다. 
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
			// 처리하는 점을 얻는다.
			vertex.point_index = i / Point_Step;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// 누적법선 데이터 초기화
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// 법선갯수 초기화.
			int N_cnt = 0;
			// 삼각형 데이터 갯수만큼 반복
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// 삼각형 데이터를 얻는다.
				tri_index_info tri = tri_index_info_list[tri_idx];

				//// 삼각형 데이터 에 해당 점이 포함됫냐 ?
				//if (vertex.point_index == tri.data[0].point_index ||
				//	vertex.point_index == tri.data[1].point_index ||
				//	vertex.point_index == tri.data[2].point_index)
				//{ // 예
				//	if (vertex.Angle_index == tri.data[0].Angle_index ||
				//		vertex.Angle_index == tri.data[1].Angle_index ||
				//		vertex.Angle_index == tri.data[2].Angle_index)
				//	{ // 예
				//		// 삼각형의 법선을 누적한다.
				//		N += tri.N;
				//		// 법선갯수 1 증가.
				//		N_cnt++;
				//	}
				//}

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // 예
					// 삼각형의 법선을 누적한다.
					N += tri.N;
					// 법선갯수 1 증가.
					N_cnt++;
				}
			} // 반복
			// 정점법선 = 누적법선 / 법선갯수
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;
			m_Progress.SetPos(++Progress_idx);
		}
	} // 반복

	// 컵 바닥  중심점 법선정보를 설정한다.
	data_Rendering_Data[floor_center_idx].vertex_Normal[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

	int Progresscnt = 1 + Angle_index_cnt / Angle_index_Step;
	Progress_idx = 0;
	for (int vi = floor_center_idx; vi <= (floor_center_idx + 1); vi++)
	{
		for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
		{
			// 처리하는 점을 얻는다.
			vertex.point_index = vi;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// 누적법선 데이터 초기화
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// 법선갯수 초기화.
			int N_cnt = 0;
			// 삼각형 데이터 갯수만큼 반복
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// 삼각형 데이터를 얻는다.
				tri_index_info tri = tri_index_info_list[tri_idx];

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // 예
					// 삼각형의 법선을 누적한다.
					N += tri.N;
					// 법선갯수 1 증가.
					N_cnt++;
				}
			} // 반복
			// 정점법선 = 누적법선 / 법선갯수
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;

			m_Progress.SetPos(++Progress_idx);
			if (vi == floor_center_idx)
				break;
		} // 반복
	}

	// 컵 뚜껑 중심점 법선정보를 설정한다.
	data_Rendering_Data[floor_center_idx+2].vertex_Normal[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	// aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

	Progresscnt = 1 + Angle_index_cnt / Angle_index_Step;
	Progress_idx = 0;
	for (int vi = floor_center_idx + 2; vi <= (floor_center_idx + 2 + 1); vi++)
	{
		for (int Angle_index = 0; Angle_index < Angle_index_cnt; Angle_index += Angle_index_Step)
		{
			// 처리하는 점을 얻는다.
			vertex.point_index = vi;
			vertex.Angle_index = Angle_index / Angle_index_Step;

			// 누적법선 데이터 초기화
			glm::vec3 N = glm::vec3(0.0f, 0.0f, 0.0f);
			// 법선갯수 초기화.
			int N_cnt = 0;
			// 삼각형 데이터 갯수만큼 반복
			for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
			{
				// 삼각형 데이터를 얻는다.
				tri_index_info tri = tri_index_info_list[tri_idx];

				if ((vertex.point_index == tri.data[0].point_index && vertex.Angle_index == tri.data[0].Angle_index) || (vertex.point_index == tri.data[1].point_index && vertex.Angle_index == tri.data[1].Angle_index) || (vertex.point_index == tri.data[2].point_index && vertex.Angle_index == tri.data[2].Angle_index))
				{ // 예
					// 삼각형의 법선을 누적한다.
					N += tri.N;
					// 법선갯수 1 증가.
					N_cnt++;
				}
			} // 반복
			// 정점법선 = 누적법선 / 법선갯수
			data_Rendering_Data[vertex.point_index].vertex_Normal[vertex.Angle_index] = N / (float)N_cnt;

			m_Progress.SetPos(++Progress_idx);
			if (vi == floor_center_idx + 2)
				break;
		} // 반복
	}
	return;
}

void COpenGL_Test_MFCDlg::Read_File()
{
	char buffer[256];
	int line_num;

	Cover_Visible_Flag = false; // 처음 뚜껑 상태는 안보임.

	FILE* fr = 0;
	FILE* fw = 0;
	bool find_flag = true;

	// 케쉬 파이링 존재 하냐?
	fopen_s(&fr, "data//contours2_chache.txt", "rb");
	if (fr == 0)
	{ // 아니오 
		find_flag = false;
		fopen_s(&fr, "data//contours2.txt", "rt");
		fopen_s(&fw, "data//contours2_chache.txt", "wb");
	}
	if (fr)
	{
		// 케쉬 파이링 존재 하냐 ?
		if (find_flag == false)
		{ // 아니오 
			memset(buffer, 0, sizeof(char)* 256);
			fgets(buffer, 255, fr);
			sscanf_s(buffer, "total point = %d", &total_point, sizeof(int));

			fgets(buffer, 255, fr); // 빈줄 처리.

			// ----- 데이터 파일에서 좌표를 얻는다. ---------------------------
			// 윈도우 중심 엑스 좌표를 구한다 
			int center_x = win_width / 2;
			data_Read_Data = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)* total_point);
			// 이 부분은 파일에서 읽는것이므로 항상 195개로 무조건 읽어야 한다.
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

				// 각 좌표에 대한 깊이를 구한다 .
				// 데이터 좌표를 클리핑 행렬 공간으로 변형.
				data_Read_Data[i].clip_pos_x = (2.0f * data_Read_Data[i].pos_x / win_width) - 1.0f;
				data_Read_Data[i].clip_pos_y = (2.0f - (2.0f * data_Read_Data[i].pos_y / win_height)) - 1.0f;
				data_Read_Data[i].depth = (center_x > data_Read_Data[i].pos_x) ? center_x - data_Read_Data[i].pos_x : data_Read_Data[i].pos_x - center_x;
				i++;
			}
			// ----------------------------------------------------------------

			// 서로 갯수가 틀리냐?
			if (i != total_point)
			{ // 예
				// 메모리를 수정한다 .
				Coord_Info_Read_Data*data_Read_Data_copy = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)*i);
				memcpy(data_Read_Data_copy, data_Read_Data, sizeof(Coord_Info_Read_Data)* i);
				delete[] data_Read_Data;
				data_Read_Data = (Coord_Info_Read_Data*)malloc(sizeof(Coord_Info_Read_Data)*i);
				memcpy(data_Read_Data, data_Read_Data_copy, sizeof(Coord_Info_Read_Data)* i);
				total_point = i;
			}

			// -------------- 렌더링 좌표 계산용 행렬 계산. -------------------
			Compute_Computing_Matrix(win_width, win_height, camera_near, camera_far);
			// ----------------------------------------------------------------

			// ------------- 렌더링용 좌표로 변환한다. ------------------------
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

			// ------------ 컵 밑바닥 중심점의 로컬 좌표를 계산한다. ----------
			floor_center_idx = cur_idx + 1;
			int tmp_floor_center_idx = floor_center_idx;

			// 컵 밑바닥 중심점 클리핑 좌표 계산
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[tmp_floor_center_idx - 1].clip_pos_y;

			glm::vec4 tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// 역투영 행렬곱해서 카메라 공간으로 변형.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// 역카메라 행렬 곱해서 모델공간으로 변형. (x, y만)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// 회전된 위치를 저장한다.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// --------- 컵 밑 바닥 정점을 복사 한다. -------------------------
			int angle_cnt = 360 / Angle_index_Step;

			// 컵 안에서 봣을대 빛을 받는 면 리스트 
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[tmp_floor_center_idx - 2].pos_in_local[num_a];
			}
			// ----------------------------------------------------------------

			// ----------------- 뚜껑 중심점을 계산한다.  ---------------------
			// 컵 밑바닥 중심점 클리핑 좌표 계산
			data_Rendering_Data[++tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[0].clip_pos_y;

			tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// 역투영 행렬곱해서 카메라 공간으로 변형.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// 역카메라 행렬 곱해서 모델공간으로 변형. (x, y만)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// 회전된 위치를 저장한다.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// 뚜껑정점을 복사한다.
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
		{ // 예
			// 캐쉬파일을 읽는다.
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
			// ------------ 컵 밑바닥 중심점의 로컬 좌표를 계산한다. ----------
			floor_center_idx = cur_idx + 1;
			int tmp_floor_center_idx = floor_center_idx;

			glm::vec4 tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// 역투영 행렬곱해서 카메라 공간으로 변형.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// 역카메라 행렬 곱해서 모델공간으로 변형. (x, y만)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// 회전된 위치를 저장한다.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// --------- 컵 밑 바닥 정점을 복사 한다. -------------------------
			int angle_cnt = 360 / Angle_index_Step;
			float h2 = (float)total_point / (float)Point_Step;
			if (h2 - (int)h2 > 0.0f)
				h2 = (float)(int)h2 + 1.0f;

			// 컵 안에서 봣을대 빛을 받는 면 리스트 
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[tmp_floor_center_idx - 2].pos_in_local[num_a];
			}
			// ----------------------------------------------------------------

			// ----------------- 뚜껑 중심점을 계산한다.  ---------------------
			// 컵 밑바닥 중심점 클리핑 좌표 계산
			data_Rendering_Data[++tmp_floor_center_idx].clip_pos_x = 0.0f;
			data_Rendering_Data[tmp_floor_center_idx].clip_pos_y = data_Rendering_Data[0].clip_pos_y;

			tmp_p = glm::vec4(
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_x,
				data_Rendering_Data[tmp_floor_center_idx].clip_pos_y,
				0.0f,
				1.0f
				);

			// 역투영 행렬곱해서 카메라 공간으로 변형.
			tmp_p = Computing_mat_info.inv_proj_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_view[0] = tmp_p;

			// 역카메라 행렬 곱해서 모델공간으로 변형. (x, y만)
			tmp_p = Computing_mat_info.inv_view_mat * tmp_p;
			data_Rendering_Data[tmp_floor_center_idx].pos_in_model[0] = tmp_p;

			tmp_p = Computing_mat_info.inv_model_mat * tmp_p;
			// 회전된 위치를 저장한다.
			data_Rendering_Data[tmp_floor_center_idx++].pos_in_local[0] = tmp_p;
			// ----------------------------------------------------------------

			// 뚜껑정점을 복사한다.
			for (int num_a = 0; num_a < angle_cnt; num_a++)
			{
				data_Rendering_Data[tmp_floor_center_idx].pos_in_local[num_a] = data_Rendering_Data[0].pos_in_local[num_a];
			}
		}
		fclose(fr);

		// 폴리곤 구성.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	if (ins_dlg.DoModal() == IDOK) // 파일선택했냐?
	{ // 예
		// 파일 읽기.
		Read_File();
	}
	return;
}


void COpenGL_Test_MFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// 현재 좌표 얻기.
	tbi.X = (GLfloat)X;
	tbi.Y = (GLfloat)Y;

	// 현재 좌표를[2,2] 정사각형에 맵핑 한다.
	// w : 2 = X : ?
	tbi.X = tbi.X * 2.0f / tbi.width;
	tbi.Y = tbi.Y * 2.0f / tbi.height;
	tbi.Y = 2.0f - tbi.Y;

	// [-1, 1]로 다시 맵핑한다.
	tbi.X = tbi.X - 1.0f;
	tbi.Y = tbi.Y - 1.0f;

	// if (abs(tbi.X) >= 1.0f || abs(tbi.Y) >= 1.0f)
	if (sqrt(tbi.X * tbi.X + tbi.Y * tbi.Y) > 1.0f)
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	// 반지름이 1인 단위구상의 좌표로 만든다.
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

	// 두방향벡터 를 외적하여 회전축을 만든다.
	glm::vec3 axis = glm::cross(tbi.prev_pos, tbi.pos);
	// axis = glm::vec3(0.0f, 0.0f, 0.0f);
	if (glm::length2(axis) < 0.0001f * 0.0001f) // 축이 0 벡터로 계산되냐?
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}

	axis = glm::normalize(axis);

	// 두방향벡터 를 내적하여 코사인값을 구한다.
	GLfloat cos_term = glm::dot(tbi.prev_pos, tbi.pos);

	// 역코사인 계산하여 라디안 타입 각도를 알아낸다.
	GLfloat rad_angle = glm::acos(cos_term);
	// 라디안 타입 각도를 60분법으로 계산한다.
	GLfloat angle = rad_angle;

	// 회전행렬을 계산한다.
	glm::mat4 axis_matR = glm::rotate(glm::mat4(), angle, axis);

	// 물체 회전 행렬에 누적계산한다.
	Rendering_mat_info.model_Rotate_mat = axis_matR * Rendering_mat_info.model_Rotate_mat;

	// 이전좌표 <--- 현재좌표
	tbi.prev_pos = tbi.pos;

	m_OpenGL_View.Invalidate(); // 다시 그린다.
	
	CDialogEx::OnMouseMove(nFlags, point);
	return;
}


void COpenGL_Test_MFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// 현재 좌표 얻기.
	tbi.X = (GLfloat)X;
	tbi.Y = (GLfloat)Y;

	// 이전 좌표 <--- 현재 좌표
	tbi.prev_X = (GLfloat)X;
	tbi.prev_Y = (GLfloat)Y;

	// 현재 좌표를[2,2] 정사각형에 맵핑 한다.
	// w : 2 = X : ?
	tbi.prev_X = tbi.prev_X * 2.0f / tbi.width;
	tbi.prev_Y = tbi.prev_Y * 2.0f / tbi.height;
	tbi.prev_Y = 2.0f - tbi.prev_Y;

	// [-1, 1]로 다시 맵핑한다.
	tbi.prev_X = tbi.prev_X - 1.0f;
	tbi.prev_Y = tbi.prev_Y - 1.0f;

	if (sqrt(tbi.prev_X * tbi.prev_X + tbi.prev_Y * tbi.prev_Y) > 1.0f)
	{
		CDialogEx::OnLButtonDown(nFlags, point);
		return;
	}

	// 반지름이 1인 단위구상의 좌표로 만든다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	tbi.prev_pos = tbi.pos;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void COpenGL_Test_MFCDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Cover_Visible_Flag = true;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Cover_Visible_Flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton4() // X+
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.x += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton5() // X-
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.x -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton6() // Y+
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.y += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton7() // Y-
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.y -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton8() // Z+
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.z += 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton9() // Z-
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	light_pos.z -= 0.01f;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (data_Read_Data) free(data_Read_Data);
	if (data_Rendering_Data) free(data_Rendering_Data);
}


void COpenGL_Test_MFCDlg::OnBnClickedButton10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vertex_mode_flag = true;
	wireframe_mode_flag = false;
	normal_mode_flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vertex_mode_flag = false;
	wireframe_mode_flag = !wireframe_mode_flag;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vertex_mode_flag = false;
	normal_mode_flag = !normal_mode_flag;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	vertex_mode_flag = false;
	wireframe_mode_flag = false;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton14()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	fov -= 0.01f;
	Compute_Rendering_Matrix(win_width, win_height, camera_near, camera_far);
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton15()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	fov += 0.01f;
	Compute_Rendering_Matrix(win_width, win_height, camera_near, camera_far);
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnRadio1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Back_Face_flag = true;
	m_OpenGL_View.Invalidate();
}


void COpenGL_Test_MFCDlg::OnBnClickedButton17()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Back_Face_flag = false;
	m_OpenGL_View.Invalidate();
}
