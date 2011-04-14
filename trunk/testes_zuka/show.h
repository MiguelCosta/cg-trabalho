

#pragma once

/** Defines publicos */
// Codigos das teclas
#define WW	0
#define AA	1
#define SS	2
#define DD	3


/** Variaveis globais */
// Mapa
extern Mapa * _mapa;
// Teclas de comando
bool teclas[10];

/**
 * Inicializacao do OpenGL
 */
void startShow(int argc, char **argv);

