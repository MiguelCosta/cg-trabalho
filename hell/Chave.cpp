#include "Chave.h"
#include "Mapa.h"

extern Mapa *_mapa;

Chave::Chave(void)
{
	posicao[XX] = 10.0f;
	posicao[YY] = 0.2f;
	posicao[ZZ] = 10.0f;
	encontrada = 0;
}

Chave::Chave(GLdouble posicaoInicialX, GLdouble posicaoInicialZ){
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 0.2f;
	posicao[ZZ] = posicaoInicialZ;
	encontrada = 0;
}


void Chave::encontra(void){
	/** coordenadas do agente */
	GLfloat ax, az;
	ax = _mapa->agente->posicao[XX];
	az = _mapa->agente->posicao[ZZ];

	/** coordenadas da chave */
	GLdouble cx, cz;
	cx = posicao[XX];
	cz = posicao[ZZ];

	/* variavel para calcular a distancia do agente à chave*/
	GLfloat distAgenteChave;

	distAgenteChave = sqrt(pow(ax-cx,2)+pow(az-cz,2));

	if(distAgenteChave <= APANHA_CHAVE) encontrada = 1;

}


void Chave::desenha(void)	{

	encontra();

	if(encontrada == 0){
	float color[] = {0.0,1.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glutSolidTorus(1,2,10,10);
	glPopMatrix();
	}
}


Chave::~Chave(void)
{
}
