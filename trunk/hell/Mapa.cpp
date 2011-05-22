#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
//#include <GL/glew.h>

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

void Mapa::initMapaAlturas(ILstring nome_textura){

	ilGenImages(1, &img_alturas);
	
	ilBindImage(img_alturas);
	ilLoadImage(nome_textura);
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	larg = ilGetInteger(IL_IMAGE_WIDTH);
	altu = ilGetInteger(IL_IMAGE_HEIGHT);
	dados_altura = ilGetData();

	grid_n = larg;
}

float Mapa::h(float x, float z) {
   return dados_altura[(int) x + (int) z * larg] / 2.0;
}

void Mapa::heightedVertex(float mult, float x, float z) {
   glVertex3f(mult*x, h(x, z), mult*z);
}

/** desenha uma grelha para o terreno */
void Mapa::terreno(void){

	// carrega a textura
	//initTextura(TEXTURA_TERRENO);

	//initTextura(TEXTURA_TERRENO);
	
	float grid_width = 256 / (float) grid_n;
	
	float color[] = {1.0,1.0,1.0,1.0};
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
	int x = 0, z = 0;	
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textura_solo);
	glTranslatef(-MAPA_METADE,0,-MAPA_METADE);
	for(x = 0; x < altu-1; x++) {
		glBegin(GL_TRIANGLE_STRIP);
			for(z = 0; z < larg; z++) {
			glTexCoord2f(z, 0); 
			heightedVertex(grid_width, (x+1), z);
			glTexCoord2f(z, 1); 
			heightedVertex(grid_width, x, z);
		}
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}
void drawParedes(float altura){
	
	float a[3] = {MAPA_TAM+1.8, altura, -MAPA_TAM-1.8};
	float b[3] = {MAPA_TAM+1.8, 0, -MAPA_TAM-1.8};
	float c[3] = {MAPA_TAM+1.8, altura, MAPA_TAM+1.8};
	float d[3] = {MAPA_TAM+1.8, 0, MAPA_TAM+1.8};
	float e[3] = {-MAPA_TAM-1.8, altura, MAPA_TAM+1.8};
	float f[3] = {-MAPA_TAM-1.8, 0, MAPA_TAM+1.8};
	float g[3] = {-MAPA_TAM-1.8, altura, -MAPA_TAM-1.8};
	float h[3] = {-MAPA_TAM-1.8, 0, -MAPA_TAM-1.8};

	float color2[] = {0.2,0.3,0.4};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color2);
	
	glBegin(GL_QUAD_STRIP);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
		glVertex3fv(d);
		glVertex3fv(e);
		glVertex3fv(f);
		glVertex3fv(g);
		glVertex3fv(h);
		glVertex3fv(a);
		glVertex3fv(b);
	glEnd();
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

// coloca no ecrão a informação de quantas chaveous já apanhou ou se já apanhou todas
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

void Mapa::drawTree() {

   glPushMatrix();
   glRotatef(-90,1.0,0.0,0.0);
   float color[] = {1.0,1.0,0.5,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
   glutSolidCone(0.25,4,5,1);
   float color2[] = {0.0, 0.5 + rand() * 0.5f/RAND_MAX,0.0,1.0};
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color2);
   glTranslatef(0.0,0.0,2.0);
   glutSolidCone(2.0,5.0,5,1);
   glPopMatrix();
}

void Mapa::placeTrees() {

   float r = 35.0;
   float alpha;
   float rr;
   float x,z;

   srand(31457);
   int arvores = 0;

   while (arvores < 200) {

      rr = rand() * 150.0/ RAND_MAX;
      alpha = rand() * 6.28 / RAND_MAX;

      x = cos(alpha) * (rr + r);
      z = sin(alpha) * (rr + r);

      if (fabs(x) < MAPA_METADE && fabs(z) < MAPA_METADE) {

         glPushMatrix();
         glTranslatef(x, h (x+MAPA_METADE, z+MAPA_METADE),z);
         drawTree();
         glPopMatrix();
         arvores++;
      }
   }
}

float Mapa::alturaCamara(float x, float z){
   double intX, intZ;
   float fracX, fracZ;

   fracX = modf(x, &intX);
   fracZ = modf(z, &intZ);

   float alt1, alt2;
   
   alt1 = h(intX,     intZ) * (1 - fracZ) + h(intX,     intZ + 1) * fracZ;
   alt2 = h(intX + 1, intZ) * (1 - fracZ) + h(intX + 1, intZ + 1) * fracZ;

   return alt1 * (1 - fracX) + alt2 * fracX;
}

/* Desenha o mapa e tudo que esta nele */
void Mapa::desenhar(void)	{

	/***** DESENHAR OS OBJECTOS *****/
	terreno();
	placeTrees();

	float posX = agente->posicao[XX];
	float posZ = agente->posicao[ZZ];
	float posY = h(posX+MAPA_METADE, posZ+MAPA_METADE);
	camY = alturaCamara(posX+MAPA_METADE, posZ+MAPA_METADE) + 2;

	printf("altura: %d\n", posY);
	agente->desenhar(posX, camY, posZ);

	posX = edificio->posicao[XX];
	posZ = edificio->posicao[ZZ];
	camY = alturaCamara(posX+MAPA_METADE, posZ+MAPA_METADE) + 2;
	posY = camY;

	//printf("Altua: %f",posY);
	edificio->desenhar(posX, posY, posZ);

	drawParedes(50);
	// desenhar as chaves
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		
		posX = chaves[i]->posicao[XX];
		posZ = chaves[i]->posicao[ZZ];
		posY = camY = alturaCamara(posX+MAPA_METADE, posZ+MAPA_METADE) + 2;

		chaves[i]->desenha(posX,posY, posZ);
	}

	// desenhar as torres
	for( int i=0 ; i < NUM_TORRES ; i++)	{
		posX = torres[i]->posicao[XX];
		posZ = torres[i]->posicao[ZZ];
		posY = camY = alturaCamara(posX+MAPA_METADE, posZ+MAPA_METADE) + 2;

		torres[i]->desenha(posX,posY,posZ);
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
