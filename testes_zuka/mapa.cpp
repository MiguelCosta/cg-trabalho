

#include "mapa.h"
;

/* Cria aleatoriamente um mapa */
Mapa::Mapa(void)	
				chaves = new list<Chave>();
{
	//srand (time(NULL));
	GLdouble x;
	GLdouble y;
	
	chaves.push_back();

	/* Colocar arvores * /
	for( int i=0 ; i < NUM_ARVORES ; i++)	{
		p.x = rand() * 2000 / RAND_MAX;
		p.y = rand() * 2000 / RAND_MAX;
		arvores.push_front(* new posicao(p));
	}
	/* Colocar pedras * /
	for( int i=0 ; i < NUM_PEDRAS ; i++)	{
		p.x = rand() * 2000 / RAND_MAX;
		p.y = rand() * 2000 / RAND_MAX;
		pedras.push_front(* new posicao(p));
	}
	for( int i=0 ; i < NUM_CHAVES ; i++)	{
		p.x = rand() * 2000 / RAND_MAX;
		p.y = rand() * 2000 / RAND_MAX;
		chaves.push_front(* new posicao(p));
	}
	inicial.x = rand() *2000 / RAND_MAX;
	inicial.y = rand() *2000 / RAND_MAX;
	edificio.x = rand() *2000 / RAND_MAX;
	edificio.y = rand() *2000 / RAND_MAX; */
}

/* Cria um mapa com base num ficheiro de configuração * /
mapa(char *filename)	{

} */

//---

/* Destroi o mapa */
Mapa::~Mapa(void)	{

}

