#pragma once

#include <GL/glut.h>
#include <math.h>
#include "defines.h"
#include "Mapa.h"

class Torre
{
public:
	GLdouble posicao[3];
	// angulo para se girar relativamente à posição do utilizador
	GLfloat ang;

	// distancia da torre ao agente
	GLfloat dist;
	

	/** Contrutores **/
	Torre(void);
	Torre(GLdouble posicaoInicialX, GLdouble posicaoInicialZ);

	/** Desenha a torre */
	void desenha(void);

	/** Calcula o angulo que a torre tem de girar */
	void girar(void);

	/** Calcula a distancia ao agente */
	void distanciaAgente(void);

	~Torre(void);

};

