
/*

#include "Modelo.h"


Modelo::Modelo(const string &pasta)	{

	string dirname ("Modelos/");
	dirname.append(pasta);

	if (dirname.find_last_of ('/') == dirname.length () - 1)
		dirname.assign (dirname, 0, dirname.find_last_of ('/'));

	// Get base dir for player if a *.md2 file is given
	if (dirname.find (".md2") == dirname.length () - 4)

	#ifdef _WIN32
		dirname.assign (dirname, 0, dirname.find_last_of ('\\'));
	#else
		dirname.assign (dirname, 0, dirname.find_last_of ('/'));
	#endif

	modeloMD2 = new Md2Player(dirname);
	modoVista = 0;
}


Modelo::~Modelo(void)	{

}
*/