#pragma once

class Teclado	{
public:
	bool teclas[4];

	Teclado(void);
	~Teclado(void);

	void recebeTeclado(unsigned char key, int x, int y);
};



