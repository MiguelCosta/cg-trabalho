
#pragma once

#ifndef __VIEW
#define __VIEW

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <IL/il.h>

/* Tipos de camera */
#define FIST_PERSON		1
#define THIRD_PERSON	2
#define GOD_MODE		3
#define _ANTERIOR		4
#define _ANTERIOR_		5

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

void renderScene(void); // colcoar no mapa todos os objectos

//void cria_menu();		// cria um menu



#endif