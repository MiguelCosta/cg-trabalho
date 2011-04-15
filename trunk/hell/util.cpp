
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
