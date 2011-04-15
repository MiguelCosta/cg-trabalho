#pragma once

#include "Agente.h"
#include "Chave.h"
#include "Edificio.h"

class Mapa	{
public:

	//Terreno

	//Missao
	Agente		*agente;
	Chave		*chave;
	Edificio	*edificio;

	Mapa(void);
	void desenhar(void);
	~Mapa(void);
};

