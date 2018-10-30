#include "stdafx.h"
#include "OpenGL_Static.h"
#include "OpenGL_Test_MFCDlg.h"

COpenGL_Static::COpenGL_Static()
{
}


COpenGL_Static::~COpenGL_Static()
{
}
BEGIN_MESSAGE_MAP(COpenGL_Static, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void COpenGL_Static::Draw_Light_Sphere(glm::vec3 pos)
{
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glm::mat4 sphere_model_mat;
	sphere_model_mat = glm::translate(glm::mat4(), pos);
	sphere_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.view_mat * sphere_model_mat * ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat;

	glMultMatrixf(glm::value_ptr(sphere_model_mat));

	glColor3f(1.0f, 0.0f, 0.0f);
	gluSphere(((COpenGL_Test_MFCDlg*)GetParent())->sphere, 1.0f / 60.0f, 50, 10);  // sphere 그리기 
	glPopMatrix();
}

void COpenGL_Static::EndScene()
{
	glFlush();
	return;
}

void COpenGL_Static::renderScene()
{
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag != true)
	{
		glEnable(GL_CULL_FACE);		// 뒷면에 대해서는 계산하지 말라
		glFrontFace(GL_CCW);		// 시계방향이 앞면
		glCullFace(GL_NONE);
	}
	else
	{
		glDisable(GL_CULL_FACE);		// 뒷면에 대해서는 계산하지 말라
		// glFrontFace(GL_CCW);		// 시계방향이 앞면
		// glCullFace(GL_NONE);
	}

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RECT rt;
	GetClientRect(&rt);
	GLfloat cx = (GLfloat)rt.right;
	GLfloat cy = (GLfloat)rt.bottom;

	glViewport(0, 0, cx, cy);

	// 모델뷰 행렬 계산.
	glm::mat4 model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.view_mat * model_view_mat;

	// 오픈지엘에 모델뷰 행렬 셋팅.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(model_view_mat));

	// 오픈지엘에 투영 행렬 셋팅.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.proj_mat));

	if (((COpenGL_Test_MFCDlg*)GetParent())->vertex_mode_flag == true)
	{
		int tmp_angle_cnt = 360 / ((COpenGL_Test_MFCDlg*)GetParent())->Angle_index_Step;
		glPushMatrix();

		glColor3f(1.f, 1.f, 0.f);
		glDisable(GL_LIGHTING);		// 빛을 사용한다.
		glDisable(GL_LIGHT0);		// 0번 빛을 사용한다.
		glDisable(GL_COLOR_MATERIAL);

		// 삼각형 데이터 갯수만큼 반복
		int tri_cnt = (int)((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list.size();
		if (tri_cnt <= 0)
		{
			glPopMatrix();
			glFlush();
			return;
		}
		for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
		{
			if (((COpenGL_Test_MFCDlg*)GetParent())->Cover_Visible_Flag != true)
			{
				if (tri_idx == tri_cnt - tmp_angle_cnt)
					break;
			}

			// 삼각형 데이터를 얻는다.
			tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

			// 삼각형을 이루고 있는각 정점의 위치를 얻는다.
			sub_tri_index_info v_loc0 = tri.data[0];
			sub_tri_index_info v_loc1 = tri.data[1];
			sub_tri_index_info v_loc2 = tri.data[2];

			// ------
			glBegin(GL_POINTS);
			glVertex3f(
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z
				);

			glVertex3f(
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z
				);

			glVertex3f(
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y,
				((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z
				);
			glEnd();
			// ------
		}
		glPopMatrix();

		glFlush();
		return;
	}

	if (((COpenGL_Test_MFCDlg*)GetParent())->flat_shading_mode_flag == true)
	{ // 예
		glShadeModel(GL_FLAT);
	}
	else
	{ // 예
		glShadeModel(GL_SMOOTH);
	}
	// ------------------------------------
	int tmp_angle_cnt = 360 / ((COpenGL_Test_MFCDlg*)GetParent())->Angle_index_Step;
	glPushMatrix();

	if (((COpenGL_Test_MFCDlg*)GetParent())->wireframe_mode_flag == true)
	{
		glPolygonMode(GL_FRONT, GL_LINE); // 이거하면 와이어프레임
		glPolygonMode(GL_BACK, GL_LINE); // 이거하면 와이어프레임
		glDisable(GL_LIGHTING);		// 빛을 사용한다.
		glDisable(GL_LIGHT0);		// 0번 빛을 사용한다.
		glDisable(GL_COLOR_MATERIAL);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL); // 이거하면 솔리드
		glPolygonMode(GL_BACK, GL_FILL); // 이거하면 솔리드
		glEnable(GL_LIGHTING);		// 빛을 사용한다.
		glEnable(GL_LIGHT0);		// 0번 빛을 사용한다.
		glEnable(GL_COLOR_MATERIAL);
	}
	glColor3f(1.f, 1.f, 1.f);

	// 삼각형 데이터 갯수만큼 반복
	int tri_cnt = (int)((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list.size();
	if (tri_cnt <= 0)
	{
		glPopMatrix();
		glFlush();
		return;
	}
	for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
	{
		if (((COpenGL_Test_MFCDlg*)GetParent())->Cover_Visible_Flag != true)
		{
			if (tri_idx == tri_cnt - tmp_angle_cnt)
				break;
		}

		// 삼각형 데이터를 얻는다.
		tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

		// 삼각형을 이루고 있는각 정점의 위치를 얻는다.
		sub_tri_index_info v_loc0 = tri.data[0];
		sub_tri_index_info v_loc1 = tri.data[1];
		sub_tri_index_info v_loc2 = tri.data[2];

		// ------
		glBegin(GL_POLYGON);
		glNormal3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].z
			);
		glVertex3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z
			);

		glNormal3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].z
			);
		glVertex3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z
			);

		glNormal3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].z
			);
		glVertex3f(
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y,
			((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z
			);
		glEnd();
		// ------
	}
	// glPopMatrix();
	// ------------------------------------

	if (((COpenGL_Test_MFCDlg*)GetParent())->normal_mode_flag == true)
	{
		int tmp_angle_cnt = 360 / ((COpenGL_Test_MFCDlg*)GetParent())->Angle_index_Step;
		// glPushMatrix();

		glColor3f(1.f, 1.f, 0.f);
		glDisable(GL_LIGHTING);		// 빛을 사용한다.
		glDisable(GL_LIGHT0);		// 0번 빛을 사용한다.
		glDisable(GL_COLOR_MATERIAL);

		// 삼각형 데이터 갯수만큼 반복
		int tri_cnt = (int)((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list.size();
		if (tri_cnt <= 0)
		{
			glPopMatrix();
			glFlush();
			return;
		}
		for (int tri_idx = 0; tri_idx < tri_cnt; tri_idx++)
		{
			if (((COpenGL_Test_MFCDlg*)GetParent())->Cover_Visible_Flag != true)
			{
				if (tri_idx == tri_cnt - tmp_angle_cnt)
					break;
			}

			// 삼각형 데이터를 얻는다.
			tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

			// 삼각형을 이루고 있는각 정점의 위치를 얻는다.
			sub_tri_index_info v_loc0 = tri.data[0];
			sub_tri_index_info v_loc1 = tri.data[1];
			sub_tri_index_info v_loc2 = tri.data[2];

			// ------
			GLfloat normal_len = 0.125f / 4.0f;

			// 플랫 쉐이딩이냐?
			if (((COpenGL_Test_MFCDlg*)GetParent())->flat_shading_mode_flag == true)
			{ // 예
				// 세 정점을 구한다 
				glm::vec3 V_1 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z
					);
				glm::vec3 V_2 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z
					);
				glm::vec3 V_3 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z
					);
				
				// 삼각형의 무게중심을 구한다.
				glm::vec3 vertex = (V_1 + V_2 + V_3) / 3.0f;
				// 새정점을 구한다.
				glm::vec3 vertex2 = vertex + tri.N * normal_len;

				// 백페이스 오프 냐?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // 예
					// 카메라 룩엣벡터를 구한다
					glm::vec3 look_at_dir = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.cam_view_dir;
					glm::vec4 look_at_dir_vec4;
					look_at_dir_vec4.x = look_at_dir.x;
					look_at_dir_vec4.y = look_at_dir.y;
					look_at_dir_vec4.z = look_at_dir.z;
					look_at_dir_vec4.w = 0.0f;

					glm::mat4 mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * mesh_model_mat;

					glm::mat4 inv_mesh_model_mat;
					inv_mesh_model_mat = glm::inverse(mesh_model_mat);

					look_at_dir_vec4 = inv_mesh_model_mat * look_at_dir_vec4;
					look_at_dir.x = look_at_dir_vec4.x;
					look_at_dir.y = look_at_dir_vec4.y;
					look_at_dir.z = look_at_dir_vec4.z;

					// 법선벡터와 내적.
					GLfloat Look_dot_N = glm::dot(look_at_dir, tri.N);
					// 각도가 둔각 이냐 ?
					if (Look_dot_N <= 0.0f)
					{ // 예
						// 라인 출력.
						glBegin(GL_LINES);
						glVertex3f(vertex.x, vertex.y, vertex.z);
						glVertex3f(vertex2.x, vertex2.y, vertex2.z);
						glEnd();
					} 
				}
				else { // 아니오
					// 라인 출력.
					glBegin(GL_LINES);
					glVertex3f(vertex.x, vertex.y, vertex.z);
					glVertex3f(vertex2.x, vertex2.y, vertex2.z);
					glEnd();
				}
			}
			else { // 아니오
				glm::vec3 N_1 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].z
					);

				// 백페이스 오프 냐 ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // 예
					// 카메라 룩엣벡터를 구한다
					glm::vec3 look_at_dir = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.cam_view_dir;
					glm::vec4 look_at_dir_vec4;
					look_at_dir_vec4.x = look_at_dir.x;
					look_at_dir_vec4.y = look_at_dir.y;
					look_at_dir_vec4.z = look_at_dir.z;
					look_at_dir_vec4.w = 0.0f;

					glm::mat4 mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * mesh_model_mat;

					glm::mat4 inv_mesh_model_mat;
					inv_mesh_model_mat = glm::inverse(mesh_model_mat);

					look_at_dir_vec4 = inv_mesh_model_mat * look_at_dir_vec4;
					look_at_dir.x = look_at_dir_vec4.x;
					look_at_dir.y = look_at_dir_vec4.y;
					look_at_dir.z = look_at_dir_vec4.z;

					// 법선벡터와 내적.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_1);
					// 각도가 둔각 이냐 ?
					if (Look_dot_N <= 0.0f)
					{ // 예
						glm::vec3 V_1 = glm::vec3(
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z
							);
						glm::vec3 V_1_2 = V_1 + N_1 * normal_len;
						glBegin(GL_LINES);
						glVertex3f(V_1.x, V_1.y, V_1.z);
						glVertex3f(V_1_2.x, V_1_2.y, V_1_2.z);
						glEnd();
					}
				}
				else { // 아니오
					glm::vec3 V_1 = glm::vec3(
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].x,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].y,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].pos_in_local[v_loc0.Angle_index].z
						);
					glm::vec3 V_1_2 = V_1 + N_1 * normal_len;
					glBegin(GL_LINES);
					glVertex3f(V_1.x, V_1.y, V_1.z);
					glVertex3f(V_1_2.x, V_1_2.y, V_1_2.z);
					glEnd();
				}

				glm::vec3 N_2 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].vertex_Normal[v_loc1.Angle_index].z
					);

				// 백페이스 오프 냐 ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // 예
					// 카메라 룩엣벡터를 구한다
					glm::vec3 look_at_dir = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.cam_view_dir;
					glm::vec4 look_at_dir_vec4;
					look_at_dir_vec4.x = look_at_dir.x;
					look_at_dir_vec4.y = look_at_dir.y;
					look_at_dir_vec4.z = look_at_dir.z;
					look_at_dir_vec4.w = 0.0f;

					glm::mat4 mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * mesh_model_mat;

					glm::mat4 inv_mesh_model_mat;
					inv_mesh_model_mat = glm::inverse(mesh_model_mat);

					look_at_dir_vec4 = inv_mesh_model_mat * look_at_dir_vec4;
					look_at_dir.x = look_at_dir_vec4.x;
					look_at_dir.y = look_at_dir_vec4.y;
					look_at_dir.z = look_at_dir_vec4.z;

					// 법선벡터와 내적.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_2);
					// 각도가 둔각 이냐 ?
					if (Look_dot_N <= 0.0f)
					{ // 예
						glm::vec3 V_2 = glm::vec3(
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z
							);
						glm::vec3 V_2_2 = V_2 + N_2 * normal_len;
						glBegin(GL_LINES); 
						glVertex3f(V_2.x, V_2.y, V_2.z);
						glVertex3f(V_2_2.x, V_2_2.y, V_2_2.z);
						glEnd();
					}
				}
				else { // 아니오
					glm::vec3 V_2 = glm::vec3(
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].x,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].y,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc1.point_index].pos_in_local[v_loc1.Angle_index].z
						);
					glm::vec3 V_2_2 = V_2 + N_2 * normal_len;
					glBegin(GL_LINES);
					glVertex3f(V_2.x, V_2.y, V_2.z);
					glVertex3f(V_2_2.x, V_2_2.y, V_2_2.z);
					glEnd();
				}

				glm::vec3 N_3 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].vertex_Normal[v_loc2.Angle_index].z
					);
				// 백페이스 오프 냐 ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // 예
					// 카메라 룩엣벡터를 구한다
					glm::vec3 look_at_dir = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.cam_view_dir;
					glm::vec4 look_at_dir_vec4;
					look_at_dir_vec4.x = look_at_dir.x;
					look_at_dir_vec4.y = look_at_dir.y;
					look_at_dir_vec4.z = look_at_dir.z;
					look_at_dir_vec4.w = 0.0f;

					glm::mat4 mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * mesh_model_mat;
					mesh_model_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * mesh_model_mat;

					glm::mat4 inv_mesh_model_mat;
					inv_mesh_model_mat = glm::inverse(mesh_model_mat);

					look_at_dir_vec4 = inv_mesh_model_mat * look_at_dir_vec4;
					look_at_dir.x = look_at_dir_vec4.x;
					look_at_dir.y = look_at_dir_vec4.y;
					look_at_dir.z = look_at_dir_vec4.z;

					// 법선벡터와 내적.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_3);
					// 각도가 둔각 이냐 ?
					if (Look_dot_N <= 0.0f)
					{ // 예
						glm::vec3 V_3 = glm::vec3(
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y,
							((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z
							);
						glm::vec3 V_3_2 = V_3 + N_3 * normal_len;
						glBegin(GL_LINES);
						glVertex3f(V_3.x, V_3.y, V_3.z);
						glVertex3f(V_3_2.x, V_3_2.y, V_3_2.z);
						glEnd();
					}
				}
				else { // 아니오
					glm::vec3 V_3 = glm::vec3(
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].x,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].y,
						((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc2.point_index].pos_in_local[v_loc2.Angle_index].z
						);
					glm::vec3 V_3_2 = V_3 + N_3 * normal_len;
					glBegin(GL_LINES);
					glVertex3f(V_3.x, V_3.y, V_3.z);
					glVertex3f(V_3_2.x, V_3_2.y, V_3_2.z);
					glEnd();
				}
			}
			// ------
		}
	}
	glPopMatrix();

	Draw_Light_Sphere(((COpenGL_Test_MFCDlg*)GetParent())->light_pos);

	glFlush();
	return;
}

