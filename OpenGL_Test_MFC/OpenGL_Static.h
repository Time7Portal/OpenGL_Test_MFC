#pragma once
#include "afxwin.h"

#include "glut/glut.h"
#include <gl/glu.h>

#include "glm//vec3.hpp" // glm::vec3
#include "glm//vec4.hpp" // glm::vec4
#include "glm//mat4x4.hpp" // glm::mat4
#include "glm//gtc//matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm//gtc//quaternion.hpp"
#include "glm//gtx//quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

class COpenGL_Static :
	public CStatic
{
public:
	COpenGL_Static();
	~COpenGL_Static();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	HGLRC m_hRC;
	HDC m_hDC;
	void GLResize(int cx, int cy);
	void GLRenderScene();
	void Init_OpenGL();
	void renderScene();
	void Draw_Light_Sphere(glm::vec3 pos);
	void EndScene();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

