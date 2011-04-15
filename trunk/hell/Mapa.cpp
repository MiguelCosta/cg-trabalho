
#include <stdlib.h>
#include <GL/glut.h>
#include "Mapa.h"


/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	{

	//carregarTextura();

	agente = new Agente(0, 0);
	chave = new Chave();
	/* Colocar Chaves * /
	for( int i=0 ; i < NUM_CHAVES ; i++)	{

		chaves->push_front(
			new Chave(
				rand() * 2000 / RAND_MAX,
				rand() * 2000 / RAND_MAX));
	}
	agente = new Agente(
		rand() *2000 / RAND_MAX,
		rand() *2000 / RAND_MAX);

	edificio = new Edificio(
		rand() *2000 / RAND_MAX,
		rand() *2000 / RAND_MAX); */
}

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{
	glPolygonMode(GL_BACK, GL_LINE);
	//Desenhar as dependencias
	agente->desenhar();
	chave->desenhar();
	
	glPushMatrix();
	float color2[] = {0.0, 0.9, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color2);
	
	glBegin(GL_QUADS);
		glColor3f(0.0,0.6, 0.0);
				
		glVertex3f(-150, 0.0, -150);
		glVertex3f(-150, 0.0,  150);
		glVertex3f( 150, 0.0,  150);
		glVertex3f( 150, 0.0, -150);
	glEnd();
	glPopMatrix();
}

Mapa::~Mapa(void)	{
}
