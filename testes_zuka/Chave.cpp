#include "Chave.h"

 
Chave::Chave(void){
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   chave = glmReadOBJ("chave.obj");
   glmUnitize(chave);
   glmFacetNormals(chave);
   glmVertexNormals(chave,90);

}

void Chave::desenhar(void){
	float lpos[4] = {1,1,1,0};
	glLightfv(GL_LIGHT0,GL_POSITION,lpos);
    glmDraw(chave,GLM_SMOOTH|GLM_MATERIAL);
}


Chave::~Chave(void)
{
}
