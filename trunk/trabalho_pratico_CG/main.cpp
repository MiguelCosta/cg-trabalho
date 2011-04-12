#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define ARVORES 5000

#define XX 0
#define YY 1
#define ZZ 2

// local camera position
GLdouble cam_pos[]={0.0, 1.2,20};
// local camera view direction
GLdouble cam_vd[]={0.0, 0.0, -1.0};
// camera orientation angle
int startX, startY, tracking = 0;
int alpha = 0, beta = 0, r = 5;
float camX = 0, camY, camZ = 5;

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

void fps()	{


	step=0;
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

	float r = 10;
	float alpha;
	float rr;
	float x,z;

	srand(31457);
	int arvores = 0;

	while (arvores < ARVORES) {

		rr = rand() * 2000.0/ RAND_MAX;
		alpha = rand() * 6.28 / RAND_MAX;

		x = cos(alpha) * (rr + r);
		z = sin(alpha) * (rr + r);

		if (fabs(x) < 2000 && fabs(z) < 2000) {

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


void scene() {

	drawPlane();
	placeTrees();
	drawBoneco();

}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	

	if(cam_local) gluLookAt(cam_pos[0],cam_pos[1],cam_pos[2],
							cam_pos[0]+cam_vd[0],cam_pos[1]+cam_vd[1],cam_pos[2]+cam_vd[2],
							0,1,0);
	
	else gluLookAt(camX,camY,camZ,
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
		case '1':  cam_local= !cam_local;
			
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
		case 'a': cam_alpha -= 0.05;
				    cam_vd[XX] = sin(cam_alpha); 		  
     				    cam_vd[ZZ] = -cos(cam_alpha);			  
				    break;
		default: 
			break;
	}
	glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) 
{
   if (state == GLUT_DOWN)  {
      startX = xx;
      startY = yy;
      if (button == GLUT_LEFT_BUTTON)
         tracking = 1;
      else if (button == GLUT_RIGHT_BUTTON)
         tracking = 2;
      else
         tracking = 0;
   }
   else if (state == GLUT_UP) {
      if (tracking == 1) {
         alpha += (xx - startX);
         beta += (yy - startY);
      }
      else if (tracking == 2) {
         
         r -= yy - startY;
         if (r < 20)
            r = 20.0;
      }
      tracking = 0;
   }

   
}


void processMouseMotion(int xx, int yy)
{

   int deltaX, deltaY;
   int alphaAux, betaAux;
   int rAux;

   if (!tracking)
      return;

   deltaX = xx - startX;
   deltaY = yy - startY;

   if (tracking == 1) {


      alphaAux = alpha + deltaX;
      betaAux = beta + deltaY;

      if (betaAux > 85.0)
         betaAux = 85.0;
      else if (betaAux < -85.0)
         betaAux = -85.0;

      rAux = r;
   }
   else if (tracking == 2) {

      alphaAux = alpha;
      betaAux = beta;
      rAux = r - deltaY;
      if (rAux < 3)
         rAux = 3;
   }
   camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
   camY = rAux *                          sin(betaAux * 3.14 / 180.0);


}

void special_kb(int key, int x, int y) {
	switch (key) {
		
	}

}

int main(int argc, char **argv) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho Patra de CG");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc(special_kb);
	//glutMouseFunc(mouse);
	glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glutMainLoop();
	return 0;
}