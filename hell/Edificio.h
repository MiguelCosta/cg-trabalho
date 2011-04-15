#pragma once

#include <GL/glut.h>

class Edificio
{
public:

	GLdouble posicao[3];

	/** Construtor */
	Edificio(void);
	Edificio(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha o edificio*/
	void desenhar(void);


	~Edificio(void);
};

