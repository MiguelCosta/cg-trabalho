
#include "mapa.h"



	/* Cria aleatoriamente um mapa */
	mapa::mapa(void)	{
		//srand (time(NULL));
		
		/* Colocar arvores */
		posicao p;
		
		for( int i=0 ; i < NUM_ARVORES ; i++)	{
			p.x = rand() * 2000 / RAND_MAX;

	}

	/* Cria um mapa com base num ficheiro de configuração */
	mapa(char *filename)	{

	}
	
	//---
	
	/* Destroi o mapa */
	~mapa(void)	{

	}

