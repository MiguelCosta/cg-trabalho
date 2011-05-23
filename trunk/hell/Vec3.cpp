
#include <math.h>
#include "Vec3.h"



Vec3::Vec3(float x, float y, float z)	{
	set(x,y,z);
}

void Vec3::set(float x, float y, float z)	{
	setX(x);
	setY(y);
	setZ(z);
}

void Vec3::setX(float x)	{
	x1 = x;
}

void Vec3::setY(float y)	{
	y1 = y;
}

void Vec3::setZ(float z)	{
	z1 = z;
}

void Vec3::get(float result[3])	{
	result[0] = x1;
	result[1] = y1;
	result[2] = z1;
}

float Vec3::getX()	{
	return x1;
}

float Vec3::getY()	{
	return y1;
}

float Vec3::getZ()	{
	return z1;
}

float Vec3::dist(Vec3 q)	{
	float xPart = x1-q.getX();
	xPart *= xPart;
	float yPart = y1-q.getY();
	yPart *= yPart;
	float zPart = z1-q.getZ();
	zPart *= zPart;
	float result = (sqrt(xPart+yPart+zPart));
	return result;
}

void Vec3::normalize()	{
	Vec3 O(0.0,0.0,0.0);
	float norma =  this->dist(O);
	x1 = x1/norma;
	y1 = y1/norma;
	z1 = z1/norma;
}

const Vec3 Vec3::operator+(const Vec3 &other)	{
	Vec3 op = other;
	Vec3 res;
	
	res.set(x1+op.getX(),y1 +op.getY(),z1+op.getZ());
	return res;
}

Vec3 Vec3::operator-(Vec3 &other)	{
	Vec3 op = other;
	Vec3 simetrico(-(op.getX()),-(op.getY()),-(op.getZ()));
	Vec3 res = this->operator+(simetrico);
	return res;
}

const Vec3 Vec3::operator*(const Vec3 &other) {
	Vec3 o = other;
    Vec3 res;

	res.setX(y1 * o.getZ() - z1 * o.getY() );
    res.setY(z1 * o.getX() - x1 * o.getZ() );
    res.setZ(x1 * o.getY() - y1 * o.getX() );

    return (res);
}


