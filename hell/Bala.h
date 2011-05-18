#pragma once
#include <GL/glut.h>


class Bala
{
public:
	/* posicao da chave */
	GLdouble posicao[3];

	Bala(void);
	/** Cria a bala recebendo a posição onde vai ser colocada*/
	Bala(GLdouble posicaoInicialX, GLdouble posicaoInicialY, GLdouble posicaoInicialZ);

	/** Desenha a chave */
	void desenha(void);

	~Bala(void);
};

