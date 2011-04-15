
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
	ang = 0;
	velocidade = 1.5;
}

void Agente::desenhar(void)	{
	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	andar();

	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glutSolidTeapot(1);
	glPopMatrix();
	
}

void Agente::andar(void)	{
	if (teclas[ANDAR_ESQ]) {
		posicao[XX] -= velocidade * cos(ang);
		posicao[ZZ] += velocidade * sin(ang);
	}
	if (teclas[ANDAR_DIR]) {
		posicao[XX] += velocidade * cos(ang);
		posicao[ZZ] -= velocidade * sin(ang);
	}
	if (teclas[ANDAR_FREN]) {
		posicao[XX] -= velocidade * sin(ang);
		posicao[ZZ] -= velocidade * cos(ang);
	}
	if (teclas[ANDAR_TRAS]) {
		posicao[XX] += velocidade * sin(ang);
		posicao[ZZ] += velocidade *cos(ang);
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

Agente::~Agente(void)	{

}
