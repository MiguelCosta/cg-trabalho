

#include "show.h"

/** Defines privados */
// Eixos cartezianos
#define XX	0
#define YY	1
#define ZZ	2
// Tipos de vista
#define PRIMEIRA_PESSOA	1
#define TERCEIRA_PESSOA	2
#define	MODO_DEUS		3

/** Variaveis globais Privadas*/
// Tipo de vista
int tipo_de_vista = PRIMEIRA_PESSOA;
// posicao do agente
GLdouble posicao[3];
// Direcao da camera
GLdouble direcao[3] = {	0.0f, 0.0f, -1.0f };

/**
 * Recebe input do teclado
 */
void recebeTeclado(unsigned char key, int ratoX, int ratoY)	{
	switch(key)	{
		case 'W':
		case 'w':
			teclas[WW] = true;
			break;
		case 'S':
		case 's':
			teclas[SS] = true;
			break;
		case 'A':
		case 'a':
			teclas[AA] = true;
			break;
		case 'D':
		case 'd':
			teclas[DD] = true;
			break;
		default:
			;
	}

}


