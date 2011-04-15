
#include <stdlib.h>
#include <GL/glut.h>
#include "Mapa.h"


/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	{

	//carregarTextura();

	agente = new Agente(rand() * 2000 / RAND_MAX,rand() * 2000 / RAND_MAX);

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

	//Desenhar as dependencias
	agente->desenhar();

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texID);

	glPushMatrix();

	glBegin(GL_QUADS);
		glColor3f(0.1f, 0.98f, 0.2f);

		//glTexCoord2f(-2000,2000);
		glVertex3f(-2000.0, 0.0, 2000.0);
		
		//glTexCoord2f(2000,2000);
		glVertex3f( 2000.0, 0.0, 2000.0);
		
		//glTexCoord2f(2000,-2000);
		glVertex3f( 2000.0, 0.0,-2000.0);
		
		//glTexCoord2f(-2000,-2000);
		glVertex3f(-2000.0, 0.0,-2000.0);
	glEnd();
	
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D, 0);
}

Mapa::~Mapa(void)
{
}
