#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <string.h>
//#include "glm.h"
#include "view.h"

#include "mapa.h"

#define _PI_ 3.14159

Mapa *_mapa;


//Redimensionar a janela
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


//Desenha os eixos
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



int main(int argc, char **argv) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho CG");
	
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keybord_special);

	glutPassiveMotionFunc(ratoPassivo);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	//glutPassiveMotionFunc(funcaoRato);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Codigo do programa
	_mapa = new Mapa();
	
	
	//criarTextura();
	glutMainLoop();
	return 0;
}