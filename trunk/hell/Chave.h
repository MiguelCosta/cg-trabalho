#pragma once

#include <GL/glut.h>
#include <math.h>
#include "defines.h"

class Chave
{
public:
	/* posicao da chave */
	GLdouble posicao[3];

	/* estado da chave 
	* 0 nao encontrada
	* 1 encontrada
	* */
	int encontrada;

	/** Contrutores **/
	/** Cria a chave*/
	Chave(void);
	/** Cria a chave recebendo a posição onde vai ser colocada*/
	Chave(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha a chave */
	void desenha(void);

	/** quando o agente encontra a chave */
	void encontra(void);

	/** Destrutor */
	~Chave(void);
};

