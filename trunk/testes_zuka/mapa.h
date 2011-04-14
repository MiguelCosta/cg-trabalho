
#ifndef __MAPA
#define __MAPA

#include <iostream>
#include <list>
#include <GL/glut.h>

#include "Chave.h"
#include "Torre.h"
#include "Edificio.h"
#include "Agente.h"

using namespace std;

//Terreno
#define NUM_ARVORES	1000
#define NUM_PEDRAS	100
//Missao
#define NUM_CHAVES	3
#define NUM_TORRES	8


class Mapa	{
	public:

		// Terreno
		//list<posicao> arvores;
		//list<posicao> pedras;

		//Missao
		list<Chave *> *chaves;
		list<Torre *> *torres;
		Edificio *edificio;
		Agente *agente;


		/* Cria um mapa com posicoes aleatorias */
		Mapa(void);
		/* Cria um mapa com base num ficheiro de configuração */
		//Mapa(char *filename);
		// Desenha o mapa e tudo que ele contem 
		void desenhar(void);
		/* Destroi o mapa */
		~Mapa(void);

	private:
		unsigned int texID;
};

#endif
