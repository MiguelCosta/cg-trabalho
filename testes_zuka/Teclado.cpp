#include "Teclado.h"

#define char ANDARFRENTE;


Teclado::Teclado(void)
{
}


Teclado::~Teclado(void)
{
}

void Teclado::recebeTeclado(unsigned char key, int x, int y){
	switch(key) {
		case 27:   // ESCape, fechar a janela
			exit (0);
			break;

		// alterar o modo da camara
		case '1': 
				break;

		// alterar a posição da camara
		case 'w': 
		case 'W':

			break;


		case 's': 
		case 'S':

			break;

		case 'd':
		case 'D':

		    break;

		case 'a':
		case 'A' 

			break;

		default: 
			break;
	}
	glutPostRedisplay();
}