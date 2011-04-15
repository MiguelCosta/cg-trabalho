#pragma once

#include "Agente.h"
#include "Chave.h"
class Mapa	{
public:

	//Terreno

	//Missao
	Agente *agente;
	Chave	*chave;

	Mapa(void);
	void desenhar(void);
	~Mapa(void);
};

