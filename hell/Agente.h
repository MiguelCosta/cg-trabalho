#pragma once

#include <GL/glut.h>

class Agente	{
public:
		
	GLfloat angAlpha;
	GLfloat angBeta;

	/** Construtores */
	Agente(void);
	Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);
	/** Desenha o agente */
	void desenhar(void);
	/** Mover o agente */
	void andar();
	/** Calcula a direcao que o agente esta a olhar */
	float direcao(int EIXO);
	/** Destrutor */
	~Agente(void);

private:
	float velocidade;
};

