#pragma once

#include <GL/glut.h>
#include "glm.h"

class Agente	{
public:
	GLdouble posicao[3];
	GLfloat angAlpha;
	GLfloat angBeta;
	int colisoes;
	GLMmodel *agente;

	/** Construtores */
	Agente(void);
	Agente(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);
	/** Desenha o agente */
	void desenhar(float posX, float posY, float posZ);
	/** Mover o agente */
	void andar();
	/** Calcula a direcao que o agente esta a olhar */
	float direcao(int EIXO);
	/**incrementa as colisões */
	void incrementaColisao(void);
	/** Destrutor */
	~Agente(void);

private:
	float velocidade;
};

