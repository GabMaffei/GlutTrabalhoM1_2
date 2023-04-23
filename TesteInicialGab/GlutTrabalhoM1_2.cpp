#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

bool cima = false;
bool baixo = false;
bool esquerda = false;
bool direita = false;

bool mais = false;
bool menos = false;
bool reset = false;

bool menorT = false;
bool maiorT = false;

bool contructor = false;

struct Vector3D {

	double x;
	double y;
	double z;
};


void rotationX(Vector3D& ponto, double x, double y, double z) {

	double rad = 0;

	rad = x;
	ponto.y = cos(rad) * ponto.y - sin(rad) * ponto.z;
	ponto.z = sin(rad) * ponto.y + cos(rad) * ponto.z;

}
void rotationY(Vector3D& ponto, double x, double y, double z) {
	double rad = 0;

	rad = y;
	ponto.x = cos(rad) * ponto.x + sin(rad) * ponto.z;
	ponto.z = -sin(rad) * ponto.x + cos(rad) * ponto.z;
}

void rotationZ(Vector3D& ponto, double x, double y, double z) {
	double rad = 0;

	rad = z;
	ponto.x = cos(rad) * ponto.x - sin(rad) * ponto.y;
	ponto.y = sin(rad) * ponto.x + cos(rad) * ponto.y;
}



void translation(Vector3D& ponto, double x, double y, double z) {

	ponto.x = ponto.x + x;
	ponto.y = ponto.y + y;
	ponto.z = ponto.z + z;

}

void scale(Vector3D& ponto, double x, double y, double z) {

	ponto.x = ponto.x * x;
	ponto.y = ponto.y * y;
	ponto.z = ponto.z * z;

}

