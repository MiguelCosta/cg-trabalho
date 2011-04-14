#include "Teclado.h"

#define ANDAR_FREN	0
#define ANDAR_TRAS	1
#define ANDAR_DIR	2
#define ANDAR_ESQ	3



void recebeTeclado(unsigned char key, int x, int y){
	switch(key) {
		case 27:   // ESCape, fechar a janela
			//exit (0);
			break;

		// alterar o modo da camara
		case '1':
			_camera->tipoDeVista = PRIMEIRA_PESSOA;
			break;
		// alterar o modo da camara
		case '2':
			_camera->tipoDeVista = TERCEIRA_PESSOA;
			break;
		// alterar o modo da camara
		case '3':
			_camera->tipoDeVista = MODO_DEUS;
			break;

		// Andar
		case 'W':
		case 'w':
			teclas[ANDAR_FREN] = true;
			break;
		case 'S':
		case 's':
			teclas[ANDAR_TRAS] = true;
			break;
		case 'D':
		case 'd':
			teclas[ANDAR_DIR] = true;
		    break;
		case 'A':
		case 'a':
			teclas[ANDAR_ESQ] = true;
			break;
	}
	glutPostRedisplay();
}