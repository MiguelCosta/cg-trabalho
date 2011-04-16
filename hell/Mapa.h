#pragma once

#include "Agente.h"
#include "Chave.h"
#include "Edificio.h"
#include "Torre.h"
#include "defines.h"
#include <IL/il.h>



class Mapa	{
public:

	//Terreno

	//Missao
	Agente				*agente;
	Chave				*chaves[NUM_CHAVES];
	Edificio			*edificio;
	Torre				*torres[3];

	Mapa(void);
	/** desenha o terreno */
	void terreno(void);
	/** textura para o terreno */
	void initTextura(char * nome_textura);

	/**desenha tudo no mapa */
	void desenhar(void);
	~Mapa(void);

private:
	// imagem de textura
	unsigned int textura_solo, img_textura;
	int textura_w, textura_h;
	unsigned char *textura_data;

};

