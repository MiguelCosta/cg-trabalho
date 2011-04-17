#include "Chave.h"

Chave::Chave(void)
{
	posicao[XX] = 10.0f;
	posicao[YY] = 1.2f;
	posicao[ZZ] = 10.0f;
}

Chave::Chave(GLdouble posicaoInicialX, GLdouble posicaoInicialZ){
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 1.2f;
	posicao[ZZ] = posicaoInicialZ;
}

void Chave::desenha(void)	{
	float color[] = {0.0,1.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glutSolidTorus(1,5,10,10);
	glPopMatrix();
	
}

Chave::~Chave(void)
{
}
