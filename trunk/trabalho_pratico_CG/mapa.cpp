

class mapa;


	/* Cria aleatoriamente um mapa */
	mapa::mapa()	{
		//srand (time(NULL));
		posicao p;

		/* Colocar arvores */
		for( int i=0 ; i < NUM_ARVORES ; i++)	{
			p.x = rand() * 2000 / RAND_MAX;
			p.y = rand() * 2000 / RAND_MAX;

	}

	/* Cria um mapa com base num ficheiro de configuração * /
	mapa(char *filename)	{

	} */
	
	//---
	
	/* Destroi o mapa */
	~mapa(void)	{

	}

