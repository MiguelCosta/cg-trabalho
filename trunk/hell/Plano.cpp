#include "Plano.h"


float Plano::dist(Vec3 p)	{
	return (normal.getX()*(ponto.getX()-p.getX())+
		normal.getY()*(ponto.getY()-p.getY())+
		normal.getZ()*(ponto.getZ()-p.getZ()));
}

void Plano::setNormalPonto(Vec3 _normal, Vec3 _ponto)	{
	normal.setX(_normal.getX());
	normal.setY(_normal.getY());
	normal.setZ(_normal.getZ());

	ponto.setX(_ponto.getX());
	ponto.setY(_ponto.getY());
	ponto.setZ(_ponto.getZ());
}


void Plano::set3pontos(Vec3 a,Vec3 b,Vec3 c)	{

	Vec3 d1 = c-a;
	Vec3 d2 = b-a;

	normal = d1*d2;
	ponto = a;
}
