
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
#define ARVORES 5000




void keyboard(unsigned char key, int x, int y);
void drawTree();
void placeTrees();
void drawWorld();
void drawBoneco();
void drawPlane();
void scene();
void renderScene(void);
void processMouseButtons(int button, int state, int xx, int yy);
void processMouseMotion(int xx, int yy);
void cria_menu();








#endif