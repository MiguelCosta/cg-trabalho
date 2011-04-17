#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>


#include "Mapa.h"
#include "defines.h"
#include <string.h>

/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	{


	//inicializa o gerador de numeros aleatorios
	srand(time(NULL));

	/***** Criar os objectos *****/
	/* Cria um agente */
	agente = new Agente(0, 0);

	/* Cria um Edificio */
	edificio = new Edificio();

	/* Colocar as Chaves num array */
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		chaves[i] = new Chave( rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM, rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM);
	}

	/* Colocar as Torres num array */

	for( int i=0 ; i < NUM_TORRES ; i++)	{
		torres[i] = new Torre(
			rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM,
			rand() * 2 * MAPA_TAM / RAND_MAX - MAPA_TAM);
	}

	/* Radar */
	radar = new Radar();

	/* numero de chaves apanhadas */
	num_chaves_apanhadas = 0;

	flagJogoCompleto = false;
}


/* Textura para o terreno */
void Mapa::initTextura(char * nome_textura){
	ilInit();

	ilGenImages(1,&img_textura);
	ilBindImage(img_textura);
	ilLoadImage((ILstring)nome_textura);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	textura_w = ilGetInteger(IL_IMAGE_WIDTH);
	textura_h = ilGetInteger(IL_IMAGE_HEIGHT);

	textura_data = ilGetData();

	glGenTextures(1,&textura_solo);
	glBindTexture(GL_TEXTURE_2D,textura_solo);
	glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_WRAP_S,        GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_WRAP_T,        GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_MAG_FILTER,    GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,               GL_TEXTURE_MIN_FILTER,    GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textura_w, textura_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textura_data);

	//Configurações para o OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//inicialização da iluminação
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

}

/** desenha uma grelha para o terreno */
void Mapa::terreno(void){

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura_solo);
	int x = 0, z = 0;	

	float color[] = {1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);


	glBegin(GL_TRIANGLE_STRIP);

	for(z = -MAPA_TAM; z < MAPA_TAM; z++) {
		for(x = -MAPA_TAM; x < MAPA_TAM; x++) {
			glTexCoord2f(x, z); glVertex3f(x,0,z);
			glTexCoord2f(x, z+1); glVertex3f(x,0,z+1);
		}
	}

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

}

void Mapa::verificaEstadoJogo(void){

	// flag que indica se as chaves estão todas apanhadas
	bool todasAsChavesApanhadas = false;
	if (num_chaves_apanhadas == NUM_CHAVES) todasAsChavesApanhadas = true;

	// se todas as chaves foram apanhadas e está à beira do edificio o jogo está completo
	if(todasAsChavesApanhadas){
		// distancia entre agente e o edificio
		GLfloat distAgenteEdificio;

		// coordenadas do agente
		GLfloat ax, az;
		ax = agente->posicao[XX];
		az = agente->posicao[ZZ];

		// coordenadas do edificio
		GLfloat ex, ez;
		ex = edificio->posicao[XX];
		ez = edificio->posicao[ZZ];

		// calcula a distancia entre o agente e o edificio
		distAgenteEdificio = sqrt(pow(ax-ex,2)+pow(az-ez,2));

		// aqui já tem as chaves apanhadas, por isso se estiver perto do edificio o jogo está completo
		if(distAgenteEdificio <= DISTANCIA_AGENTE_NO_EDIFICIO) flagJogoCompleto = true;
	}
}

void setOrthographicProjection2(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);
	glScalef(1, -1, 1);
	glTranslatef(0, -200, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection2() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

// coloca no ecrão a informação de quantas chaves já apanhou ou se já apanhou todas
void Mapa::desenhaEstadoJogo(GLuint x, GLuint y){

	glPushMatrix();
	glLoadIdentity();

	setOrthographicProjection2();

	glRasterPos2i(x, y);
	char *string = new char[50];

	/** Mensagens que aparem do jogo, verifica se já apanhou as chaves todas ou nao*/
	if (flagJogoCompleto)
		sprintf(string, "JOGO TERMINADO :)");
	else 
		if(num_chaves_apanhadas == NUM_CHAVES)
			sprintf(string, "PARABENS! Ja apanhou as %d chaves, va para o edificio final!", num_chaves_apanhadas);
		else sprintf(string, "Chaves apanhadas: %d de %d", num_chaves_apanhadas, NUM_CHAVES);

		int len, i;
		len = (int) strlen(string);

		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
		}
		resetPerspectiveProjection2();
		glPopMatrix();
}

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{

	/***** DESENHAR OS OBJECTOS *****/
	terreno();
	agente->desenhar();
	edificio->desenhar();

	// desenhar as chaves
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		chaves[i]->desenha();
	}

	// desenhar as torres
	for( int i=0 ; i < NUM_TORRES ; i++)	{
		torres[i]->desenha();
	}

	// radar
	radar->desenha(7,7);

	// actualiza a variàvel de chaves apanhadas
	num_chaves_apanhadas = chaves_apanhadas();

	// verifica as se as chaves estão todas apanhadas e se está no edificio
	verificaEstadoJogo();

	// coloca no ecrã o estado actual do jogo, quantas chaves foram apanhadas e se já tem de ir para o edificio
	desenhaEstadoJogo(7,15);

	//list<Chave *>::iterator it;
	/* Colocar Chaves */
	/*for( it = chaves->begin() ; it != chaves->end() ; it++)	{
	(*it)->desenhar();
	}
	*/
}

int Mapa::chaves_apanhadas(void){
	int count = 0;
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		if (chaves[i]->encontrada == 1) count++;
	}

	return count;
}

Mapa::~Mapa(void)	{
}
