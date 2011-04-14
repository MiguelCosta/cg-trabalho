#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <IL/il.h>
#include "mapa.h"

// Tipos de vista
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3

// Eixos cartesianos
#define	XX	0
#define	YY	1
#define	ZZ	2

extern Mapa		*_mapa;
extern Agente	*_agente;

class Camera	{
public:
	//GLdouble cam_pos[3];
	GLdouble direcao[3];
	int tipoDeVista;

	void desenhar();

	Camera(void);
	~Camera(void);
};

