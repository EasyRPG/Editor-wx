/**
	@file
	@brief		Save??.lsd(LcfSaveData)‚ğŠÇ—‚·‚éƒNƒ‰ƒX
	@author		sue445
*/
#ifndef _INC_CRPGLMT
#define _INC_CRPGLMT

#include "CRpgIOBase.h"

//const int MAX_SAVEDATA = 15;		///maximo de saves



class CRpgLmt : public CRpgIOBase{
private:
		///< cabezera del archivo
	const char* GetHeader(){ return "LcfMapTree"; }
public:

	struct DataofTree{
	string strName;		  ///< 0x01 nombre del mapa
    int intIdMapF;///< 0x02 	ID del mapa padre 
    int intDepth;///< 0x03   Profundidad del árbol 
    int intFlagMA;///< 0x04 	Bandera de mapa o área 
    int intXbar;///< 0x05 	Barra de desplazamiento  X del mapa
    int intYbar;///< 0x06 	Barra de desplazamiento Y del mapa
    int intSon;///< 0x07 	Tiene subrama (hijo)
    int intMusic;///< 0x0B 	Música de fondo 
    string strMusic;	///< 0x0C 	Música de fondo (archivo) String
    int intBatle;///< 0x15 	Fondo de batalla 
    string strBatle;	///< 0x16 	Fondo de batalla (archivo) String
    int intTelepor;///< 0x1F 	Teletransporte
    int intScape;///< 0x20 	Escapar 	Entero 
    int intSave;///< 0x21 	Guardar 	Entero 
    smart_array< int > intsaEnemy;//< 0x29  arreglo dos dimenciones	 con enemigos	
    int intNofsteeps;///< 0x2C 	Pasos entre encuentros
///< 0x33 	Datos del área //no parecen nada
    };//

struct InitDat{       
    int intPartymapId;//0x01		Party start map
    int intPartymapX;//0x02		Party start X
    int intPartymapY;//0x03		Party start Y
    int intSkiffId;//0x0B		Skiff start map
    int intSkiffX;//0x0C		Skiff start X
    int intSkiffY;//0x0D		Skiff start Y
    int intBoatId;//0x15		Boat start map
    int intBoatX;//0x16		Boat start X
    int intBoatY;//0x17		Boat start Y
    int intAirshipId;//0x1F		Airship start map
    int intAirshipX;//0x20		Airship start X
    int intAirshipY;//0x21		Airship start Y       
}InitD;

    smart_array< DataofTree >	saDataofTree;//yo usaria vector
    int treesize;
    int begin;
    int end;
public:
	CRpgLmt(){}											///< constructor
	~CRpgLmt(){}										///< destructor
    smart_buffer ReadData2();
	bool Init(const char* szDir="");	//init
};

#endif
