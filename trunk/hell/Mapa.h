#pragma once

#include "Agente.h"
#include "Chave.h"
#include "Edificio.h"
#include "defines.h"
#include <IL/il.h>



class Mapa	{
public:

	//Terreno

	//Missao
	Agente				*agente;
	Chave				*chaves[NUM_CHAVES];
	Edificio			*edificio;

	Mapa(void);
	/** desenha o terreno */
	void terreno(void);
	/** textura para o terreno */
	void initTextura(ILstring nomeTextura);

	/**desenha tudo no mapa */
	void desenhar(void);
	~Mapa(void);

private:
	// imagem de textura
	unsigned int id_textura;
	int textura_w, textura_h;
	unsigned char *textura_data;

};

