
#include "Torre.h"
#include "util.h"
#include "Mapa.h"
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

	//modelo = new Modelo("catapull");
}

/** Calcula o angulo que as torres tem de girar */
void Torre::girar(void){
	/**PRODUTO ESCALAR -> para saber o angulo que a torre tem de girar */
	// ca = coordenadas agente
	// ct = coordenadas torre
	GLfloat cax, ctx, cay, cty, caz, ctz;	// coordenadas
	GLfloat normaA;							// normas
	GLfloat h;								// cos(ang) = h ==> ang = 1/cos(h)

	/* vector ca - ct*/
	GLfloat vectorAx;
	GLfloat vectorAy;
	GLfloat vectorAz;

	// vector unitário (1,0,0)
	//GLfloat vectorBx;
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

	ang = acos(h);							// angulo que a torre vai girar em graus
	ang = (ang*180)/_pi;					// passar o angulo de radianos para graus

	/* caso necessário quando o agente está numa posição ZZ superior à torre */
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

/*
void Torre::disparaBala(void){
	Bala *b = new Bala(posicao[XX], posicao[YY]+1, posicao[ZZ], ang);
	lista_balas.push_front(*b);
}

void Torre::desenhaBalas(){
	list<Bala>::iterator it;

	for(it = lista_balas.begin() ; it != lista_balas.end() ; it++ ){
		// vai buscar as posicoes da chave
		float posX = it->getPosicaoXX();
		float posZ = it->getPosicaoZZ();

		// este posY tem de ser a altura dno mapa
		float posY = _mapa->h(posX, posZ);

		if(posX > MAPA_TAM || posX < -MAPA_TAM || posZ > MAPA_TAM || posZ < - MAPA_TAM){
			it->~Bala();
		} else {
			// vai desenhar a chave na nova posicao
			it->desenha(posX, posY, posZ);

			// incrementa a colisão no agente
			if(distancia3d(_mapa->agente->posicao[XX], _mapa->agente->posicao[YY], _mapa->agente->posicao[ZZ], posX, posY, posZ) < DIST_COLISAO){
				_mapa->agente->incrementaColisao();
			}
		}

		
	}

}
*/
void Torre::desenha(float posX, float posY, float posZ)	{

	// alterar o angulo
	distanciaAgente();
	if(dist < DISTANCIA_TORRE_AGENTE){
		girar();
		//disparaBala();
	}

	//desenhaBalas();

	posicao[XX] = (GLdouble) posX;
	posicao[YY] = (GLdouble) posY + 1;
	posicao[ZZ] = (GLdouble) posZ;

	float color[] = {1.0,1.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);

	glPushMatrix();
	glTranslatef(posicao[XX], posicao[YY], posicao[ZZ]);
	glRotatef(ang,0,posicao[YY],0);

	glutSolidCube(3);

	//modelo->modeloMD2->drawPlayerItp(false,(Md2Object::Md2RenderMode) modelo->modoVista);

	glPopMatrix();

}

Torre::~Torre(void)
{
}
