#pragma once

class Vec3	{
	float x1,y1,z1;

public:
	Vec3(void);
	Vec3(float x, float y, float z);

	void get(float result[3]);
	float getX();
	float getY();
	float getZ();

	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float dist(Vec3 q);
	void normalize();

	const Vec3 operator+(const Vec3 &other);
	const Vec3 operator-(const Vec3 &other);
	const Vec3 operator*(const Vec3 &other);
	const Vec3 operator*(const float &other);
};

