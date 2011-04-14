
#include "main.h"

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
	
	// OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1024,1024);
	glutCreateWindow("Trabalho CG");
	
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	
	glutKeyboardFunc(recebeTeclado);
	//glutSpecialFunc(keybord_special);

	glutPassiveMotionFunc();
	//glutMouseFunc(processMouseButtons);
	//glutMotionFunc(processMouseMotion);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	//	codigo...
	//posicao[XX] = _mapa.

	//criarTextura();
	glutMainLoop();
	return 0;
}