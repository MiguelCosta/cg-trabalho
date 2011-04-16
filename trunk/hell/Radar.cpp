
#include "util.h"
#include "Mapa.h"
#include "Radar.h"
#include "defines.h"

extern Mapa * _mapa;

int radar(float &dist)	{
	float x1,y1,z1,x2,y2,z2;
	float act,min = 1e+10;

	x1 = _mapa->agente->posicao[XX];
	y1 = _mapa->agente->posicao[YY];
	z1 = _mapa->agente->posicao[ZZ];

	int i=0;
	do {
		x2 = _mapa->chaves[i]->posicao[XX];
		y2 = _mapa->chaves[i]->posicao[YY];
		z2 = _mapa->chaves[i]->posicao[ZZ];

		act = distancia3d(x1,y1,z1,x2,y2,z2);
		if(act < min) min = act;
	}while(i < NUM_CHAVES);

	if(min <= RADAR_ALCALCE)	{
		dist = min;
		return 0;
	}
	
	dist = 0;
	return 1;
}
