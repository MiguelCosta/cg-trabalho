#include "Bala.h"
#include "Mapa.h"

extern Mapa *_mapa;

Bala::Bala(void)
{
	Bala(0,0,0);
}

Bala::Bala(GLdouble posicaoInicialX, GLdouble posicaoInicialY, GLdouble posicaoInicialZ)
{
	posicao[XX] = posicaoInicialX;
	posicao[YY] = posicaoInicialY;
	posicao[ZZ] = posicaoInicialZ; 
}

void Bala::desenha(void)	{


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
