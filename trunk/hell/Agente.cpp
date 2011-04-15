
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
	glColor3f(0.98, 0.01, 0.3);
	glutSolidTeapot(50);
}

void Agente::andar(void)	{


}
Agente::~Agente(void)	{

}
