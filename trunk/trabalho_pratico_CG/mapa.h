

#ifndef __MAPA
#define __MAPA

#define NUM_ARVORES 2000

#include <list>

class mapa	{
	public:
		
		typedef struct _posicao	{
			int x;
			int y;
		}posicao;

		// Terreno
		list<posicao> arvores;
		list<posicao> pedras;

		//Missao
		posicao chaves[3];
		list<posicao> torres;
		posicao inicial;
		posicao edificio;


		/* Cria aleatoriamente um mapa */
		mapa(void);
		/* Cria um mapa com base num ficheiro de configuração */
		mapa(char *filename);

		//---

		/* Destroi o mapa */
		~mapa(void);
}


#endif