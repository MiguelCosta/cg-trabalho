
#include "Agente.h"


Agente::Agente(void)	{
	posicao[0] = 0.0f;
	posicao[1] = 1.2f;
	posicao[2] = 0.0f;
}

Agente::Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ)	{
	posicao[0] = posicaoInicialX;
	posicao[1] = 1.2f;
	posicao[2] = posicaoInicialZ;
}

void Agente::desenhar(void)	{
	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
		
	glPushMatrix();
		glutSolidTeapot(1);
	glPopMatrix();
	
}

void Agente::andar(void)	{


}
Agente::~Agente(void)	{

}
