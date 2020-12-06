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
//описываем вершины домика
static const VertexVector thing_vertices {
	{-1., -1., 1.}, {-1., 1., 1.}, {0.8, 1., 1.}, {1., 1., 1.}, {1., -1., 1.},
	{0.8, -1., 1.}, {1., 0.5, 0.9}, {1., -0.7, 0.9}, {0.8, -0.7, 0.9 }, {0.8, 0.5, 0.9},
	{1., 0.5, 0.1}, {1., -0.7, 0.1}, {0.8, -0.7, 0.1}, {0.8, 0.5, 0.1}, {1., -1., 0.},
	{0.8, -1., 0.}, {-1., -1., 0.}, {-1.,1.,0.}, {0.8, 1., 0.}, {1., 1., 0.},
	{0.5, 0., 3.}, {-0.5, 0., 3.}, {0.8, -0.9, 0.}, {0.8, 0.7, 0.}, {0.8, 0.7, 1.},
	{0.8, -0.9, 1.}, {-0.8, -0.9, 1.}, {-0.8, 0.7, 1.}, {-0.8, -0.9, 0.}, {-0.8, 0.7, 0.}
};
// описываем грани по вершинам по часовой стрелке если смотреть на них спереди
static const FaceVector thing_faces {
	{0, 1, 2, 5},
	{5, 2, 3, 4},
	{3, 2, 18, 19},
	{6, 3, 19, 10},
	{4, 3, 6, 7},
	{4, 7, 11, 14},
	{11, 10, 19, 14},
	{7, 8, 12, 11},
	{11, 12, 13, 10},
	{9, 6, 10, 13},
	{6, 9, 8, 7},
	{9, 24, 25, 8},
	{9, 24, 23, 13},
	{13, 12, 22, 23},
	{8, 25, 22, 12},
	{5, 4, 14, 15},
	{2, 1, 17, 18},
	{18, 17, 16, 15},
	{0, 5, 15, 16},
	{1, 0, 16, 17},
	{20, 21, 1, 3},
	{4, 20, 3},
	{21, 20, 4, 0},
	{21, 0, 1},
	{25, 26, 28, 22},
	{26, 27, 29, 28},
	{27, 24, 23, 29}
};
//описываем нормали к граням домика (считали как-то четко вообще почти не понял как высчитали)
static const NormalVecotr thing_normals {
	{0, 0, 1},
	{0, 0, 1},
	{0, 1, 0},
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{0, -1, 0},
	{0, 0, 1},
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0},
	{-1, 0, 0},
	{0, -1, 0},
	{0, 1, 0},
	{0, 0, 1},
	{0, -1, 0},
	{-1, 0, 0},
	{0., 0.447, 0.447},
	{0.485, 0., 0.485},
	{0., -0.447, 0.447},
	{-0.485, 0., 0.485},
	{0., 1., 0},
	{1., 0., 0.},
	{0., -1., 0.}
};

// описание модели трубы
static const VertexVector thing_vertices_tube {
	{0., 0.5, 2.7}, {0.3, 0.5, 2.7}, {0.3, 0.5, 1.},
	{0., 0.5, 1.}, {0., 0.3, 1.}, {0.3, 0.3, 1. },
	{0.3, 0.3, 2.7}, {0., 0.3, 2.7}
};

static const FaceVector thing_faces_tube {
	{1, 6, 7, 0},
	{1, 0, 3, 2},
	{6, 1, 2, 5},
	{7, 6, 5, 4},
	{0, 7, 4, 3}

};

static const NormalVecotr thing_normals_tube {
	{0., 0., 1.},
	{0., 1., 0.},
	{1., 0., 0.},
	{0., -1., 0.},
	{-1., 0., 0.}
};

