
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
	// a = coordenadas agente
	// t = coordenadas torre
	GLfloat ax, tx, ay, ty, az, tz;	// coordenadas
	GLfloat normaA, normaT;			// normas
	GLfloat h;						// cos(ang) = h ==> ang = 1/cos(h)

	ax = _mapa->agente->posicao[XX];
	ay = _mapa->agente->posicao[YY];
	az = _mapa->agente->posicao[ZZ];

	tx = posicao[XX];
	ty = posicao[YY];
	tz = posicao[ZZ];

	normaA = sqrt(pow(ax,2)+pow(ay,2)+pow(az,2));
	normaT = sqrt(pow(tx,2)+pow(ty,2)+pow(tz,2));

	h = ((ax*tx)+(ay*ty)+(az*tz))/(normaA*normaT);

	ang = acos(h);							// angulo que a torre vai girar

	// passar o angulo de radianos para graus
	ang = (ang*180)/_pi;

	//printf("angulo: %lf\n",ang);
}

void Torre::desenha(void)	{
	
	// alterar o angulo
	girar();

	float color[] = {1.0,0.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	
	glPushMatrix();
		glColor3f(0.5, 0.5, 0);
		glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
		printf("angulo2: %lf\n",ang);
		glRotatef(ang,0,1,0);
		glutSolidCube(3);
	glPopMatrix();
	
}

Torre::~Torre(void)
{
}
