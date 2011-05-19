#pragma once
#include <GL/glut.h>


class Bala
{
private:
	/* posicao da chave */
	GLdouble posicao[3];
	GLdouble pTorre[3];
	GLdouble ang;
	
public:
	Bala(void);
	/** Cria a bala recebendo a posição onde vai ser colocada*/
	Bala(GLdouble posicaoInicialX, GLdouble posicaoInicialY, GLdouble posicaoInicialZ, GLdouble angTorre);

	/** Desenha a chave */
	void desenha(void);

	~Bala(void);
};

