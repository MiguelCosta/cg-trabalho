#pragma once

#include <GL/glut.h>
#include <math.h>

class Chave
{
public:
	GLdouble posicao[3];
	/** Contrutores **/
	/** Cria a chave*/
	Chave(void);
	/** Cria a chave recebendo a posição onde vai ser colocada*/
	Chave(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha a chave */
	void desenhar(void);

	/** Destrutor */
	~Chave(void);
};

