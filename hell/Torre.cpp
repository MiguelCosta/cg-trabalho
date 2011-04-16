
#include "Torre.h"
#include "Torre.h"


Torre::Torre(void)
{
	posicao[XX] = 10.0f;
	posicao[YY] = 1.2f;
	posicao[ZZ] = 10.0f;
	ang = 0;
}

Torre::Torre(GLdouble posicaoInicialX, GLdouble posicaoInicialZ)
{
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 1.2f;
	posicao[ZZ] = posicaoInicialZ;
	ang = 0;
}

void Torre::desenha(void)	{
	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glRotatef(ang,0,posicao[YY],0);
		glutSolidTorus(1,5,10,10);
	glPopMatrix();
	
}

Torre::~Torre(void)
{
}
