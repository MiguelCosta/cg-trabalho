#pragma once

#include "Vec3.h"

// Tipos de vista
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3


class Camera	{
private:
public:

	enum TroncoCamera	{
		DENTRO,
		INTERSEPTA,
		FORA
	};

	int tipoDeVista;
	GLdouble camPosOnGodMode[3];

	Camera(void);
	void initFrame();
	void desenhar(void);
	~Camera(void);
};

bool deveDesenhar(Vec3 centroEsfera, float raioEsfera);
void changeSize(int w, int h);

