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
	gluSphere(((COpenGL_Test_MFCDlg*)GetParent())->sphere, 1.0f / 60.0f, 50, 10);  // sphere �׸��� 
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
		glEnable(GL_CULL_FACE);		// �޸鿡 ���ؼ��� ������� ����
		glFrontFace(GL_CCW);		// �ð������ �ո�
		glCullFace(GL_NONE);
	}
	else
	{
		glDisable(GL_CULL_FACE);		// �޸鿡 ���ؼ��� ������� ����
		// glFrontFace(GL_CCW);		// �ð������ �ո�
		// glCullFace(GL_NONE);
	}

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RECT rt;
	GetClientRect(&rt);
	GLfloat cx = (GLfloat)rt.right;
	GLfloat cy = (GLfloat)rt.bottom;

	glViewport(0, 0, cx, cy);

	// �𵨺� ��� ���.
	glm::mat4 model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.inv_model_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_Rotate_mat * model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.model_mat * model_view_mat;
	model_view_mat = ((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.view_mat * model_view_mat;

	// ���������� �𵨺� ��� ����.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(model_view_mat));

	// ���������� ���� ��� ����.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(((COpenGL_Test_MFCDlg*)GetParent())->Rendering_mat_info.proj_mat));

	if (((COpenGL_Test_MFCDlg*)GetParent())->vertex_mode_flag == true)
	{
		int tmp_angle_cnt = 360 / ((COpenGL_Test_MFCDlg*)GetParent())->Angle_index_Step;
		glPushMatrix();

		glColor3f(1.f, 1.f, 0.f);
		glDisable(GL_LIGHTING);		// ���� ����Ѵ�.
		glDisable(GL_LIGHT0);		// 0�� ���� ����Ѵ�.
		glDisable(GL_COLOR_MATERIAL);

		// �ﰢ�� ������ ������ŭ �ݺ�
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

			// �ﰢ�� �����͸� ��´�.
			tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

			// �ﰢ���� �̷�� �ִ°� ������ ��ġ�� ��´�.
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
	{ // ��
		glShadeModel(GL_FLAT);
	}
	else
	{ // ��
		glShadeModel(GL_SMOOTH);
	}
	// ------------------------------------
	int tmp_angle_cnt = 360 / ((COpenGL_Test_MFCDlg*)GetParent())->Angle_index_Step;
	glPushMatrix();

	if (((COpenGL_Test_MFCDlg*)GetParent())->wireframe_mode_flag == true)
	{
		glPolygonMode(GL_FRONT, GL_LINE); // �̰��ϸ� ���̾�������
		glPolygonMode(GL_BACK, GL_LINE); // �̰��ϸ� ���̾�������
		glDisable(GL_LIGHTING);		// ���� ����Ѵ�.
		glDisable(GL_LIGHT0);		// 0�� ���� ����Ѵ�.
		glDisable(GL_COLOR_MATERIAL);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL); // �̰��ϸ� �ָ���
		glPolygonMode(GL_BACK, GL_FILL); // �̰��ϸ� �ָ���
		glEnable(GL_LIGHTING);		// ���� ����Ѵ�.
		glEnable(GL_LIGHT0);		// 0�� ���� ����Ѵ�.
		glEnable(GL_COLOR_MATERIAL);
	}
	glColor3f(1.f, 1.f, 1.f);

	// �ﰢ�� ������ ������ŭ �ݺ�
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

		// �ﰢ�� �����͸� ��´�.
		tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

		// �ﰢ���� �̷�� �ִ°� ������ ��ġ�� ��´�.
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
		glDisable(GL_LIGHTING);		// ���� ����Ѵ�.
		glDisable(GL_LIGHT0);		// 0�� ���� ����Ѵ�.
		glDisable(GL_COLOR_MATERIAL);

		// �ﰢ�� ������ ������ŭ �ݺ�
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

			// �ﰢ�� �����͸� ��´�.
			tri_index_info tri = ((COpenGL_Test_MFCDlg*)GetParent())->tri_index_info_list[tri_idx];

			// �ﰢ���� �̷�� �ִ°� ������ ��ġ�� ��´�.
			sub_tri_index_info v_loc0 = tri.data[0];
			sub_tri_index_info v_loc1 = tri.data[1];
			sub_tri_index_info v_loc2 = tri.data[2];

			// ------
			GLfloat normal_len = 0.125f / 4.0f;

			// �÷� ���̵��̳�?
			if (((COpenGL_Test_MFCDlg*)GetParent())->flat_shading_mode_flag == true)
			{ // ��
				// �� ������ ���Ѵ� 
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
				
				// �ﰢ���� �����߽��� ���Ѵ�.
				glm::vec3 vertex = (V_1 + V_2 + V_3) / 3.0f;
				// �������� ���Ѵ�.
				glm::vec3 vertex2 = vertex + tri.N * normal_len;

				// �����̽� ���� ��?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // ��
					// ī�޶� �迧���͸� ���Ѵ�
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

					// �������Ϳ� ����.
					GLfloat Look_dot_N = glm::dot(look_at_dir, tri.N);
					// ������ �а� �̳� ?
					if (Look_dot_N <= 0.0f)
					{ // ��
						// ���� ���.
						glBegin(GL_LINES);
						glVertex3f(vertex.x, vertex.y, vertex.z);
						glVertex3f(vertex2.x, vertex2.y, vertex2.z);
						glEnd();
					} 
				}
				else { // �ƴϿ�
					// ���� ���.
					glBegin(GL_LINES);
					glVertex3f(vertex.x, vertex.y, vertex.z);
					glVertex3f(vertex2.x, vertex2.y, vertex2.z);
					glEnd();
				}
			}
			else { // �ƴϿ�
				glm::vec3 N_1 = glm::vec3(
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].x,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].y,
					((COpenGL_Test_MFCDlg*)GetParent())->data_Rendering_Data[v_loc0.point_index].vertex_Normal[v_loc0.Angle_index].z
					);

				// �����̽� ���� �� ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // ��
					// ī�޶� �迧���͸� ���Ѵ�
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

					// �������Ϳ� ����.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_1);
					// ������ �а� �̳� ?
					if (Look_dot_N <= 0.0f)
					{ // ��
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
				else { // �ƴϿ�
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

				// �����̽� ���� �� ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // ��
					// ī�޶� �迧���͸� ���Ѵ�
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

					// �������Ϳ� ����.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_2);
					// ������ �а� �̳� ?
					if (Look_dot_N <= 0.0f)
					{ // ��
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
				else { // �ƴϿ�
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
				// �����̽� ���� �� ?
				if (((COpenGL_Test_MFCDlg*)GetParent())->Back_Face_flag == false)
				{ // ��
					// ī�޶� �迧���͸� ���Ѵ�
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

					// �������Ϳ� ����.
					GLfloat Look_dot_N = glm::dot(look_at_dir, N_3);
					// ������ �а� �̳� ?
					if (Look_dot_N <= 0.0f)
					{ // ��
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
				else { // �ƴϿ�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CStatic::OnPaint()��(��) ȣ������ ���ʽÿ�.
	wglMakeCurrent(m_hDC, m_hRC);

	glEnable(GL_DEPTH_TEST);	// ��� Ȱ��ȭ
	glDepthFunc(GL_LEQUAL);

	//LIGHT
	glEnable(GL_LIGHTING);		// ���� ����Ѵ�.
	glEnable(GL_LIGHT0);		// 0�� ���� ����Ѵ�.
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };		// ambient light���� ����
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// diffuse light���� ����
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// ���� ���鿡�� ���� ��� - ��κ� �Ͼ������ ����
	GLfloat light_position[] = { 0.0f, 0.0f, 1.0f, 0.0f };		// ���� ��ġ���� ����

	light_position[0] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.x;
	light_position[1] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.y;
	light_position[2] = ((COpenGL_Test_MFCDlg*)GetParent())->light_pos.z;

	// ���� ������ �Ӽ����� ������ ���� - ��� GL_LIGHT0�̶�� ���� �Ӽ��� ����.
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//COLOR MATERIAL
	glEnable(GL_COLOR_MATERIAL);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	((COpenGL_Test_MFCDlg*)GetParent())->sphere = gluNewQuadric(); // object ����
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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	VERIFY(wglMakeCurrent(m_hDC, m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL, NULL));
}


void COpenGL_Static::OnDestroy()
{
	CStatic::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd, m_hDC);
}
