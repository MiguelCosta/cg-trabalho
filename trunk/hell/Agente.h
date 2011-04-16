#pragma once

#include <GL/glut.h>

extern bool teclas[4];

class Agente	{
public:
	GLdouble posicao[3];
	GLfloat angAlpha;
	GLfloat angBeta;

	/** Construtores */
	Agente(void);
	Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);
	/** Desenha o agente */
	void desenhar(void);
	/** Mover o agente */
	void andar();
	/** Destrutor */
	~Agente(void);

private:
	GLfloat velocidade;
};

