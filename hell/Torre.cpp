
#include "Torre.h"


#include "Mapa.h"
#include <math.h>
extern Mapa * _mapa;


GLfloat _pi = 3.14159265358979323846;

Torre::Torre(void)
{
	posicao[XX] = 10.0f;
	posicao[YY] = 1.2f;
	posicao[ZZ] = 10.0f;
	ang = 0;
}

Torre::Torre(GLdouble posicaoInicialX, GLdouble posicaoInicialZ)
{
	posicao[XX] = posicaoInicialX;
	posicao[YY] = 1.2f;
	posicao[ZZ] = posicaoInicialZ;
	ang = 0;
}

/** Calcula o angulo que as torres tem de girar */
void Torre::girar(void){
	/**PRODUTO ESCALAR -> para saber o angulo que a torre tem de girar */
	// ca = coordenadas agente
	// ct = coordenadas torre
	GLfloat cax, ctx, cay, cty, caz, ctz;	// coordenadas
	GLfloat normaA, normaB;					// normas
	GLfloat h;								// cos(ang) = h ==> ang = 1/cos(h)

	/* vector ca - ct*/
	GLfloat vectorAx;
	GLfloat vectorAy;
	GLfloat vectorAz;

	// vector unit�rio (1,0,0)
	GLfloat vectorBx;
	//vectorBx = 1;

	/* coordenadas do agente */
	cax = _mapa->agente->posicao[XX];
	cay = _mapa->agente->posicao[YY];
	caz = _mapa->agente->posicao[ZZ];

	/*coordenadas da torre*/
	ctx = posicao[XX];
	cty = posicao[YY];
	ctz = posicao[ZZ];

	vectorAx = cax-ctx;
	vectorAy = cay-cty;
	vectorAz = caz-ctz;

	normaA = sqrt(pow(vectorAx,2)+pow(vectorAy,2)+pow(vectorAz,2));

	h = (vectorAx)/(normaA);

	ang = acos(h);							// angulo que a torre vai girar

	// passar o angulo de radianos para graus
	ang = (ang*180)/_pi;

	/**/
	if(posicao[ZZ] <= _mapa->agente->posicao[ZZ]) ang = -ang;
}

void Torre::distanciaAgente(void){
	// coordenadas do agente
	GLfloat ax, az;

	// coordenadas da torre
	GLfloat tx, tz;
	
	ax = _mapa->agente->posicao[XX];
	az = _mapa->agente->posicao[ZZ];

	tx = posicao[XX];
	tz = posicao[ZZ];

	dist = sqrt(pow(ax-tx,2)+pow(az-tz,2));

}

void Torre::desenha(void)	{
	
	// alterar o angulo
	distanciaAgente();
	if(dist < DISTANCIA_TORRE_AGENTE)  girar();
	

	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glColor3f(0.5, 0.5, 0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		glRotatef(ang,0,posicao[YY],0);
		glutSolidCube(3);
	glPopMatrix();
	
}

Torre::~Torre(void)
{
}
