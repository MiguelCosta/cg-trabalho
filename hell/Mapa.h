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
	
	// flag que diz se já apanhou as chaves todas e se depois foi até ao edificio
	bool flagJogoCompleto;

	Mapa(void);
	/** desenha o terreno */

	void terreno(void);

	/** textura para o terreno */
	void initTextura(char * nome_textura);

	void initRelevo(char * nome_relevo);

	// conta quantas chaves já foram apanhadas
	int chaves_apanhadas(void);

	// verifica se jogo já está completo ou não, se estiver coloca a flagJogoCompleto a true
	void verificaEstadoJogo(void);

	// coloca no ecra quantas chaves ja foram apanhadas e o que tem de fazer
	void desenhaEstadoJogo(GLuint x, GLuint y);

	/**desenha tudo no mapa */
	void desenhar(void);
	~Mapa(void);

private:
	// imagem de textura
	unsigned int textura_solo, img_textura, img_relevo;
	int textura_w, textura_h, relevo_w, relevo_h;
	unsigned char *textura_data, *relevo_data;




};

