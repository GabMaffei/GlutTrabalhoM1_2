#include <GL/freeglut.h>
using namespace std;

struct XYZ
{
	float x;
	float y;
	float z;
};

bool quit = false;

float diffuseLight[] ={ 0.8f, 0.8f, 0.8f, 1.0f };
float specularLight[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
float LightPosition[] ={ 0.0f, 100.0f, 0.0f, 1.0f };
float local_view[] ={ 0.0 };

float theta = 0.0f;
float thetaup = 0.0f;
float smallest_y = 0.0f;

int w = 600;
int h = 600;

int t, p;

void drawpolyshape()
{

	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-10.0f, smallest_y, 10.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(10.0f, smallest_y, 10.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(10.0f, smallest_y, -10.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-10.0f, smallest_y, -10.0f);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-10.0f, smallest_y, -10.0f);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(10.0f, smallest_y, -10.0f);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(10.0f, smallest_y, 10.0f);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-10.0f, smallest_y, 10.0f);
	glEnd();
}

//------------------------------------------------------------	Reshape()
void OnReshape(int w, int h)
{
	// prevent a division by zero when minimising the window
	if (h == 0) h = 1;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just use a perspective projection
	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

//------------------------------------------------------------	Draw()
//
void OnDraw()
{
	if (theta >= 360.0f)
		theta = 0.0f;

	theta += 0.1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0f, 15.0f, 30.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	drawpolyshape();

	glutSwapBuffers();
	glutPostRedisplay();
}

//------------------------------------------------------------	OnInit()
//
void OnInit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);// Clear the buffer to this color.
	glShadeModel(GL_FLAT);

	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); // Enable lighting.

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	// Set light information
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	// Enable light
	glEnable(GL_LIGHT0);

	// Set up the material information for objects
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
}

//------------------------------------------------------------	OnExit()
//
void OnExit()
{
}

//------------------------------------------------------------	main()
//
int main(int argc, char** argv)
{

	// initialise glut
	glutInit(&argc, argv);

	// request a depth buffer, RGBA display mode, and we want double buffering
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);

	// set the initial window size
	glutInitWindowSize(640, 480);

	// create the window
	glutCreateWindow("A basic glut example");

	// set the function to use to draw our scene
	glutDisplayFunc(OnDraw);

	// set the function to handle changes in screen size
	glutReshapeFunc(OnReshape);

	// run our custom initialisation
	OnInit();

	// set the function to be called when we exit
	atexit(OnExit);

	// this function runs a while loop to keep the program running.
	glutMainLoop();
	return 0;
}
