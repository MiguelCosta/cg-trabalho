#include "Chave.h"

Chave::Chave(void){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	aplicaTextura();

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

	aplicaTextura("chave.jpg");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

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

void Chave::aplicaTextura(char *nome){
	unsigned int t, tw, th;
	unsigned char *texData;
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)nome);
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
	glGenTextures(1,&texID);
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
}

Chave::~Chave(void)
{
}
