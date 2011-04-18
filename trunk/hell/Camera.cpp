
#include <GL/glut.h>
#include "Camera.h"
#include "Mapa.h"
#include "defines.h"

extern Mapa * _mapa;

Camera::Camera(void)	{
	tipoDeVista = TERCEIRA_PESSOA;
	
	camPosOnGodMode[XX] =  0.0;
	camPosOnGodMode[YY] = MAPA_TAM*1.9;
	camPosOnGodMode[ZZ] = 0.1;
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
		
		gluLookAt(	
			posicao[XX],				posicao[YY],		posicao[ZZ],
			posicao[XX]+direcao[XX],	posicao[YY]-0.2,	posicao[ZZ]+direcao[ZZ],
			0,	1,	0);
		}
	// se a camara estiver para o mundo - third person
	else if(tipoDeVista == TERCEIRA_PESSOA){

		gluLookAt(	
			posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX],		posicao[YY]+CAMARA_3_P_YY,	posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ]-CAMARA_3_P_ZZ,
			posicao[XX],										posicao[YY],		posicao[ZZ],
			0,	1,	0);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){
		gluLookAt(	camPosOnGodMode[XX],camPosOnGodMode[YY],camPosOnGodMode[ZZ],
					0.0,				0.0,				0.0,
					0.0f,				1.0f,				0.0f);
	}

}

Camera::~Camera(void)	{

}
