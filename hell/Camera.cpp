
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

	camPosPrimeiraPessoa[XX]= 0.0;
	camPosPrimeiraPessoa[YY]= 0.0;
	camPosPrimeiraPessoa[ZZ]= 0.0;
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
		//printf("X: %lf\tY: %lf\tZ: %lf\n",_mapa->agente->posicao[XX],	_mapa->agente->posicao[YY],	_mapa->agente->posicao[ZZ]);
		gluLookAt(	
			posicao[XX],				posicao[YY],				posicao[ZZ],
			posicao[XX]+direcao[XX],	posicao[YY]+0.3,	posicao[ZZ]+direcao[ZZ],
			0,	1,	0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){

		gluLookAt(	
			posicao[XX]-1.5*direcao[XX],	posicao[YY]+0.3,	posicao[ZZ]-1.5 * direcao[ZZ],
			posicao[XX],					posicao[YY],		posicao[ZZ],
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