//описание модели дивана
static const VertexVector thing_divan {
	{-0.7, -0.7, 0.5},
	{-0.7, 0.3, 0.5},
	{-0.5, 0.3, 0.5},
	{-0.5, -0.7, 0.5},
	{-0.7, -0.7, 0.},
	{-0.7, 0.3, 0.},
	{-0.5, 0.3, 0.},
	{-0.5, -0.7, 0.},
	{-0.5, -0.7, 0.25},
	{0., -0.7, 0.25},
	{0., -0.7, 0.},
	{0., -0.9, 0.},
	{0., -0.9, 0.5},
	{0., -0.7, 0.5},
	{-0.7, -0.9, 0.5},
	{-0.7, -0.9, 0.},
	{-0.5, 0.3, 0.25},
	{0., 0.3, 0.25},
	{0., 0.3, 0.},
	{-0.7, 0.5, 0.5},
	{0., 0.5, 0.5},
	{0., 0.3, 0.5},
	{0., 0.5, 0.},
	{-0.7, 0.5, 0.},
	{-0.7, 0.3, 0.6},
	{-0.5, 0.3, 0.6},
	{-0.5, -0.7, 0.6},
	{-0.7, -0.7, 0.6}

};

static const FaceVector thing_faces_divan {
	{27, 24, 25, 26},
	{8, 16, 17, 9},
	{26, 25, 16, 8},
	{9, 17, 18, 10},
	{19, 14, 15, 23},
	{23, 15, 11, 22},
	{14, 0, 13, 12},
	{12, 13, 10, 11},
	{13, 3, 8, 9},
	{14, 12, 11, 15},
	{2, 21, 17, 16},
	{1, 19, 20, 21},
	{20, 19, 23, 22},
	{21, 20, 22, 18},
	{25, 24, 1, 2},
	{27, 26, 3, 0},
	{24, 27, 0, 1}
};

static const NormalVecotr thing_normals_divan {
	{0., 0., 1.}, {0., 0., 1.}, {1., 0., 0.},
	{1., 0., 0.}, {-1., 0., 0.}, {0., 0., -1.},
	{0., 0., 1.}, {1., 0., 0.}, {0., 1., 0.},
	{0., -1., 0.}, {0., -1., 0.}, {0., 0., 1.},
	{0., 1., 0.}, {1., 0., 0.}, {0., 1., 0.},
	{0., -1., 0.},	{-1., 0., 0.}
};
static const Model Tube {
	thing_vertices_tube,
	thing_faces_tube,
	thing_normals_tube,

};

static const Model thing_model {
	thing_vertices,
	thing_faces,
	thing_normals
};

static const Model Divan {
	thing_divan,
	thing_faces_divan,
	thing_normals_divan
};
void draw_model(const Model& m, int qw){
	GLfloat a[]{0.f, 0.f, 0.f};
	GLfloat d[]{0.3f, 0.22f, 0.f};
	GLfloat s[]{0.3f, 0.3f, 0.f};
	GLfloat e[]{0.f, 0.01f, 0.f};
	GLfloat a1[]{0.f, 0.f, 0.f};
	GLfloat d1[]{0.1f, 0.1f, 0.f};
	GLfloat s1[]{0.1f, 0.18f, 0.f};
	GLfloat e1[]{0.f, 0.01f, 0.f};
	for (size_t face = 0; face < m.faces.size(); face++){

		//кол-во вершин в грани
		size_t nv = m.faces[face].size();
		if (nv == 3) glBegin(GL_TRIANGLES);
		else if (nv == 4) glBegin(GL_QUADS);
		else glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(&m.normals[face][0]);
		if (qw < 2) {
			// надеваем материал на треугольник
			// GL_AMBENT - цвет фоновой засветки
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
			// цвет рассеянного излучения
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
			// цвет бликов
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
			// излучение свет
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e);


		}
		else {
			// надеваем материал на треугольник
			// GL_AMBENT - цвет фоновой засветки
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a1);
			// цвет рассеянного излучения
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d1);
			// цвет бликов
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s1);
			// излучение свет
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e1);

		}


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
	a += 0.01;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.3, 0.7, 0.8, 0., 0., 0.5, 0., 0., 1.);
	glRotated(a, 0., 0., 1.);
	draw_model(thing_model, 0);
	draw_model(Tube, 1);
	draw_model(Divan, 2);
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