/*----------PONTOS-------------*/
//Verde
Vector3D pontoVUm;
Vector3D pontoVDois;
Vector3D pontoVTres;
Vector3D pontoVQuatro;
//Laranja
Vector3D pontoLUm;
Vector3D pontoLDois;
Vector3D pontoLTres;
Vector3D pontoLQuatro;
//VeRmelho
Vector3D pontoRUm;
Vector3D pontoRDois;
Vector3D pontoRTres;
Vector3D pontoRQuatro;
//Amarelo
Vector3D pontoAUm;
Vector3D pontoADois;
Vector3D pontoATres;
Vector3D pontoAQuatro;
//AZul
Vector3D pontoZUm;
Vector3D pontoZDois;
Vector3D pontoZTres;
Vector3D pontoZQuatro;
//Magenta
Vector3D pontoMUm;
Vector3D pontoMDois;
Vector3D pontoMTres;
Vector3D pontoMQuatro;

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if (!contructor || reset) {

		/*Verde*/
		//Um
		pontoVUm.x = 1.0f;
		pontoVUm.y = 1.0f;
		pontoVUm.z = -1.0f;
		//Dois
		pontoVDois.x = -1.0f;
		pontoVDois.y = 1.0f;
		pontoVDois.z = -1.0f;
		//Tres
		pontoVTres.x = -1.0f;
		pontoVTres.y = 1.0f;
		pontoVTres.z = 1.0f;
		//Quatro
		pontoVQuatro.x = 1.0f;
		pontoVQuatro.y = 1.0f;
		pontoVQuatro.z = 1.0f;

		/*Laranja*/
		//Um
		pontoLUm.x = 1.0f;
		pontoLUm.y = -1.0f;
		pontoLUm.z = 1.0f;
		//Dois
		pontoLDois.x = -1.0f;
		pontoLDois.y = -1.0f;
		pontoLDois.z = 1.0f;
		//Tres
		pontoLTres.x = -1.0f;
		pontoLTres.y = -1.0f;
		pontoLTres.z = -1.0f;
		//Quatro
		pontoLQuatro.x = 1.0f;
		pontoLQuatro.y = -1.0f;
		pontoLQuatro.z = -1.0f;

		/*VeRmelho*/
		//Um
		pontoRUm.x = 1.0f;
		pontoRUm.y = 1.0f;
		pontoRUm.z = 1.0f;
		//Dois
		pontoRDois.x = -1.0f;
		pontoRDois.y = 1.0f;
		pontoRDois.z = 1.0f;
		//Tres
		pontoRTres.x = -1.0f;
		pontoRTres.y = -1.0f;
		pontoRTres.z = 1.0f;
		//Quatro
		pontoRQuatro.x = 1.0f;
		pontoRQuatro.y = -1.0f;
		pontoRQuatro.z = 1.0f;

		/*Amarelo*/
		//Um
		pontoAUm.x = 1.0f;
		pontoAUm.y = -1.0f;
		pontoAUm.z = -1.0f;
		//Dois
		pontoADois.x = -1.0f;
		pontoADois.y = -1.0f;
		pontoADois.z = -1.0f;
		//Tres
		pontoATres.x = -1.0f;
		pontoATres.y = 1.0f;
		pontoATres.z = -1.0f;
		//Quatro
		pontoAQuatro.x = 1.0f;
		pontoAQuatro.y = 1.0f;
		pontoAQuatro.z = -1.0f;

		/*AZul*/
		//Um
		pontoZUm.x = -1.0f;
		pontoZUm.y = 1.0f;
		pontoZUm.z = 1.0f;
		//Dois
		pontoZDois.x = -1.0f;
		pontoZDois.y = 1.0f;
		pontoZDois.z = -1.0f;
		//Tres
		pontoZTres.x = -1.0f;
		pontoZTres.y = -1.0f;
		pontoZTres.z = -1.0f;
		//Quatro
		pontoZQuatro.x = -1.0f;
		pontoZQuatro.y = -1.0f;
		pontoZQuatro.z = 1.0f;

		/*Magenta*/
		//Um
		pontoMUm.x = 1.0f;
		pontoMUm.y = 1.0f;
		pontoMUm.z = -1.0f;
		//Dois
		pontoMDois.x = 1.0f;
		pontoMDois.y = 1.0f;
		pontoMDois.z = 1.0f;
		//Tres
		pontoMTres.x = 1.0f;
		pontoMTres.y = -1.0f;
		pontoMTres.z = 1.0f;
		//Quatro
		pontoMQuatro.x = 1.0f;
		pontoMQuatro.y = -1.0f;
		pontoMQuatro.z = -1.0f;

		contructor = true;
	}

	if (cima) {
		//Verde
		rotationX(pontoVUm, -0.001, 0, 0);
		rotationX(pontoVDois, -0.001, 0, 0);
		rotationX(pontoVTres, -0.001, 0, 0);
		rotationX(pontoVQuatro, -0.001, 0, 0);

		//Laranja
		rotationX(pontoLUm, -0.001, 0, 0);
		rotationX(pontoLDois, -0.001, 0, 0);
		rotationX(pontoLTres, -0.001, 0, 0);
		rotationX(pontoLQuatro, -0.001, 0, 0);

		//VeRmelho
		rotationX(pontoRUm, -0.001, 0, 0);
		rotationX(pontoRDois, -0.001, 0, 0);
		rotationX(pontoRTres, -0.001, 0, 0);
		rotationX(pontoRQuatro, -0.001, 0, 0);

		//Amarelo
		rotationX(pontoAUm, -0.001, 0, 0);
		rotationX(pontoADois, -0.001, 0, 0);
		rotationX(pontoATres, -0.001, 0, 0);
		rotationX(pontoAQuatro, -0.001, 0, 0);

		//AZul
		rotationX(pontoZUm, -0.001, 0, 0);
		rotationX(pontoZDois, -0.001, 0, 0);
		rotationX(pontoZTres, -0.001, 0, 0);
		rotationX(pontoZQuatro, -0.001, 0, 0);

		//Magsenta
		rotationX(pontoMUm, -0.001, 0, 0);
		rotationX(pontoMDois, -0.001, 0, 0);
		rotationX(pontoMTres, -0.001, 0, 0);
		rotationX(pontoMQuatro, -0.001, 0, 0);
	}

	if (baixo) {
		//Verde
		rotationX(pontoVUm, 0.001, 0, 0);
		rotationX(pontoVDois, 0.001, 0, 0);
		rotationX(pontoVTres, 0.001, 0, 0);
		rotationX(pontoVQuatro, 0.001, 0, 0);

		//Laranja
		rotationX(pontoLUm, 0.001, 0, 0);
		rotationX(pontoLDois, 0.001, 0, 0);
		rotationX(pontoLTres, 0.001, 0, 0);
		rotationX(pontoLQuatro, 0.001, 0, 0);

		//VeRmelho
		rotationX(pontoRUm, 0.001, 0, 0);
		rotationX(pontoRDois, 0.001, 0, 0);
		rotationX(pontoRTres, 0.001, 0, 0);
		rotationX(pontoRQuatro, 0.001, 0, 0);

		//Amarelo
		rotationX(pontoAUm, 0.001, 0, 0);
		rotationX(pontoADois, 0.001, 0, 0);
		rotationX(pontoATres, 0.001, 0, 0);
		rotationX(pontoAQuatro, 0.001, 0, 0);

		//AZul
		rotationX(pontoZUm, 0.001, 0, 0);
		rotationX(pontoZDois, 0.001, 0, 0);
		rotationX(pontoZTres, 0.001, 0, 0);
		rotationX(pontoZQuatro, 0.001, 0, 0);

		//Magsenta
		rotationX(pontoMUm, 0.001, 0, 0);
		rotationX(pontoMDois, 0.001, 0, 0);
		rotationX(pontoMTres, 0.001, 0, 0);
		rotationX(pontoMQuatro, 0.001, 0, 0);
	}

	if (esquerda) {
		//Verde
		rotationY(pontoVUm, 0, -0.001, 0);
		rotationY(pontoVDois, 0, -0.001, 0);
		rotationY(pontoVTres, 0, -0.001, 0);
		rotationY(pontoVQuatro, 0, -0.001, 0);

		//Laranja
		rotationY(pontoLUm, 0, -0.001, 0);
		rotationY(pontoLDois, 0, -0.001, 0);
		rotationY(pontoLTres, 0, -0.001, 0);
		rotationY(pontoLQuatro, 0, -0.001, 0);

		//VeRmelho
		rotationY(pontoRUm, 0, -0.001, 0);
		rotationY(pontoRDois, 0, -0.001, 0);
		rotationY(pontoRTres, 0, -0.001, 0);
		rotationY(pontoRQuatro, 0, -0.001, 0);

		//Amarelo
		rotationY(pontoAUm, 0, -0.001, 0);
		rotationY(pontoADois, 0, -0.001, 0);
		rotationY(pontoATres, 0, -0.001, 0);
		rotationY(pontoAQuatro, 0, -0.001, 0);

		//AZul
		rotationY(pontoZUm, 0, -0.001, 0);
		rotationY(pontoZDois, 0, -0.001, 0);
		rotationY(pontoZTres, 0, -0.001, 0);
		rotationY(pontoZQuatro, 0, -0.001, 0);

		//Magenta
		rotationY(pontoMUm, 0, -0.001, 0);
		rotationY(pontoMDois, 0, -0.001, 0);
		rotationY(pontoMTres, 0, -0.001, 0);
		rotationY(pontoMQuatro, 0, -0.001, 0);
	}

	if (direita) {
		//Verde
		rotationY(pontoVUm, 0, 0.001, 0);
		rotationY(pontoVDois, 0, 0.001, 0);
		rotationY(pontoVTres, 0, 0.001, 0);
		rotationY(pontoVQuatro, 0, 0.001, 0);

		//Laranja
		rotationY(pontoLUm, 0, 0.001, 0);
		rotationY(pontoLDois, 0, 0.001, 0);
		rotationY(pontoLTres, 0, 0.001, 0);
		rotationY(pontoLQuatro, 0, 0.001, 0);

		//VeRmelho
		rotationY(pontoRUm, 0, 0.001, 0);
		rotationY(pontoRDois, 0, 0.001, 0);
		rotationY(pontoRTres, 0, 0.001, 0);
		rotationY(pontoRQuatro, 0, 0.001, 0);

		//Amarelo
		rotationY(pontoAUm, 0, 0.001, 0);
		rotationY(pontoADois, 0, 0.001, 0);
		rotationY(pontoATres, 0, 0.001, 0);
		rotationY(pontoAQuatro, 0, 0.001, 0);

		//AZul
		rotationY(pontoZUm, 0, 0.001, 0);
		rotationY(pontoZDois, 0, 0.001, 0);
		rotationY(pontoZTres, 0, 0.001, 0);
		rotationY(pontoZQuatro, 0, 0.001, 0);

		//Magenta
		rotationY(pontoMUm, 0, 0.001, 0);
		rotationY(pontoMDois, 0, 0.001, 0);
		rotationY(pontoMTres, 0, 0.001, 0);
		rotationY(pontoMQuatro, 0, 0.001, 0);
	}

	if (mais) {
		//Verde
		scale(pontoVUm, 1.001, 1.001, 1.001);
		scale(pontoVDois, 1.001, 1.001, 1.001);
		scale(pontoVTres, 1.001, 1.001, 1.001);
		scale(pontoVQuatro, 1.001, 1.001, 1.001);

		//Laranja
		scale(pontoLUm, 1.001, 1.001, 1.001);
		scale(pontoLDois, 1.001, 1.001, 1.001);
		scale(pontoLTres, 1.001, 1.001, 1.001);
		scale(pontoLQuatro, 1.001, 1.001, 1.001);

		//VeRmelho
		scale(pontoRUm, 1.001, 1.001, 1.001);
		scale(pontoRDois, 1.001, 1.001, 1.001);
		scale(pontoRTres, 1.001, 1.001, 1.001);
		scale(pontoRQuatro, 1.001, 1.001, 1.001);

		//Amarelo
		scale(pontoAUm, 1.001, 1.001, 1.001);
		scale(pontoADois, 1.001, 1.001, 1.001);
		scale(pontoATres, 1.001, 1.001, 1.001);
		scale(pontoAQuatro, 1.001, 1.001, 1.001);

		//AZul
		scale(pontoZUm, 1.001, 1.001, 1.001);
		scale(pontoZDois, 1.001, 1.001, 1.001);
		scale(pontoZTres, 1.001, 1.001, 1.001);
		scale(pontoZQuatro, 1.001, 1.001, 1.001);

		//Magsenta
		scale(pontoMUm, 1.001, 1.001, 1.001);
		scale(pontoMDois, 1.001, 1.001, 1.001);
		scale(pontoMTres, 1.001, 1.001, 1.001);
		scale(pontoMQuatro, 1.001, 1.001, 1.001);
	}

	if (menos) {
		//Verde
		scale(pontoVUm, 0.999, 0.999, 0.999);
		scale(pontoVDois, 0.999, 0.999, 0.999);
		scale(pontoVTres, 0.999, 0.999, 0.999);
		scale(pontoVQuatro, 0.999, 0.999, 0.999);

		//Laranja
		scale(pontoLUm, 0.999, 0.999, 0.999);
		scale(pontoLDois, 0.999, 0.999, 0.999);
		scale(pontoLTres, 0.999, 0.999, 0.999);
		scale(pontoLQuatro, 0.999, 0.999, 0.999);

		//VeRmelho
		scale(pontoRUm, 0.999, 0.999, 0.999);
		scale(pontoRDois, 0.999, 0.999, 0.999);
		scale(pontoRTres, 0.999, 0.999, 0.999);
		scale(pontoRQuatro, 0.999, 0.999, 0.999);

		//Amarelo
		scale(pontoAUm, 0.999, 0.999, 0.999);
		scale(pontoADois, 0.999, 0.999, 0.999);
		scale(pontoATres, 0.999, 0.999, 0.999);
		scale(pontoAQuatro, 0.999, 0.999, 0.999);

		//AZul
		scale(pontoZUm, 0.999, 0.999, 0.999);
		scale(pontoZDois, 0.999, 0.999, 0.999);
		scale(pontoZTres, 0.999, 0.999, 0.999);
		scale(pontoZQuatro, 0.999, 0.999, 0.999);

		//Magsenta
		scale(pontoMUm, 0.999, 0.999, 0.999);
		scale(pontoMDois, 0.999, 0.999, 0.999);
		scale(pontoMTres, 0.999, 0.999, 0.999);
		scale(pontoMQuatro, 0.999, 0.999, 0.999);
	}

	if (maiorT) {
		//Verde
		translation(pontoVUm, 0.001, 0.001, 0.001);
		translation(pontoVDois, 0.001, 0.001, 0.001);
		translation(pontoVTres, 0.001, 0.001, 0.001);
		translation(pontoVQuatro, 0.001, 0.001, 0.001);

		//Laranja
		translation(pontoLUm, 0.001, 0.001, 0.001);
		translation(pontoLDois, 0.001, 0.001, 0.001);
		translation(pontoLTres, 0.001, 0.001, 0.001);
		translation(pontoLQuatro, 0.001, 0.001, 0.001);

		//VeRmelho
		translation(pontoRUm, 0.001, 0.001, 0.001);
		translation(pontoRDois, 0.001, 0.001, 0.001);
		translation(pontoRTres, 0.001, 0.001, 0.001);
		translation(pontoRQuatro, 0.001, 0.001, 0.001);

		//Amarelo
		translation(pontoAUm, 0.001, 0.001, 0.001);
		translation(pontoADois, 0.001, 0.001, 0.001);
		translation(pontoATres, 0.001, 0.001, 0.001);
		translation(pontoAQuatro, 0.001, 0.001, 0.001);

		//AZul
		translation(pontoZUm, 0.001, 0.001, 0.001);
		translation(pontoZDois, 0.001, 0.001, 0.001);
		translation(pontoZTres, 0.001, 0.001, 0.001);
		translation(pontoZQuatro, 0.001, 0.001, 0.001);

		//Magsenta
		translation(pontoMUm, 0.001, 0.001, 0.001);
		translation(pontoMDois, 0.001, 0.001, 0.001);
		translation(pontoMTres, 0.001, 0.001, 0.001);
		translation(pontoMQuatro, 0.001, 0.001, 0.001);
	}

	if (menorT) {
		//Verde
		translation(pontoVUm, -0.001, -0.001, -0.001);
		translation(pontoVDois, -0.001, -0.001, -0.001);
		translation(pontoVTres, -0.001, -0.001, -0.001);
		translation(pontoVQuatro, -0.001, -0.001, -0.001);

		//Laranja
		translation(pontoLUm, -0.001, -0.001, -0.001);
		translation(pontoLDois, -0.001, -0.001, -0.001);
		translation(pontoLTres, -0.001, -0.001, -0.001);
		translation(pontoLQuatro, -0.001, -0.001, -0.001);

		//VeRmelho
		translation(pontoRUm, -0.001, -0.001, -0.001);
		translation(pontoRDois, -0.001, -0.001, -0.001);
		translation(pontoRTres, -0.001, -0.001, -0.001);
		translation(pontoRQuatro, -0.001, -0.001, -0.001);

		//Amarelo
		translation(pontoAUm, -0.001, -0.001, -0.001);
		translation(pontoADois, -0.001, -0.001, -0.001);
		translation(pontoATres, -0.001, -0.001, -0.001);
		translation(pontoAQuatro, -0.001, -0.001, -0.001);

		//AZul
		translation(pontoZUm, -0.001, -0.001, -0.001);
		translation(pontoZDois, -0.001, -0.001, -0.001);
		translation(pontoZTres, -0.001, -0.001, -0.001);
		translation(pontoZQuatro, -0.001, -0.001, -0.001);

		//Magsenta
		translation(pontoMUm, -0.001, -0.001, -0.001);
		translation(pontoMDois, -0.001, -0.001, -0.001);
		translation(pontoMTres, -0.001, -0.001, -0.001);
		translation(pontoMQuatro, -0.001, -0.001, -0.001);
	}

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0); //Define a posição da camera

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//COMANDO ATIVAR WIREFRAME

	//Renderiza o cubo
	glBegin(GL_QUADS);                // Começa a desenhar o cubo com 6 quads
		// Face superior (y = 1.0f)
		// Define as vertices no sentido anti-horáro (CCW)
		glColor3f(0.0f, 1.0f, 0.0f);     // Verde
		glVertex3f(pontoVUm.x, pontoVUm.y, pontoVUm.z);
		glVertex3f(pontoVDois.x, pontoVDois.y, pontoVDois.z);
		glVertex3f(pontoVTres.x, pontoVTres.y, pontoVTres.z);
		glVertex3f(pontoVQuatro.x, pontoVQuatro.y, pontoVQuatro.z);

		// Face inferior (y = -1.0f)
		glColor3f(1.0f, 0.5f, 0.0f);     // Laranja
		glVertex3f(pontoLUm.x, pontoLUm.y, pontoLUm.z);
		glVertex3f(pontoLDois.x, pontoLDois.y, pontoLDois.z);
		glVertex3f(pontoLTres.x, pontoLTres.y, pontoLTres.z);
		glVertex3f(pontoLQuatro.x, pontoLQuatro.y, pontoLQuatro.z);

		// Face frontal  (z = 1.0f)
		glColor3f(1.0f, 0.0f, 0.0f);     // VeRmelho
		glVertex3f(pontoRUm.x, pontoRUm.y, pontoRUm.z);
		glVertex3f(pontoRDois.x, pontoRDois.y, pontoRDois.z);
		glVertex3f(pontoRTres.x, pontoRTres.y, pontoRTres.z);
		glVertex3f(pontoRQuatro.x, pontoRQuatro.y, pontoRQuatro.z);

		// Face traseira (z = -1.0f)
		glColor3f(1.0f, 1.0f, 0.0f);     // Amarelo
		glVertex3f(pontoAUm.x, pontoAUm.y, pontoAUm.z);
		glVertex3f(pontoADois.x, pontoADois.y, pontoADois.z);
		glVertex3f(pontoATres.x, pontoATres.y, pontoATres.z);
		glVertex3f(pontoAQuatro.x, pontoAQuatro.y, pontoAQuatro.z);

		// Face esquerda (x = -1.0f)
		glColor3f(0.0f, 0.0f, 1.0f);     //AZul
		glVertex3f(pontoZUm.x, pontoZUm.y, pontoZUm.z);
		glVertex3f(pontoZDois.x, pontoZDois.y, pontoZDois.z);
		glVertex3f(pontoZTres.x, pontoZTres.y, pontoZTres.z);
		glVertex3f(pontoZQuatro.x, pontoZQuatro.y, pontoZQuatro.z);

		// Face direita (x = 1.0f)
		glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
		glVertex3f(pontoMUm.x, pontoMUm.y, pontoMUm.z);
		glVertex3f(pontoMDois.x, pontoMDois.y, pontoMDois.z);
		glVertex3f(pontoMTres.x, pontoMTres.y, pontoMTres.z);
		glVertex3f(pontoMQuatro.x, pontoMQuatro.y, pontoMQuatro.z);
	glEnd();  // Fim do desenho do cubo

	glutSwapBuffers();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Esc
		exit(0);
		break;
	case 119: //w
		//Variavel que representa a tecla = 1
		cima = true;
		break;
	case 115: //s
		baixo = true;
		break;
	case 97: //a
		esquerda = true;
		break;
	case 100: //w
		direita = true;
		break;
	case 45: //menos
		menos = true;
		break;
	case 43: //mais
		mais = true;
		break;
	case 61: //igual (mais)
		mais = true;
		break;
	case 48: //tecla zero = reset
		reset = true;
		break;
	case 60: //menor que
		menorT = true;
		break;
	case 44: //menor que (vírgula)
		menorT = true;
		break;
	case 101: //menor que (letra e)
		menorT = true;
		break;
	case 62: //maior que
		maiorT = true;
		break;
	case 46: //maior que (ponto)
		maiorT = true;
		break;
	case 114: //maior que (letra r)
		maiorT = true;
		break;
	}
}

