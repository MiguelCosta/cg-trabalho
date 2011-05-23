#pragma once

#include "Bala.h"

class ListaBalas
{
public:
	
	Bala *listaBalas[MAX_BALAS];

	int indice;

	void addBala(GLdouble x, GLdouble y, GLdouble z, GLdouble ang);
	void incIndiceBalas(void);
	void desenha(void);
	void init(void);
	ListaBalas(void);
	~ListaBalas(void);
};

