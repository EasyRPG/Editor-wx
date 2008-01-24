#ifndef LMT_H
#define LMT_H
#include <vector>
struct Sound_effect
{
	std::string Name_of_Sound_effect;
	int Fadein;
	int Volume; 
	int Tempo; 
	int Balance;
};

struct DataofTree
{
	std::string	strName;	///< 0x01 nombre del mapa
	int		intIdMapF;	///< 0x02 ID del mapa padre
	int		intDepth;	///< 0x03 Profundidad del árbol
	int		intFlagMA;	///< 0x04 Bandera de mapa o área
	int		intXbar;	///< 0x05 Barra de desplazamiento  X del mapa
	int		intYbar;	///< 0x06 Barra de desplazamiento Y del mapa
	int		intSon;		///< 0x07 Tiene subrama (hijo)
	int		intMusic;	///< 0x0B Música de fondo 
	Sound_effect	stcMusic;	///< 0x0C Música de fondo (archivo) String
	int		intBatle;	///< 0x15 Fondo de batalla 
	std::string	strBatle;	///< 0x16 Fondo de batalla (archivo) String
	int		intTelepor;	///< 0x1F Teletransporte
	int		intScape;	///< 0x20 Escapar Entero
	int		intSave;	///< 0x21 Guardar Entero
	std::vector < int > vcEnemyGroup; ///< 0x29 arreglo dos dimensiones con enemigos
	int		intNofsteeps;	///< 0x2C Pasos entre encuentros
					///< 0x33 Datos del área
	int		intAreaX1;
	int		intAreaY1;
	int		intAreaX2;
	int		intAreaY2;
};

class LMT
{
	public: 
		int 	intPartymapId;	///< 0x01 Party start map
		int	intPartymapX;	///< 0x02 Party start X
		int	intPartymapY;	///< 0x03 Party start Y
		int	intSkiffId;	///< 0x0B Skiff start map
		int	intSkiffX;	///< 0x0C Skiff start X
		int	intSkiffY;	///< 0x0D Skiff start Y
		int	intBoatId;	///< 0x15 Boat start map
		int	intBoatX;	///< 0x16 Boat start X
		int	intBoatY;	///< 0x17 Boat start Y
		int	intAirshipId;	///< 0x1F Airship start map
		int	intAirshipX;	///< 0x20 Airship start X
		int	intAirshipY;	///< 0x21 Airship start Y
		unsigned int	treesize;
		std::vector <DataofTree> str_Vector;
		std::vector <int> vc_int_treeorder;
		// Methods
		bool	Load(std::string Filename);
		void	ShowInformation();
	private:
		void	GetNextChunk(FILE * Stream);
		void	leafclear(DataofTree * leaf);
};

#endif
