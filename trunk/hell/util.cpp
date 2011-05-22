
#include <GL/glut.h>
#include <math.h>

#include "util.h"

void writeText(char *texto, int posX, int posY){
	void *font = GLUT_BITMAP_HELVETICA_12;
   
}


float inline distancia2d(double x1, double y1,double x2, double y2)	{

	return (sqrt(pow(x2-x1,2) + pow(y2-y1,2)));
}

double inline distancia3d(double x1, double y1,double z1, double x2,double y2, double z2)	{

	return (sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2)));
}

bool colideu(Agente *a, Bala *b){
	GLdouble ax = a->posicao[XX];
	GLdouble ay = a->posicao[YY];
	GLdouble az = a->posicao[ZZ];
	GLdouble bx = a->posicao[XX];
	GLdouble by = a->posicao[YY];
	GLdouble bz = a->posicao[ZZ];

	if(distancia3d(ax,ay,az,bx,by,bz) < DIST_COLISAO) return true;

	return false;
}
