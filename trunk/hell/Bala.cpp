#include "Bala.h"
#include "Mapa.h"

extern Mapa *_mapa;

Bala::Bala(void)
{
	Bala(0,0,0,0);
}

Bala::Bala(GLdouble posicaoInicialX, GLdouble posicaoInicialY, GLdouble posicaoInicialZ, GLdouble angTorre)
{
	posicao[XX] = posicaoInicialX;
	posicao[YY] = posicaoInicialY;
	posicao[ZZ] = posicaoInicialZ;
	ang = (angTorre*PI)/180;
}

void Bala::desenha(void)
{
		
	posicao[XX] = posicao[XX] + 10*cos(ang);
	posicao[ZZ] = posicao[ZZ] + 10*sin(ang);

	/*
	posicao[XX] = pTorre[XX] + i * 10 * cos(ang);
	posicao[ZZ] = pTorre[ZZ] + i * 10 * sin(ang);
	*/
	float color[] = {0.0,0.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

	glPushMatrix();
	glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
	// desenha um cone
	glutSolidCone(1,2,5,5);
	glPopMatrix();
	
}


Bala::~Bala(void)
{
}
