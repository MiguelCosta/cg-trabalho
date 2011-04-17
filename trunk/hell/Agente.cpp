

#include <iostream>

#include "Agente.h"
#include "Input.h"
#include "defines.h"

#include <math.h>

extern bool teclas[];

Agente::Agente(void)	{
	Agente(0, 0);
	//posicao[0] = 0.0f;
	//posicao[1] = 1.2f;
	//posicao[2] = 0.0f;
	//ang = 0;
	//svelocidade = 1.5;
}

Agente::Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ) {
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 1.2f;
	posicao[ZZ] = posicaoInicialZ;
	angAlpha = 0;
	angBeta = 0;
	velocidade = AGENTE_VELOCIDADE_INICIAL;
}

void Agente::desenhar(void)	{
	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glRotatef(angAlpha * 180 / PI,0,posicao[YY],0);
		glutSolidTeapot(0.2);
	glPopMatrix();
	
	andar();
}

void Agente::andar(void)	{
	if (teclas[ANDAR_ESQ]) {
		posicao[XX] += velocidade * cos(angAlpha);
		posicao[ZZ] -= velocidade * sin(angAlpha);
	}
	if (teclas[ANDAR_DIR]) {
		posicao[XX] -= velocidade * cos(angAlpha);
		posicao[ZZ] += velocidade * sin(angAlpha);
	}
	if (teclas[ANDAR_FREN]) {
		posicao[XX] += velocidade * sin(angAlpha);
		posicao[ZZ] += velocidade * cos(angAlpha);
	}
	if (teclas[ANDAR_TRAS]) {
		posicao[XX] -= velocidade * sin(angAlpha);
		posicao[ZZ] -= velocidade * cos(angAlpha);
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
			return (cos(angBeta));
			break;
		case ZZ:
			return(cos(angBeta)*cos(angAlpha));
			break;
	}

}

Agente::~Agente(void)	{

}
