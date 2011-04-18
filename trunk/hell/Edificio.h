#pragma once

#include <GL/glut.h>
#include "glm.h"

class Edificio
{
public:

	GLdouble posicao[3];
	GLMmodel *edificio;

	/** Construtor */
	Edificio(void);
	Edificio(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha o edificio*/
	void desenhar(void);


	~Edificio(void);
};

