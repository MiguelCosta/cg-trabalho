
#pragma once

#ifndef __VIEW
#define __VIEW

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <IL/il.h>

/* Tipos de camera */
#define PRIMEIRA_PESSOA			1
#define TERCEIRA_PESSOA			2
#define GOD_MODE				3
#define PRIMEIRA_PESSOA_NOVO	4

#define XX 0
#define YY 1
#define ZZ 2

// velocidade de movimento da camara
#define VELOCIDADE_CAM 1

// numero de árvores no mapa
#define ARVORES 5000

// funções para o teclado
void keyboard(unsigned char key, int x, int y);
void keybord_special(int key, int x, int y);

// funções do rato
void processMouseButtons(int button, int state, int xx, int yy);
void processMouseMotion(int xx, int yy);
void ratoPassivo(int x, int y);

void renderScene(void); // colcoar no mapa todos os objectos

//void cria_menu();		// cria um menu



#endif