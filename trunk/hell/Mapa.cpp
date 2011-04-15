
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>


#include "Mapa.h"
#include "defines.h"


/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	{

	//carregarTextura();

	agente = new Agente(0, 0);
	edificio = new Edificio();

	//inicializa o gerador de numeros aleatorios
	srand(time(NULL));

	/* Colocar Chaves */
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		chaves[i] = new Chave(
			rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM,
			rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM);
	}
	/*
	agente = new Agente(
		rand() *2000 / RAND_MAX,
		rand() *2000 / RAND_MAX);

	edificio = new Edificio(
		rand() *2000 / RAND_MAX,
		rand() *2000 / RAND_MAX); */
}

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{

	//glPolygonMode(GL_BACK, GL_LINE);
	
	//Desenhar as dependencias
	agente->desenhar();
	edificio->desenhar();
	
	// desenhar as chaves
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		chaves[i]->desenha();
	}

	//list<Chave *>::iterator it;
	/* Colocar Chaves */
	/*for( it = chaves->begin() ; it != chaves->end() ; it++)	{
		(*it)->desenhar();
	}
	*/
	glPushMatrix();
	float color2[] = {0.0, 0.9, 0.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color2);
	
	glBegin(GL_QUADS);
		glColor3f(0.0,0.6, 0.0);
				
		glVertex3f(-MAPA_TAM, 0.0, -MAPA_TAM);
		glVertex3f(-MAPA_TAM, 0.0,  MAPA_TAM);
		glVertex3f( MAPA_TAM, 0.0,  MAPA_TAM);
		glVertex3f( MAPA_TAM, 0.0, -MAPA_TAM);
	glEnd();
	glPopMatrix();
}

Mapa::~Mapa(void)	{
}
