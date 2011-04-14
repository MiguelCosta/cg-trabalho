

#ifndef __AGENTE
#define __AGENTE

#include <GL/glut.h>

class Agente	{
public:
	GLdouble posicao[3];

	Agente(void);
	Agente(GLdouble x, GLdouble y);
	void desenhar(void);
	~Agente(void);
};

#endif