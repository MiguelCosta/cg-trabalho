#pragma once


class Radar
{
public:
	/** 
	* Ditancia a que a chave mais perto est� do agente
	* se a distancia for -1 � porque n�o est� ao alcance do radar 
	*/
	GLfloat dist;

	Radar(void);

	/* calcula qual a dist�ncia do objecto mais pr�ximo */
	void distancia(void);

	/* desenha o radar na janela recebendo a posi��o */
	void desenha(GLuint x, GLuint y);
	
};
