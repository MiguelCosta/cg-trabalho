#pragma once

// Tipos de vista
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3


class Camera	{
private:
public:
	int tipoDeVista;
	GLdouble camPosOnGodMode[3];

	Camera(void);
	void initFrame();
	void desenhar(void);
	~Camera(void);
};

void changeSize(int w, int h);

