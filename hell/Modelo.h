

#include "../md2loader/Md2Player.h"
#include <string>

class Modelo	{
public:
	float posicao[3];
	float direcao[3];
	float orientacao[3];

	Md2Player * modeloMD2;
	int modoVista;

	Modelo(char *pasta);
	~Modelo(void);
};

