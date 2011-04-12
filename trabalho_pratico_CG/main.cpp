#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define COWBOYS 8
#define RAIO_COWBOYS 5
#define INDIOS 16
#define RAIO_INDIOS 25
#define ARVORES 300
#define STEP_COWBOY 1.0f
#define STEP_INDIO 0.5f

#define XX 0
#define YY 1
#define ZZ 2

// local camera position
GLdouble cam_pos[]={0.0, 1.2, (GLdouble)(RAIO_INDIOS+20)};
// local camera view direction
GLdouble cam_vd[]={0.0, 0.0, -1.0};
// camera orientation angle
float cam_alpha=0.0;

bool cam_local=false; // switch between camera local to agent and high camera

float step = 0.0;
float delta = 1;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if(h == 0)
		h = 1;

	//width = w; 
	//height = h;

	float ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1.5,1000);
	glMatrixMode(GL_MODELVIEW);
}

void drawAxis() {
   glBegin(GL_LINES);
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(100.0, 0.0, 0.0);

	  glColor3f(0.0, 1.0, 0.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 100.0, 0.0);
      
	  glColor3f(0.0, 0.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);
      glVertex3f(0.0, 0.0, 100.0);
   glEnd();
}

void drawTree() {

	glPushMatrix();
	glRotatef(-90,1.0,0.0,0.0);
	glColor3f(1.0,1.0,0.5);
	glutSolidCone(0.25,4,8,1);
	glColor3f(0.0,1.0,0.0);
	glTranslatef(0.0,0.0,2.0);
	glutSolidCone(2.0,5.0,8,1);
	glPopMatrix();
}

void placeTrees() {

	float r = 35.0;
	float alpha;
	float rr;
	float x,z;

	srand(31457);
	int arvores = 0;

	while (arvores < ARVORES) {

		rr = rand() * 70.0/ RAND_MAX;
		alpha = rand() * 6.28 / RAND_MAX;

		x = cos(alpha) * (rr + r);
		z = sin(alpha) * (rr + r);

		if (fabs(x) < 100 && fabs(z) < 100) {

			glPushMatrix();
			glTranslatef(x,0.0,z);
			drawTree();
			glPopMatrix();
			arvores++;
		}
	}
}

void drawPlane() {

	glColor3f(0.5,0.75,0.0);
	glBegin(GL_QUADS);
		glVertex3f(-2000.0, 0.0, 2000.0);
		glVertex3f( 2000.0, 0.0, 2000.0);
		glVertex3f( 2000.0, 0.0,-2000.0);
		glVertex3f(-2000.0, 0.0,-2000.0);
	glEnd();
}

void drawBoneco() {

	glPushMatrix();
	glTranslatef(0.0,2,0.0);
	glColor3f(0.0,0.5,1.0);
	glutSolidTeapot(2);
	//glutSolidTorus(0.5,1.25,8,16);
	glPopMatrix();
}

void drawIndios() {

	float angulo;
	glColor3f(1.0,0.0,0.0);
	for (int i = 0; i < INDIOS; i++) {
		
		angulo = i * 360.0/INDIOS + step * STEP_INDIO;
		glPushMatrix();
		glRotatef(angulo,0.0,1.0,0.0);
		glTranslatef(0.0,1.0,RAIO_INDIOS);
		glColor3d(1,0,0);
		glutSolidTeapot(1);
		glPopMatrix();
	}
}

void drawCowboys() {

	float angulo;
	glColor3f(0.0,0.0,1.0);
	for (int i = 0; i < COWBOYS; i++) {
		
		angulo = i * 360.0/COWBOYS + step * STEP_COWBOY;
		glPushMatrix();
		glRotatef(-angulo,0.0,1.0,0.0);
		glTranslatef(RAIO_COWBOYS,1.0,0.0);
		glColor3d(0,0,1);
		glutSolidTeapot(1);
		glPopMatrix();
	}
}

void scene() {

	drawPlane();
	placeTrees();
	drawBoneco();

	//drawCowboys();
	//drawIndios();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	

	if(cam_local) gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],
							cam_pos[0]+cam_vd[0],cam_pos[1]+cam_vd[1],cam_pos[2]+cam_vd[2],
							0,1,0);
	else gluLookAt(200,100,200,
					0,0,0,
					0,1,0);
	drawAxis();
	scene();
	step++;

	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 27:   // ESCape
			exit (0);
			break;
		case 'c':  cam_local= !cam_local;
			
		default:
			break;
	}
	glutPostRedisplay();
}


void special_kb(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: cam_pos[0] = cam_pos[0] + cam_vd[0]*delta;
				  cam_pos[1] = cam_pos[1] + cam_vd[1]*delta;
				  cam_pos[2] = cam_pos[2] + cam_vd[2]*delta;				  
				  break;
		case GLUT_KEY_DOWN: cam_pos[0] = cam_pos[0] - cam_vd[0]*delta;
				    cam_pos[1] = cam_pos[1] - cam_vd[1]*delta;
				    cam_pos[2] = cam_pos[2] - cam_vd[2]*delta;				  
				    break;
		//se a camara rodar com as setas
		case GLUT_KEY_RIGHT: cam_alpha += 0.05;
				     cam_vd[XX] = sin(cam_alpha); 		  
     				     cam_vd[ZZ] = -cos(cam_alpha);
				     break;
		case GLUT_KEY_LEFT: cam_alpha -= 0.05;
				    cam_vd[XX] = sin(cam_alpha); 		  
     				    cam_vd[ZZ] = -cos(cam_alpha);			  
				    break;
		default: 
			break;
	}

}

int main(int argc, char **argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("CG@DI-UM");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc(special_kb);
	//glutMouseFunc(mouse);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
	return 0;
}