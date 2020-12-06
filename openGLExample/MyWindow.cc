#include "MyWindow.h"
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>

//вектор вершин
using VertexVector = std::vector<std::vector<GLdouble>>;
//вектор координат вершин
using FaceVector = std::vector<std::vector<size_t>>;
//вектор нормалей граней
using NormalVecotr = std::vector<std::vector<GLdouble>>;

struct Model {
	VertexVector vertices;
	FaceVector faces;
	NormalVecotr normals;
};
//описываем вершины штуки нашей по 3 вершины в ряд
static const VertexVector thing_vertices {
	{-1., -2., 1.}, {-1., 1., 1.}, {0., 1., 1.},
	{0., -2., 1.}, {-1., 2., 0.}, {0., 2., 0.},
	{1., 1., 0.,}, {1., -2., 0.}, {-1., -2., -0.5},
	{1., -2., -0.5}, {-1., -1.5, -1.}, {-1., 2., -1.},
	{0., 2., -1.}, {1., 1., -1.}, {1., -1.5, -1.}
};
// описываем грани по вершинам по часовой стрелке если смотреть на них спереди
static const FaceVector thing_faces {
	{0, 1, 2, 3},
	{2, 1, 4, 5},
	{2, 5, 6},
	{3, 2, 6, 7},
	{5, 4, 11, 12},
	{6, 5, 12, 13},
	{7, 6, 13, 14, 9},
	{1, 0, 8, 10, 11, 4},
	{11, 10, 14, 13, 12},
	{0, 3, 7, 9, 8},
	{8, 9, 14, 10}
};
//описываем нормали к граням (считали как-то четко вообще почти не понял как высчитали)
static const NormalVecotr thing_normals {
	{0., 0., 1.},
	{0., 0.707, 0.707},
	{0.577, 0.577, 0.577},
	{0.707, 0., 0.707},
	{0., 1., 0.},
	{0.707, 0.707, 0.},
	{1., 0., 0.},
	{-1., 0., 0.},
	{0., 0., -1},
	{0., -1., 0.},
	{0., -0.707, -0.707}
};

static const Model thing_model {
	thing_vertices,
	thing_faces,
	thing_normals
};

void draw_model(const Model& m){
	for (size_t face = 0; face < m.faces.size(); face++){
		//кол-во вершин в грани
		size_t nv = m.faces[face].size();
		if (nv == 3) glBegin(GL_TRIANGLES);
		else if (nv == 4) glBegin(GL_QUADS);
		else glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(&m.normals[face][0]);

		for (size_t v = 0; v < nv; v++) {
			glVertex3dv(&m.vertices[m.faces[face][v]][0]);

		}
		glEnd();
	}
}
void MyWindow::setupGL(){
	glClearColor(0.1f, 0.4f, 0.5f, 1.f);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45., double(width())/height(), 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void MyWindow::render(){
	static double a = 0.;
	a += 1.;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(4., 4., 1.5, 0., 0., 0., 0., 0., 1.);
	glRotated(a, 0., 0., 1.);
	draw_model(thing_model);
//	glTranslated(0.,0.5,0.);
//	glScaled(0.25,0.5,1.);
//	glBegin(GL_TRIANGLES);
//		glColor3d(1.,0.,0.);
//		glVertex2d(0., 1.);
//		glColor3d(0.,1.,0.);
//		glVertex2d(1., -1.);
//		glColor3d(0.,0.,1.);
//		glVertex2d(-1., -1.);
//	glEnd();

}
