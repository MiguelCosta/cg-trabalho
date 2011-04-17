




typedef enum e_teclas {
		ANDAR_FREN,
		ANDAR_TRAS,
		ANDAR_DIR,
		ANDAR_ESQ,

		NUM_TECLAS,
	} COD_TECLAS;


	/** Funcoes */
	void processarTecladoEspecialDown(int key, int x, int y);

	void processarTecladoEspecialUp(int key, int x, int y);

	void processarTecladoDown	(unsigned char key, int x, int y);

	void processarTecladoUp		(unsigned char key, int x, int y);

	void processMouseButtons	(int button, int state, int xx, int yy);
	
	void processMouseMotion		(int xx, int yy);

	void processarMovimentoRato(int x, int y);
