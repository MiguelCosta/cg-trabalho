#include "Chave.h"
#include "Mapa.h"

extern Mapa *_mapa;

Chave::Chave(void)
{
	Chave(0,0);
}

Chave::Chave(GLdouble posicaoInicialX, GLdouble posicaoInicialZ){
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 0.4f;
	posicao[ZZ] = posicaoInicialZ;
	encontrada = 0;
	ang = 0;
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

	if(distAgenteChave <= APANHA_CHAVE)	encontrada = 1;

}

void Chave::girar(void){
	ang +=CHAVE_ANGULO_ROTACAO;
}

void Chave::desenha(float posX, float posY, float posZ)	{

	// verifica se a chave ja foi encontrada
	encontra();

	// gira a chave
	girar();

	posicao[XX] = (GLdouble) posX;
	posicao[YY] = (GLdouble) posY + 1;
	posicao[ZZ] = (GLdouble) posZ;

	// se a chave ainda nao for encontrada vai desenha-la
	if(encontrada == 0){
		float color[] = {0.0,0.0,1.0,1.0};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

		glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glRotatef(ang,0, posicao[YY],0);
		glmDraw(chave,GLM_SMOOTH);
		//glutSolidTorus(0.1,0.3,10,10);
		glPopMatrix();
	}
}


Chave::~Chave(void)
{
}
