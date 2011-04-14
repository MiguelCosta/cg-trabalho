#pragma once

#include <GL/glut.h>
#include <math.h>
#include "glm.h"

class Chave
{
public:
	Chave(void);
	void desenhar(void);
	~Chave(void);

private:
	 GLMmodel *chave;

};

