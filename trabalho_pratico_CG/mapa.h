
#pragma once
#ifndef __MAPA
#define __MAPA


#include <iostream>
#include <list>
#include <set>

using namespace std;

//Terreno
#define NUM_ARVORES	1000
#define NUM_PEDRAS	100
//Missao
#define NUM_CHAVES	3
#define NUM_TORRES	8


typedef struct _posicao	{
	int x;
	int y;
}posicao;


class Mapa	{
	public:

		// Terreno
		list<posicao> arvores;
		list<posicao> pedras;

		//Missao
		list<posicao> chaves;
		list<posicao> torres;
		posicao inicial;
		posicao edificio;


		/* Cria aleatoriamente um mapa */
		Mapa(void);
		/* Cria um mapa com base num ficheiro de configuração */
		//Mapa(char *filename);

		//---

		/* Destroi o mapa */
		~Mapa(void);
}


#endif