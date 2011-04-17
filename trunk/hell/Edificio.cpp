#include "Edificio.h"
#include "defines.h"

Edificio::Edificio(void)
{
	posicao[XX] = 0;
	posicao[YY] = 10.0f;
	posicao[ZZ] = -(MAPA_TAM);
}

Edificio::Edificio(GLdouble posicaoInicialX, GLdouble posicaoInicialZ){
	posicao[XX] = 10.0f;
	posicao[YY] = 10.0f;
	posicao[ZZ] = 10.0f;

}

void Edificio::desenhar(void)	{
	float color[] = {0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glutSolidTeapot(10);
	glPopMatrix();
	
}

Edificio::~Edificio(void)
{
}
