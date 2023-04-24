#include <iostream>
#include <fstream>
#include <vector>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include <string>
using namespace std;

//globals

unsigned int elefante;
struct Face {
	vector<int> vi;
	vector<int> ti;
	vector<int> ni;
};

Face criar_face(vector<int> vi, vector<int> ti, vector<int> ni) {
	Face face;
	face.vi = vi;
	face.ti = ti;
	face.ni = ni;
	return face;
}

vector<vector<float>> vertices;
vector<Face> faces;
vector<vector<float>> normais;
vector<vector<float>> texturas;
float rot_ele;

void loadObj(string fname)
{
    int read;
    //float x, y, z;
    ifstream arquivo(fname);
    if (!arquivo.is_open()) {
        cout << "arquivo nao encontrado";
        exit(1);
    }
    else {
        string tipo;
		while (arquivo >> tipo)
		{
			if (tipo == "f")
			{
				string a, b, c;
				arquivo >> a >> b >> c;

				int v1, v2, v3;
				int t1, t2, t3;
				int n1, n2, n3;

				v1 = stoi(a.substr(0, a.find("/"))) - 1;
				a.erase(0, a.find("/") + 1);

				if (a.find("/") != 0) {
					t1 = stoi(a.substr(0, a.find("/"))) - 1;
				}
				else {
					t1 = -1;
				}

				a.erase(0, a.find("/") + 1);
				n1 = stoi(a) - 1;
				v2 = stoi(b.substr(0, b.find("/"))) - 1;
				b.erase(0, b.find("/") + 1);

				if (b.find("/") != 0) {
					t2 = stoi(b.substr(0, b.find("/"))) - 1;
				}
				else {
					t2 = -1;
				}

				b.erase(0, b.find("/") + 1);
				n2 = stoi(b) - 1;
				v3 = stoi(c.substr(0, c.find("/"))) - 1;
				c.erase(0, c.find("/") + 1);

				if (c.find("/") != 0) {
					t3 = stoi(c.substr(0, c.find("/"))) - 1;
				}
				else {
					t3 = -1;
				}

				c.erase(0, c.find("/") + 1);
				n3 = stoi(c) - 1;

				vector<int> vi;
				vector<int> ti;
				vector<int> ni;

				vi.push_back(v1);
				vi.push_back(v2);
				vi.push_back(v3);

				ti.push_back(t1);
				ti.push_back(t2);
				ti.push_back(t3);

				ni.push_back(n1);
				ni.push_back(n2);
				ni.push_back(n3);

				faces.push_back(criar_face(vi, ti, ni));
			}
			else if (tipo == "v")
			{
				vector<float> vertice;
				float x, y, z;
				arquivo >> x >> y >> z;
				vertice.push_back(x);
				vertice.push_back(y);
				vertice.push_back(z);
				vertices.push_back(vertice);
			}
			else if (tipo == "vn")
			{
				vector<float> normal;
				float x, y, z;
				arquivo >> x >> y >> z;
				normal.push_back(x);
				normal.push_back(y);
				normal.push_back(z);
				normais.push_back(normal);
			}
			else if (tipo == "vt") {
				vector<float> textura;
				float x, y;
				arquivo >> x >> y;
				textura.push_back(x);
				textura.push_back(y);
				texturas.push_back(textura);
			}
		}
    }




    elefante = glGenLists(1);
    glPointSize(2.0);
    glNewList(elefante, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_QUADS);

        for (int i = 0; i < faces.size(); i++)
        {
            vector<int> face = faces[i];

            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);
            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);

            glVertex3f(vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2]);
            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);

            glVertex3f(vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2]);
            glVertex3f(vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2]);

        }
        glEnd();

    }
    glPopMatrix();
    glEndList();
    arquivo.close();

}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}
void drawElephant()
{
    glPushMatrix();
    glTranslatef(0, -40.00, -105);
    glColor3f(1.0, 0.23, 0.27);
    glScalef(0.4, 0.4, 0.4);
    glRotatef(rot_ele, 0, 1, 0);
    glCallList(elefante);
    glPopMatrix();
    rot_ele = rot_ele + 0.6;
    if (rot_ele > 360) rot_ele = rot_ele - 360;
}
void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawElephant();
    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 450);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Carregar OBJ");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutTimerFunc(10, timer, 0);
    loadObj("data/mba1.obj");
    glutMainLoop();
    return 0;
}