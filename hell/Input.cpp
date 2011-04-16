
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "Input.h"
#include "defines.h"
#include "Camera.h"
#include "Mapa.h"


extern Mapa * _mapa;


//NOVO
int mouse_left_clicked = GLUT_UP;
float camX = 0.0f, camY = 0.0f, camZ = 7.0f;

/* Cenas para o rato! */
float startX, startY, tracking = 0;
int alpha = 0, beta = 0, r = 5.0;

extern Camera * _camera;
extern bool teclas[];

void processarTecladoEspecialDown(int key, int x, int y)	{
	switch (key)	{
		case GLUT_KEY_LEFT:
			teclas[ANDAR_ESQ] = true;
			break;
		case GLUT_KEY_RIGHT:
			teclas[ANDAR_DIR] = true;
			break;
		case GLUT_KEY_UP:
			teclas[ANDAR_FREN] = true;
			break;
		case GLUT_KEY_DOWN:
			teclas[ANDAR_TRAS] = true;
			break;
	}
}

void processarTecladoEspecialUp(int key, int x, int y)	{
	switch (key)	{
		case GLUT_KEY_LEFT:
			teclas[ANDAR_ESQ] = false;
			break;
		case GLUT_KEY_RIGHT:
			teclas[ANDAR_DIR] = false;
			break;
		case GLUT_KEY_UP:
			teclas[ANDAR_FREN] = false;
			break;
		case GLUT_KEY_DOWN:
			teclas[ANDAR_TRAS] = false;
			break;
	}
}

void processarTecladoDown	(unsigned char key, int x, int y)	{
	
	switch(key) {
		case 27:   // ESCape, fechar a janela
			exit (0);
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
}

void processarTecladoUp		(unsigned char key, int x, int y)	{
	switch (key)	{
		// Andar
		case 'W':
		case 'w':
			teclas[ANDAR_FREN] = false;
			break;
		case 'S':
		case 's':
			teclas[ANDAR_TRAS] = false;
			break;
		case 'D':
		case 'd':
			teclas[ANDAR_DIR] = false;
		    break;
		case 'A':
		case 'a':
			teclas[ANDAR_ESQ] = false;
			break;
	}
}


void processMouseButtons(int button, int state, int xx, int yy)		{
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
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}

	
}


void processMouseMotion(int xx, int yy)	{

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
	
	_camera->camPosOnGodMode[XX] = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	_camera->camPosOnGodMode[ZZ] = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	_camera->camPosOnGodMode[YY] = rAux * 							     sin(betaAux * 3.14 / 180.0);

	_camera->camPosPrimeiraPessoa[XX] = (rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0))- _mapa->agente->posicao[XX];
	_camera->camPosPrimeiraPessoa[ZZ] = (rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0))- _mapa->agente->posicao[ZZ];
	_camera->camPosPrimeiraPessoa[YY] = (rAux * 							     sin(betaAux * 3.14 / 180.0))- _mapa->agente->posicao[YY];

}

