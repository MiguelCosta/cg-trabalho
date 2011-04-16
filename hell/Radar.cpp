
#include "util.h"
#include "Mapa.h"
#include "Radar.h"
#include "defines.h"
#include <string.h>

extern Mapa * _mapa;

Radar::Radar(void)
{
	dist = MAPA_TAM*2;
}


void Radar::distancia(void){
	// coordenadas do agente
	GLfloat ax, az;
	ax = _mapa->agente->posicao[XX];
	az = _mapa->agente->posicao[ZZ];

	// coordenadas temporarias da chave
	GLfloat cxt, czt;

	GLfloat distTemp = MAPA_TAM*2;
	GLfloat distTemp2 = 0;
	
	for(int i = 0; i < NUM_CHAVES; i++){
		// coordenadas temporarias da chave
		cxt = _mapa->chaves[i]->posicao[XX];
		czt = _mapa->chaves[i]->posicao[ZZ];
		
		// calcula a distancia à chave i
		distTemp2 = sqrt(pow(ax-cxt,2)+pow(az-czt,2));
		if(distTemp2 < distTemp) distTemp = distTemp2;
	}

	// se a chave i estiver mais próxima actualiza a dist
	dist = distTemp;

	// se a distancia for -1 é porque não está ao alcance do radar
	if(dist > RADAR_ALCALCE) dist = -1;

	//printf("Distancia: %lf\n",dist);
}


void setOrthographicProjection(){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 200, 0, 200);
  glScalef(1, -1, 1);
  glTranslatef(0, -200, 0);
  glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}


void Radar::desenha(GLuint x, GLuint y) {
   
	// calcula a distancia
	distancia();

    glPushMatrix();
    glLoadIdentity();
  
    setOrthographicProjection();

    glRasterPos2i(x, y);
	char *string = new char[50];
	if(dist > 0) sprintf(string, "Radar: Chave a %.2lf metros", dist);
	else sprintf(string, "Radar: sem alcance");

	int len, i;
	len = (int) strlen(string);

	for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
    resetPerspectiveProjection();
    glPopMatrix();
}
