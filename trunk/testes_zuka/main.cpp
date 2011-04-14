
#include <iostream>

#include "mapa.h"
#include "show.h"

Mapa * _mapa;


int main(int argc, char **argv) {

	
	// Codigo do programa
	_mapa = new Mapa();
	
	// Codigo OpenGL
	startShow(argc,argv);
	
	return 0;
}