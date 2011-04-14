
#include "main.h"


void renderScene(void)	{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	_camera->desenhar();
	_agente->desenhar();
	_mapa->desenhar();
	
	glutSwapBuffers();
}


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



int main(int argc, char **argv) {

	
	// Codigo do programa
	_mapa = new Mapa();
	_camera = new Camera();

	
	// OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho CG");
	
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
//	glutKeyboardFunc(Teclado::recebeTeclado);
	//glutSpecialFunc(keybord_special);

	glutPassiveMotionFunc(mover);
	//glutMouseFunc(processMouseButtons);
	//glutMotionFunc(processMouseMotion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//criarTextura();
	glutMainLoop();
	return 0;
}