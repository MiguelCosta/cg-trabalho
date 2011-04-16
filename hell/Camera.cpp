
#include <GL/glut.h>
#include "Camera.h"
#include "Mapa.h"
#include "defines.h"

extern Mapa * _mapa;

Camera::Camera(void)	{
	tipoDeVista = MODO_DEUS;
	/*direcao[XX] = 0.0f;
	direcao[YY] = -1.0f;
	direcao[ZZ] = 0.0f;*/
	camPosOnGodMode[XX] =  0.0;
	camPosOnGodMode[YY] = 30.0;
	camPosOnGodMode[ZZ] = 40.0;
}

/**
 * Desenha a cena
 */
//renderScene
void Camera::desenhar(void) {
	
	/* se a camara estiver para o objecto - first person */
	if(tipoDeVista == PRIMEIRA_PESSOA){
		//printf("X: %lf\tY: %lf\tZ: %lf\n",_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY],	_mapa->agente->posicao[ZZ]);
		gluLookAt(	
			_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY],	_mapa->agente->posicao[ZZ],
			_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY]+0.1,	_mapa->agente->posicao[ZZ]-1,
			0,	1,	0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){
		gluLookAt(	
			_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY],	(_mapa->agente->posicao[ZZ]+1.5),
			_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY]+0.1,	_mapa->agente->posicao[ZZ],
			0,	1,	0);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){
		//printf("X: %lf\tY: %lf\tZ: %lf\n",_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY],	_mapa->agente->posicao[ZZ]);
		gluLookAt(	camPosOnGodMode[XX],camPosOnGodMode[YY],camPosOnGodMode[ZZ],
					0.0,				0.0,				0.0,
					0.0f,				1.0f,				0.0f);
	}

}

Camera::~Camera(void)	{

}
