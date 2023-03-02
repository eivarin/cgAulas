#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices) {
	float aCil = 0;
	float rotation = (2 * M_PI);
	float delta = rotation / slices;
	height = height / 2;
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_TRIANGLES);
	while (aCil <= rotation) {
		glColor3f(1.0f,0.0f,0.0f);
		float px1 = radius * sin(aCil), py1 = radius * cos(aCil);
		float px2 = radius * sin(aCil+delta), py2 = radius * cos(aCil+delta);
		
		glVertex3f(0.0f, height, 0.0f);
		glVertex3f(px1, height, py1);
		glVertex3f(px2, height, py2);
		

		glVertex3f(px1, height, py1);
		glVertex3f(px1, -height, py1);
		glVertex3f(px2, -height, py2);
		
		glVertex3f(px1, height, py1);
		glVertex3f(px2, -height, py2);
		glVertex3f(px2, height, py2);

		glVertex3f(0.0f, -height, 0.0f);
		glVertex3f(px2, -height, py2);
		glVertex3f(px1, -height, py1);
		aCil+=delta;
	}
	glEnd();
}

int ai = 0;
int bi = 0;
int steps = 16;
float r = 5.0f;

float px = 0.0f;
float py = 0.0f;
float pz = 0.0f;


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	float step = (M_PI / (steps*2));
	float a = ai * step;
	float b = bi * step;
	gluLookAt(px, py, pz, 
		      r * cos(b) * sin(a),r * sin(b),r * cos(b) * cos(a),
			  0.0f,1.0f,0.0f);

	drawCylinder(1,2,10);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c)
	{
	case 'w':
		bi = ((bi + 1) < steps) ? bi += 1 : bi;
		break;
	case 's':
		bi = ((bi - 1) > -steps) ? bi -= 1 : bi;
		break;

	case 'a':
		ai -= 1;
		break;

	case 'd':
		ai += 1;
		break;
	
	default:
		break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {
	switch (key)
	{
	case GLUT_KEY_UP:
		pz += 1; 
		break;
	case GLUT_KEY_DOWN:
		pz -= 1; 
		break;

	case GLUT_KEY_LEFT:
		px -= 1;
		break;

	case GLUT_KEY_RIGHT:
		px += 1;
		break;
	
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
