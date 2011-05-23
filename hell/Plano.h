#pragma once

#include "Vec3.h"

class Plano	{
	Vec3 normal;
	Vec3 ponto;

public:
	Plano(void);

	float dist(Vec3 P);
	void setNormalPonto(Vec3 normal, Vec3 ponto);
	void set3pontos(Vec3 a,Vec3 b,Vec3 c);

	~Plano(void);
};

