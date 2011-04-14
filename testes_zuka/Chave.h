#pragma once

#include <GL/glut.h>
#include <IL/il.h>
#include <math.h>
#include "glm.h"

class Chave	{

public:
	GLdouble posicao[3];
	Chave(void);
	Chave(GLdouble x, GLdouble z);
	
	~Chave(void);
	
	void desenhar(void);
	
	

private:
	 GLMmodel *chave;
	 GLdouble altura;
	 unsigned int texID;
	 void aplicaTextura(char *nomeFich);
	 void carregaModeloObj(char *nomeFich);

};
