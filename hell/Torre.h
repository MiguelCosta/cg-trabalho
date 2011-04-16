#pragma once

#include <GL/glut.h>
#include <math.h>
#include "defines.h"

class Torre
{
public:
	GLdouble posicao[3];
	GLfloat ang;

	/** Contrutores **/
	Torre(void);
	Torre(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha a torre */
	void desenha(void);

	~Torre(void);

};

