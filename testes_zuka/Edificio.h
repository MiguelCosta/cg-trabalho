#pragma once

#include <GL/glut.h>
#include <IL/il.h>
#include <math.h>

class Edificio
{
public:
	Edificio(void);
	Edificio(GLdouble posicaoX, GLdouble posicaoZ);
	~Edificio(void);


private:
	GLdouble posicao[3];
	GLdouble altura;
};

