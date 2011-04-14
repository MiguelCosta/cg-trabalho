#pragma once

#include <GL/glut.h>
#include <IL/il.h>

// Tipos de vista
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3

// Eixos cartesianos
#define	XX	0
#define	YY	1
#define	ZZ	2

class Camera	{
public:
	GLdouble direcao[3];
	int tipoDeVista[3];

	void mostracena();

	Camera(void);
	~Camera(void);
};

