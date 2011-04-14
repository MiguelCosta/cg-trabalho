

#include <GL/glut.h>

#include "mapa.h"
#include "textura.h"



/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	{

	//carregarTextura();

	/* Colocar Chaves */
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
		rand() *2000 / RAND_MAX);
}

/* Cria um mapa com base num ficheiro de configuração * /
mapa(char *filename)	{

} */

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{

	//Desenhar as dependencias
	

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texID);

	glPushMatrix();

	glBegin(GL_QUADS);
		glTexCoord2f(-2000,2000);glVertex3f(-2000.0, 0.0, 2000.0);
		glTexCoord2f(2000,2000);glVertex3f( 2000.0, 0.0, 2000.0);
		glTexCoord2f(2000,-2000);glVertex3f( 2000.0, 0.0,-2000.0);
		glTexCoord2f(-2000,-2000);glVertex3f(-2000.0, 0.0,-2000.0);
	glEnd();
	
	glPopMatrix();

	//glBindTexture(GL_TEXTURE_2D, 0);
}

/* Destroi o mapa */
Mapa::~Mapa(void)	{

}

