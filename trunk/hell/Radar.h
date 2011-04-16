#pragma once


class Radar
{
public:
	/** 
	* Ditancia a que a chave mais perto está do agente
	* se a distancia for -1 é porque não está ao alcance do radar 
	*/
	GLfloat dist;

	Radar(void);

	/* calcula qual a distância do objecto mais próximo */
	void distancia(void);

	/* desenha o radar na janela recebendo a posição */
	void desenha(GLuint x, GLuint y);
	
};
