
#include "Chave.h"

Chave::Chave(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//aplicaTextura();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	carregaModeloObj("chave.obj");

	glBindTexture(GL_TEXTURE_2D, 0);

	posicao[0]=0.0;
	posicao[1]=0.0;
	posicao[2]=0.0;
}

Chave::Chave(GLdouble posX, GLdouble posZ){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	texID = aplicaTextura("chave.jpg", texID);

	carregaModeloObj("chave.obj");

	glBindTexture(GL_TEXTURE_2D, 0);

	posicao[0]=posX;
	posicao[1]=altura;
	posicao[2]=posZ;

}
void Chave::desenhar(void){
	float lpos[4] = {1,1,1,0};
	glLightfv(GL_LIGHT0,GL_POSITION,lpos);
    glmDraw(chave,GLM_SMOOTH|GLM_MATERIAL);
}

void Chave::carregaModeloObj(char* nome){
	chave = glmReadOBJ(nome);
	glmUnitize(chave);
	glmFacetNormals(chave);
	glmVertexNormals(chave,90);
}

Chave::~Chave(void)
{
}
