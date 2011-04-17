
#include "md2loader\Md2Player.h"

class Modelo	{
public:
	float posicao[3];
	float direcao[3];
	float orientacao[3];

	Md2Player * modeloMD2;
	int modoVista;

	Modelo(const string &pasta);
	~Modelo(void);
};

