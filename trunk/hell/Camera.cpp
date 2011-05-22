
#include <math.h>
#include <GL/glut.h>

#include "Camera.h"
#include "Mapa.h"
#include "defines.h"
#include "util.h"

extern Mapa * _mapa;

float ratio = 1.0;
float direcaoCamera[3];

float cima[3], baixo[3], direira[3], esquerda[3], perto[3], longe[3];

Camera::Camera(void)	{
	tipoDeVista = TERCEIRA_PESSOA;
	
	camPosOnGodMode[XX] =  0.0;
	camPosOnGodMode[YY] = MAPA_TAM * 1.9;
	camPosOnGodMode[ZZ] = 0.1;
}

//Redimensionar a janela
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if(h == 0)
		h = 1;

	//width = w; 
	//height = h;

	ratio = 1.0 * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1.5,1000);
	glMatrixMode(GL_MODELVIEW);
}

void initFrame()	{
	
	GLfloat Hnear = 2 * 0.836777609;
	GLfloat Wnear = Hnear * ratio;
	GLfloat Hfar = 2 * 557.851739;
	GLfloat Wfar = Hfar * ratio;

	float pertoCentro[3], pertoEsqBaixo[3], pertoEsqCima[3], pertoDirBaixo[3], pertoDirCima[3];
	float longeCentro[3], longeEsqBaixo[3], longeEsqCima[3], longeDirBaixo[3], longeDirCima[3];

	pertoCentro[XX] = 
	pertoCentro[YY] = 
	pertoCentro[ZZ] = 

}
bool deveDesenhar(GLfloat centroEsfera[], GLfloat raioEsfera)	{
	bool result = false;

	return result;
}


/**
 * Desenha a cena
 */
//renderScene
void Camera::desenhar(void) {
	
	float posicao[3], direcao[3];
		posicao[XX] = _mapa->agente->posicao[XX];
		posicao[YY] = _mapa->agente->posicao[YY];
		posicao[ZZ] = _mapa->agente->posicao[ZZ];
		direcao[XX] = _mapa->agente->direcao(XX);
		direcao[YY] = _mapa->agente->direcao(YY);
		direcao[ZZ] = _mapa->agente->direcao(ZZ);

	/* se a camara estiver para o objecto - first person */
	if(tipoDeVista == PRIMEIRA_PESSOA){
		
		direcaoCamera[XX] = direcao[XX];
		direcaoCamera[YY] = direcao[YY];
		direcaoCamera[ZZ] = direcao[ZZ];
		posicaoCamera[XX] = posicao[XX];
		posicaoCamera[YY] = posicao[YY];
		posicaoCamera[ZZ] = posicao[ZZ];

		gluLookAt(	
			posicao[XX],				posicao[YY],		posicao[ZZ],
			posicao[XX]+direcao[XX],	posicao[YY]-0.2,	posicao[ZZ]+direcao[ZZ],
			0,	1,	0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){

		direcaoCamera[XX] = -CAMARA_TERCEIRA_PESSOA * direcao[XX];
		direcaoCamera[YY] = -CAMARA_3_P_YY;
		direcaoCamera[ZZ] = -CAMARA_TERCEIRA_PESSOA * direcao[XX]- CAMARA_3_P_ZZ;

		posicaoCamera[XX] = posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX];
		posicaoCamera[YY] = posicao[YY]+CAMARA_3_P_YY;
		posicaoCamera[ZZ] = posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ]-CAMARA_3_P_ZZ;

		gluLookAt(	
			posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX],		posicao[YY]+CAMARA_3_P_YY,	posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ]-CAMARA_3_P_ZZ,
			posicao[XX],										posicao[YY],		posicao[ZZ],
			0,	1,	0);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){

		direcaoCamera[XX] = 0.0;
		direcaoCamera[YY] = 0.0;
		direcaoCamera[ZZ] = 0.0;

		gluLookAt(	camPosOnGodMode[XX],camPosOnGodMode[YY],camPosOnGodMode[ZZ],
					0.0,				0.0,				0.0,
					0.0f,				1.0f,				0.0f);
	}

	float norma = distancia3d(0,0,0,direcaoCamera[XX],direcaoCamera[YY],direcaoCamera[ZZ]);
	direcaoCamera[XX] /= norma;
	direcaoCamera[YY] /= norma;
	direcaoCamera[ZZ] /= norma;

}

Camera::~Camera(void)	{

}
