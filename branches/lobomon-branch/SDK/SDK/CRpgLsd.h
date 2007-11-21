/**
	@file
	@brief		Save??.lsd(LcfSaveData)を管理するクラス
	@author		sue445
*/
#ifndef _INC_CRPGLSD
#define _INC_CRPGLSD

#include "CRpgIOBase.h"

const int MAX_SAVEDATA = 15;		///maximo de saves



class CRpgLsd : public CRpgIOBase{
private:
	const char* GetHeader(){ return "LcfSaveData"; }	///< ファイルごとの固有ヘッダ(CRpgIOBaseからオーバーライドして使います)

public:
	CRpgArray1		ArrayLoading;						//< 0x64:セーブデータ選択画面の情報
    CRpgArray2		ArrayLoading2;	
struct Data{
	
		///< 0x01 arreglo
	string strName;		  ///< 0x0B nombre del save
int intlevel;		///< 0x0C nivel del heroe
int intHp;		///< 0x0D hp del heroe	
	string strNFP1;		  ///< 0x15 nombre faceset perso 1
int intIDFP1;	///< 0x16 id facet p1
	string strNFP2;		  ///< 0x17 nombre faceset perso 2
int intIDFP2;	///< 0x18 id facet p2
	string strNFP3;		  ///< 0x19 nombre faceset perso 3
int intIDFP3;	///< 0x1A id facet p3
	string strNFP4;		  ///< 0x1B nombre faceset perso 4
int intIDFP4;	 ///< 0x1C id facet p4
	//
}saData;//yo usaria vector

// informacion de parametros vairables tipe 0x65

struct VData{
 //npi
/*  1  tama 2 ?
   11  tama 2 //tentativa de variables
   32  tama 1
   34  tama 1
   71  tama 4 ?
   72  tama 4 ?
   73  tama 4 ?
   74  tama 4 ?
   75  tama 18 Musica
   76  tama 9 ??(OFF)
   77  tama 9 ??(OFF)
   78  tama 9 ??(OFF)
   79  tama 4 ?
   80  tama 4 ?
   81  tama 4 ?
   82  tama 4 ?
   91  tama 4 ?
   92  tama 4 ?
   93  tama 4 ?
   94  tama 4 ?
   95  tama 4 ?
   96  tama 4 ?
   97  tama 4 ?
   98  tama 4 ?
   99  tama 4 ?
   100  tama 4 ?
   101  tama 4 ?
   102  tama 4 ?
   111  tama 2 
   112  tama 2 
   113  tama 2 
   114  tama 2 
   115  tama 2 
   116  tama 2 
   125  //fondo de batalla
   131  tama 2 */
}saVData;//



/*//id 0x68// posicion de guardado
   11  id de mapa
   12  posicion en X
   13  posicion en Y
   21  direccion en la que mira
   22  direccion en la que mira?
   33  tama 2 ?
   35  tama 2
   37  tama 2 ?
   41  posicion de la imagen
   52  posicion de la imagen
   53  tama 2 ?
   73  nombre del cahra a mostrar
   75  tama 2 ?
   124  //cambia con la posicion 
   131  //cambia con la posicion 
   132  tama 3 ﾄ?*/
/*   //0x6A //0x69 //0x6B //vehiculos
   11  id de mapa
   12  posicion en x
   13  posicion en y
   21  tama 2 ?
   22  tama 2 ?
   33  tama 2 ?
   35  tama 2
   37  tama 2 ?
   41  tama 4 ?
   73  nombre del vehiculo 
   74  id de numero de imagen
   101  tama 2 ?*/
/*0x6C informacion del grupo 2
 filas 1 m columnas 1  tamaｱo 1  numero 1 ?
 filas 1 m columnas 2  tamaｱo 1  numero 1 ?
 filas 1 m columnas 31  tamaｱo 1  numero 18 ? //nivel
 filas 1 m columnas 32  tamaｱo 2  numero 7820 ｢?//exp
 filas 1 m columnas 33  tamaｱo 1  numero 0
 filas 1 m columnas 34  tamaｱo 1  numero 0
 filas 1 m columnas 51  tamaｱo 1  numero 1 
 filas 1 m columnas 52  tamaｱo 2  numero 49 
 filas 1 m columnas 61  tamaｱo 10 ?
 filas 1 m columnas 71  tamaｱo 2  numero 1338 //hp
 filas 1 m columnas 72  tamaｱo 1  numero 73 I//mp
 filas 1 m columnas 80  tamaｱo 28 
 filas 1 m columnas 81  tamaｱo 1  numero 10
 filas 1 m columnas 82  tamaｱo 20
*/   

/*0x6D // informacion de los objetos
  columnas 1  tamaｱo 1  numero 4 ?
  columnas 2  tamaｱo 8 ?
  columnas 11  tamaｱo 1  numero 4 //num obj
  columnas 12  tamaｱo 8 ?         //arreglo de objetoss
  columnas 13  tamaｱo 4  numero 1 ????
  columnas 14  tamaｱo 4  numero 0
  columnas 42  tamaｱo 1  numero 5 ?
  */ 

public:
	CRpgLsd(){}											///< コンストラクタ
	~CRpgLsd(){}										///< デストラクタ

	bool Init(int nSaveNum, const char* szDir="");		///< 初期化
};

#endif
