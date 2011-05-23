
#include <GL/glut.h>
#include "Camera.h"
#include "Mapa.h"
#include "defines.h"
#include "Plano.h"
#include "util.h"

extern Mapa * _mapa;

float ratio = 1.0;
Vec3 direcaoCamera, posicaoCamera;

Plano cima, baixo, direita, esquerda, perto, longe;

Camera::Camera(void)	{
	tipoDeVista = TERCEIRA_PESSOA;
	
	camPosOnGodMode[XX] =  0.0;
	camPosOnGodMode[YY] = MAPA_TAM*1.9;
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
	
	GLfloat Hperto = 2 * 0.414213562373095 * 1.5;
	GLfloat Wperto = Hperto * ratio;
	GLfloat Hlonge = 2 * 0.414213562373095 * 1000;
	GLfloat Wlonge = Hlonge * ratio;

	Vec3 pertoCentro, pertoEsqBaixo, pertoEsqCima, pertoDirBaixo, pertoDirCima;
	Vec3 longeCentro, longeEsqBaixo, longeEsqCima, longeDirBaixo, longeDirCima;
	Vec3 up(0,1,0),dir;
	dir = direcaoCamera * up;

	pertoCentro = posicaoCamera + direcaoCamera * 1.5;
	longeCentro = posicaoCamera + direcaoCamera * 1000;

	pertoEsqCima = pertoCentro + up * Hperto;
	pertoEsqCima = pertoEsqCima - dir * Wperto;

	pertoDirCima = pertoCentro + up * Hperto;
	pertoDirCima = pertoDirCima + dir * Wperto;

	pertoEsqBaixo = pertoCentro - up * Hperto;
	pertoEsqBaixo = pertoEsqBaixo - dir * Wperto;

	pertoDirBaixo = pertoCentro - up * Hperto;
	pertoDirBaixo = pertoCentro + dir * Wlonge;

    longeEsqCima = longeCentro + up * (Hlonge / 2);
	longeEsqCima = longeEsqCima - dir * (Wlonge /2);
	
	longeDirCima = longeCentro + up * (Hlonge / 2);
	longeDirCima = longeDirCima + dir * Wlonge;

	longeEsqBaixo = longeCentro - up * (Hlonge / 2);
	longeEsqBaixo = longeEsqBaixo - dir * Wlonge;

	longeDirBaixo = longeCentro - up * Hlonge;
	longeDirBaixo = longeDirBaixo + dir * Wlonge;

	cima.set3pontos(pertoDirCima, pertoEsqCima, longeDirCima);
	baixo.set3pontos(pertoDirBaixo, pertoEsqBaixo, longeDirBaixo);
	direita.set3pontos(pertoDirBaixo, longeDirBaixo, pertoDirCima);
	esquerda.set3pontos(pertoEsqBaixo, pertoEsqCima, longeEsqBaixo);
	perto.set3pontos(pertoDirBaixo, pertoDirCima, pertoEsqBaixo);
	longe.set3pontos(longeDirBaixo,longeDirCima, longeEsqBaixo);
}

bool deveDesenhar(Vec3 centroEsfera, float raioEsfera)	{

	if(    direita.dist(centroEsfera)	> raioEsfera //&& direita.dist(centroEsfera) 
		&& esquerda.dist(centroEsfera)	> raioEsfera //&& 1
		&& baixo.dist(centroEsfera)		> raioEsfera //&& 1
		&& cima.dist(centroEsfera)		> raioEsfera //&& 1
		&& perto.dist(centroEsfera)		> raioEsfera //&& 1
		&& longe.dist(centroEsfera)		> raioEsfera //&& 1
		)
		return false;
	return true;
	/*for(int i=0; i < 6; i++) {
		distance = pl[i].distance(p);
		if (distance < -radius)
			return OUTSIDE;
		else if (distance < radius)
			result = INTERSECT;
		}
	return(result); */
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
		posicaoCamera.set(posicao[XX], posicao[YY], posicao[ZZ]);
		direcaoCamera.set(direcao[XX], -0.2+direcao[YY], direcao[ZZ]);

		gluLookAt(	
			posicao[XX],				posicao[YY],		posicao[ZZ],
			posicao[XX]+direcao[XX],	posicao[YY]-0.2+direcao[YY],	posicao[ZZ]+direcao[ZZ],
			0,	1,	0);
	
	// se a camara estiver para o mundo - third person
	} else if(tipoDeVista == TERCEIRA_PESSOA){
		
		float posX = posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX];
		float posY = posicao[YY]+CAMARA_3_P_YY;
		float posZ = posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ];
		gluLookAt(      
			posX,   posY,   posZ,
			posX+direcao[XX],       posY+direcao[YY],       posZ+direcao[ZZ],
			0,	1,	0);

		//posicaoCamera.set( posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX], posicao[YY]+CAMARA_3_P_YY, posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ]-CAMARA_3_P_ZZ);
		/*gluLookAt(
			posicaoCamera.getX(),	posicaoCamera.getY(),	posicaoCamera.getZ(),
			direcaoCamera.getX(),	direcaoCamera.getZ(),	direcaoCamera.getZ(),
			0,	1,	0);*/

		posicaoCamera.setX(posX);//posicao[XX]-CAMARA_TERCEIRA_PESSOA*direcao[XX]);
		posicaoCamera.setY(posY);//posicao[YY]+CAMARA_3_P_YY);
		posicaoCamera.setZ(posZ);//posicao[ZZ]-CAMARA_TERCEIRA_PESSOA * direcao[ZZ]);

		direcaoCamera.set(posX+direcao[XX], posY+direcao[YY], posZ+direcao[ZZ]);
	}
	// se a camara estiver em modo deus
	else if(tipoDeVista == MODO_DEUS){

		direcaoCamera.set( 0.0, 0.0, 0.0);
		posicaoCamera.set( camPosOnGodMode[XX], camPosOnGodMode[YY], camPosOnGodMode[ZZ]);

		gluLookAt(	camPosOnGodMode[XX],camPosOnGodMode[YY],camPosOnGodMode[ZZ],
					0.0,				0.0,				0.0,
					0.0f,				1.0f,				0.0f);
	}

	direcaoCamera.normalize();
}

Camera::~Camera(void)	{

}
