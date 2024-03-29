

//#include <iostream>

#include "Agente.h"
#include "Input.h"
#include "defines.h"

#include <math.h>

extern bool teclas[];

Agente::Agente(void)	{
	Agente(0, 0);
	colisoes = 0;
}

Agente::Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ) {
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 0.8f;
	posicao[ZZ] = posicaoInicialZ;
	angAlpha = 0;
	angBeta = 0;
	velocidade = AGENTE_VELOCIDADE_INICIAL;
	colisoes = 0;
}

void Agente::desenhar(float posX, float posY, float posZ)	{
	//float color[] = {1.0,0.0,0.0,1.0};
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

	posicao[XX] = (GLdouble) posX;
	posicao[YY] = (GLdouble) posY + 1;
	posicao[ZZ] = (GLdouble) posZ;

	glPushMatrix();
		//glTranslatef(-1,0,0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		
		glRotatef(angAlpha * 180 / PI,0,posicao[YY],0);
		glmDraw(agente,GLM_SMOOTH|GLM_MATERIAL);
		//glutSolidTeapot(0.2);
	glPopMatrix();
	
	andar();
}

void Agente::andar(void)	{
	float vel = velocidade;
	if (teclas[CORRER])	{
		vel *= 2;
	}
	if (teclas[ANDAR_ESQ]) {
		posicao[XX] += vel * cos(angAlpha);
		posicao[ZZ] -= vel * sin(angAlpha);
	}
	if (teclas[ANDAR_DIR]) {
		posicao[XX] -= vel * cos(angAlpha);
		posicao[ZZ] += vel * sin(angAlpha);
	}
	if (teclas[ANDAR_FREN]) {
		posicao[XX] += vel * sin(angAlpha);
		posicao[ZZ] += vel * cos(angAlpha);
	}
	if (teclas[ANDAR_TRAS]) {
		posicao[XX] -= vel * sin(angAlpha);
		posicao[ZZ] -= vel * cos(angAlpha);
	}
	if(posicao[XX] >= MAPA_TAM)
		posicao[XX] = MAPA_TAM;
	if(posicao[XX] <= -MAPA_TAM)
		posicao[XX] = -MAPA_TAM;
	if(posicao[ZZ] >= MAPA_TAM)
		posicao[ZZ] = MAPA_TAM;
	if(posicao[ZZ] <= -MAPA_TAM)
		posicao[ZZ] = -MAPA_TAM;
}

float Agente::direcao(int EIXO)	{
	switch(EIXO)	{
		case XX:
			return (cos(angBeta)*sin(angAlpha));
			break;
		case YY:
			return (sin(angBeta));
			break;
		case ZZ:
			return(cos(angBeta)*cos(angAlpha));
			break;
	}
	return -1;

}

void Agente::incrementaColisao(void){
	colisoes++;
}

Agente::~Agente(void)	{

}
