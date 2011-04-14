#include "Edificio.h"


Edificio::Edificio(void)
{


	posicao[0]=0.0;
	posicao[1]=0.0;
	posicao[2]=0.0;
}

Edificio::Edificio(GLdouble posX, GLdouble posZ ){

	posicao[0]=posX;
	posicao[1]=altura;
	posicao[2]=posZ;
}

Edificio::~Edificio(void)
{
}
