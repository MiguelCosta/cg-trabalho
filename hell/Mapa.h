#pragma once

#include "Agente.h"
#include "Chave.h"
#include "Edificio.h"
#include "Torre.h"
#include "Radar.h"
#include "defines.h"
#include <IL/il.h>



class Mapa	{
public:

	//Missao
	Agente				*agente;
	Chave				*chaves[NUM_CHAVES];
	Edificio			*edificio;
	Torre				*torres[3];
	Radar				*radar;

	// variavel que diz quantas chaves foram apanhadas
	int num_chaves_apanhadas;

	Mapa(void);
	/** desenha o terreno */
	void terreno(void);
	/** textura para o terreno */
	void initTextura(char * nome_textura);

	// conta quantas chaves já foram apanhadas
	int chaves_apanhadas(void);

	// coloca no ecra quantas chaves ja foram apanhadas e o que tem de fazer
	void desenhaEstadoJogo(GLuint x, GLuint y);

	/**desenha tudo no mapa */
	void desenhar(void);
	~Mapa(void);

private:
	// imagem de textura
	unsigned int textura_solo, img_textura;
	int textura_w, textura_h;
	unsigned char *textura_data;

};