void keyboardOnRelease(unsigned char key, int x, int y) {
	switch (key) {
	case 119: //w
		//Variavel que representa a tecla = 0
		cima = false;
		break;
	case 115: //s
		baixo = false;
		break;
	case 97: //a
		esquerda = false;
		break;
	case 100: //w
		direita = false;
		break;
	case 45: //menos
		menos = false;
		break;
	case 43: //mais
		mais = false;
		break;
	case 61: //igual
		mais = false;
		break;
	case 48: //tecla zero = reset
		reset = false;
		break;
	case 60: //menor que
		menorT = false;
		break;
	case 44: //menor que (vírgula)
		menorT = false;
		break;
	case 101: //menor que (letra e)
		menorT = false;
		break;
	case 62: //maior que
		maiorT = false;
		break;
	case 46: //maior que (ponto)
		maiorT = false;
		break;
	case 114: //maior que (letra r)
		maiorT = false;
		break;
	}
}

void pressedSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: //Seta pra cima
		//Variavel que representa a tecla++
		cima = true;
		break;
	case GLUT_KEY_DOWN: //Seta pra baixo
		baixo = true;
		break;
	case GLUT_KEY_LEFT: //Seta pra esquerda
		esquerda = true;
		break;
	case GLUT_KEY_RIGHT: //Seta pra direita
		direita = true;
		break;
	}
}

void releasedSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: //Seta pra cima
		//Variavel que representa a tecla--
		cima = false;
		break;
	case GLUT_KEY_DOWN: //Seta pra baixo
		baixo = false;
		break;
	case GLUT_KEY_LEFT: //Seta pra esquerda
		esquerda = false;
		break;
	case GLUT_KEY_RIGHT: //Seta pra direita
		direita = false;
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("forma geometrica de seis lados");
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);

	//Entrada
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardOnRelease);
	glutSpecialFunc(pressedSpecialKeys);
	glutSpecialUpFunc(releasedSpecialKeys);

	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}