#include "Bala.h"
#include "Mapa.h"

extern Mapa *_mapa;

Bala::Bala(void)
{
	Bala(0,0,0,0);
}

Bala::Bala(float posicaoInicialX, float posicaoInicialY, float posicaoInicialZ, float angTorre)
{
	posicao[XX] = posicaoInicialX;
	posicao[YY] = posicaoInicialY;
	posicao[ZZ] = posicaoInicialZ;
	ang = (angTorre*PI)/180;
	ok = false;
}

void Bala::desenha()
{
	if(ok){
		posicao[XX] = posicao[XX] + VELOCIDADE_BALA*cos(ang);
		posicao[ZZ] = posicao[ZZ] + VELOCIDADE_BALA*sin(ang);
		posicao[YY] = _mapa->h(posicao[XX],posicao[ZZ]);

		float color[] = {0.0,0.0,1.0,1.0};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

		glPushMatrix();
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glRotatef(ang,0,1,0);
		// desenha um cone
		glutSolidCone(1,2,5,5);
		glPopMatrix();
	}
}

GLdouble Bala::getPosicaoXX(void){
	return posicao[XX];
}

GLdouble Bala::getPosicaoYY(void){
	return posicao[YY];
}

GLdouble Bala::getPosicaoZZ(void){
	return posicao[ZZ];
}

Bala::~Bala(void)
{
}
