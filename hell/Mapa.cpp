
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


void Mapa::terreno(void){
	

	float color[] = {1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	int x = 0, z = 0;
	
	glPushMatrix();

	glColor3f(1.0,1.0,1.0);
	for(x = -MAPA_TAM; x < MAPA_TAM; x++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(z = -MAPA_TAM; z < MAPA_TAM; z++) {
			glVertex3f(x+1,0,z);
			glVertex3f(x,0,z);
		}
		glEnd();
	}

	glPopMatrix();

}

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{

	//glPolygonMode(GL_BACK, GL_LINE);

	//Desenhar as dependencias
	agente->desenhar();
	edificio->desenhar();
	terreno();
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
}

Mapa::~Mapa(void)	{
}
