

#include "show.h"

/** Defines privados */
// Eixos cartezianos
#define XX	0
#define YY	1
#define ZZ 2
// Tipos de camera
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3

/** Variaveis globais Privadas*/
// Tipo de vista
int tipo_de_vista = PRIMEIRA_PESSOA;
// posicao do agente
GLdouble posicao[3];
// Direcao da camera
GLdouble direcao[3] = {	0.0f, 0.0f, -1.0f };

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

void scene()	{


}

/**
 * Desenha a cena
 */
void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	/* se a camara estiver para o objecto - first person
	if(tipo_de_camera == PRIMEIRA_PESSOA || tipo_de_camera == PRIMEIRA_PESSOA_NOVO)
		gluLookAt(	cam_pos[XX],			cam_pos[YY],			cam_pos[ZZ],
					cam_pos[XX]+cam_vd[XX],	cam_pos[YY]+cam_vd[YY],	cam_pos[ZZ]+cam_vd[ZZ],
					0,						1,						0);

	// se a camara estiver para o mundo - third person
	else gluLookAt(camX,camY,camZ,
					0,0,0,
					0,1,0);
	*/
	scene();
	
	glutSwapBuffers();
}

/**
 * Recebe input do teclado
 */
void recebeTeclado(unsigned char key, int ratoX, int ratoY)	{
	switch(key)	{
		case 'W':
		case 'w':
			teclas[WW] = true;
			break;
		case 'S':
		case 's':
			teclas[SS] = true;
			break;
		case 'A':
		case 'a':
			teclas[AA] = true;
			break;
		case 'D':
		case 'd':
			teclas[DD] = true;
			break;
		default:
			;
	}

}

/**
 * Funcao de inicializacao
 */
void startShow(int argc, char **argv)	{

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
	
	//criarTextura();
	glutMainLoop();

}
