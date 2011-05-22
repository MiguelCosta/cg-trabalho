#include "Edificio.h"
#include "defines.h"
#include <stdio.h>

Edificio::Edificio(void)
{
	posicao[XX] = 0;
	posicao[YY] = 0.1f;
	posicao[ZZ] = -(MAPA_TAM);
}

Edificio::Edificio(GLdouble posicaoInicialX, GLdouble posicaoInicialZ){
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 1.0f;
	posicao[ZZ] = posicaoInicialZ;

}

void Edificio::desenhar(float posX, float posY, float posZ)	{

	posicao[XX] = (GLdouble) posX;
	posicao[YY] = (GLdouble) posY;
	posicao[ZZ] = (GLdouble) posZ;

	//float color[] = {0.0,0.0,1.0};
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		//glutSolidTeapot(4);
		//glScalef(5,5,5);
		glmDraw(edificio,GLM_SMOOTH|GLM_MATERIAL);
	glPopMatrix();
	
}

Edificio::~Edificio(void)
{
}
