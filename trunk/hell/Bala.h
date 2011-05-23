#pragma once

#include <GL/glut.h>
#include "defines.h"

class Bala
{
private:
	/* posicao da chave */
	float posicao[3];
	float pTorre[3];
	float ang;
	
public:
	Bala(void);

	/** Variavel que diz se é ou nao para desenhar a bala*/
	bool ok;
	
	/** Cria a bala recebendo a posição onde vai ser colocada*/
	Bala(float posicaoInicialX, float posicaoInicialY, float posicaoInicialZ, float angTorre);

	/** Desenha a chave */
	void desenha();

	GLdouble getPosicaoXX(void);
	GLdouble getPosicaoYY(void);
	GLdouble getPosicaoZZ(void);

	~Bala(void);
};

