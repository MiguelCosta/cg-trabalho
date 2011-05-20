
#ifndef __DEFINES
#define __DEFINES

typedef enum e_teclas {
	ANDAR_FREN,
	ANDAR_TRAS,
	ANDAR_DIR,
	ANDAR_ESQ,
	CORRER,

	NUM_TECLAS,
} COD_TECLAS;

// Eixos cartesianos
#define	XX	0
#define	YY	1
#define	ZZ	2

// Tamanho do Mapa
#define MAPA_TAM	256

#define TEXTURA_TERRENO "texturas/terreno/relva.png"

// numero de chaves
#define NUM_CHAVES	3
#define APANHA_CHAVE 5
#define CHAVE_ANGULO_ROTACAO 1

// numero de torres
#define NUM_TORRES	3
#define DISTANCIA_TORRE_AGENTE 50

// edificio
#define DISTANCIA_AGENTE_NO_EDIFICIO 10

// velocidade do agente
#define AGENTE_VELOCIDADE_INICIAL	0.2

// distancia a que a camara na terceira pessoa est� do agente
#define CAMARA_TERCEIRA_PESSOA			1.5
#define CAMARA_3_P_ZZ					3
#define CAMARA_3_P_YY					1.5

// Radar
#define RADAR_ALCALCE 50

// Velocidade do rato
#define VELOCIDADE_RATO_ALPHA	0.2
#define VELOCIDADE_RATO_BETA	0.5

// Pi!
#define PI						3.14159265

#endif