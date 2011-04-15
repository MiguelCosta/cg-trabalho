#pragma once

#include "Agente.h"
#include "Chave.h"
#include "Edificio.h"
#include "defines.h"

class Mapa	{
public:

	//Terreno

	//Missao
	Agente				*agente;
	Chave				*chaves[NUM_CHAVES];
	Edificio			*edificio;

	Mapa(void);

	void  terreno(void);
	void desenhar(void);
	~Mapa(void);

};