void COpenGL_Static::GLRenderScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// -------------
	RECT rt;
	GetClientRect(&rt);
	GLfloat cx = (GLfloat)rt.right;
	GLfloat cy = (GLfloat)rt.bottom;

	GLfloat fAspect;
	if (cy == 0) cy = 1;
	glViewport(0, 0, cx, cy);

	fAspect = (GLfloat)cx / (GLfloat)cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// -------------

	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_FLAT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 1000.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(-100, 0, 0);
	glVertex3f(0, 100, 0);
	glVertex3f(100, 0, 0);
	glEnd();
	glPopMatrix();
	glFlush();
}

void COpenGL_Static::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.
	wglMakeCurrent(m_hDC, m_hRC);

	glEnable(GL_DEPTH_TEST);	// 기능 활성화
	glDepthFunc(GL_LEQUAL);

	//LIGHT
	glEnable(GL_LIGHTING);		// 빛을 사용한다.
	glEnable(GL_LIGHT0);		// 0번 빛을 사용한다.
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };		// ambient light값을 설정
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// diffuse light값을 설정
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// 빛을 정면에서 받을 경우 - 대부분 하얀색으로 지정
	GLfloat light_position[] = { 0.0f, 0.0f, 1.0f, 0.0f };		// 빛의 위치값을 저장

	light_position[0] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.x;
	light_position[1] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.y;
	light_position[2] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.z;

	// 빛의 각각의 속성값을 실제로 설정 - 모두 GL_LIGHT0이라는 빛의 속성을 지정.
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//COLOR MATERIAL
	glEnable(GL_COLOR_MATERIAL);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	((COpenGL_Test_MFCDlg*)GetParent())->sphere = gluNewQuadric(); // object 생성
	((COpenGL_Test_MFCDlg*)GetParent())->light_pos = glm::vec3(light_position[0], light_position[1], light_position[2]);

	((COpenGL_Test_MFCDlg*)GetParent())->tbi.width = 640.0f;
	((COpenGL_Test_MFCDlg*)GetParent())->tbi.height = 480.0f;

	renderScene();
	SwapBuffers(m_hDC);
	wglMakeCurrent(m_hDC, NULL);
}

void COpenGL_Static::Init_OpenGL()
{
	int nPixelFormat;
	// m_hDC = ::GetDC(m_hWnd);
	m_hDC = ::GetDC(this->GetSafeHwnd());

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0, 0,
		0, 0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));
	m_hRC = wglCreateContext(m_hDC);
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	wglMakeCurrent(NULL, NULL);
}

int COpenGL_Static::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}

void COpenGL_Static::GLResize(int cx, int cy)
{
	GLfloat fAspect;
	if (cy == 0) cy = 1;
	glViewport(0, 0, cx, cy);

	fAspect = (GLfloat)cx / (GLfloat)cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGL_Static::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}


void COpenGL_Static::OnDestroy()
{
	CStatic::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}
