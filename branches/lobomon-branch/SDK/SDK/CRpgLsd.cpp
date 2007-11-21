/**
	@file
	@brief		Save??.lsd(LcfSaveData)を管理するクラス
	@author		sue445
*/
#include "CRpgLsd.h"


//=============================================================================
/**
	初期化

	@param	nSaveNum		[in] セーブデータ番号(1～15)
	@param	szDir			[in] 読み込み先のディレクトリ

	@retval					セーブデータの読み込みに成功
	@retval					セーブデータの読み込みに失敗
*/
//=============================================================================
bool CRpgLsd::Init(int nSaveNum, const char* szDir)
{
	int type,seek;
	char file[256];
	smart_buffer	buf;
	string			strFile;


	// セーブデータの番号がおかしい
	if(nSaveNum<1 || nSaveNum>MAX_SAVEDATA)		return false;

	bInit = false;
	sprintf(file, "Save%02d.lsd", nSaveNum);
	if(strlen(szDir)){
		strFile += szDir;
		strFile += "\\";
	}
	strFile += file;

	// セーブデータじゃない
	if(!OpenFile(strFile.c_str()))		return false;


	// データを読み込む
	while(!IsEof()){
        seek=GetSeek();//la psicion atees de lalectura dle buffer 
        type = ReadBerNumber();
		printf("\n tipo %d ",type); 
		buf = ReadData();
		switch(type){
		case 0x64:	//informacion del de guardar
	/*	ArrayLoading = CRpgUtil::GetArray1(buf);
		    
            saData.intlevel=ArrayLoading.GetNumber(0x0C);
            saData.intHp=ArrayLoading.GetNumber(0x0D);
            saData.intIDFP1=ArrayLoading.GetNumber(0x16);
            saData.intIDFP2=ArrayLoading.GetNumber(0x18);
            saData.intIDFP3=ArrayLoading.GetNumber(0x1A);
            saData.intIDFP4=ArrayLoading.GetNumber(0x1C);
            saData.strName=ArrayLoading.GetString(0x0B);//nobre del prota 1
            saData.strNFP1=ArrayLoading.GetString(0x15);//nobre del prota 1
            saData.strNFP2=ArrayLoading.GetString(0x17);//nobre del prota 1
            saData.strNFP3=ArrayLoading.GetString(0x19);//nobre del prota 1
            saData.strNFP4=ArrayLoading.GetString(0x1B);//nobre del prota 1*/
            break;
		case 0x65:	// informacion de parametros vairables
           printf("\n pos %d ",seek); 
           ArrayLoading = CRpgUtil::GetArray1(buf);       
         // ArrayLoading2 = CRpgUtil::GetArray2(buf); 
			break;
		case 0x66://inutil 
            printf("\n pos %d ",seek);
           //  ArrayLoading = CRpgUtil::GetArray1(buf);
            // ArrayLoading2 = CRpgUtil::GetArray2(buf); 
			break;
		case 0x67://inutil 
          //  printf("\n pos %d ",seek);
          //   ArrayLoading = CRpgUtil::GetArray1(buf);
			break;
		case 0x68:// posicion de guardado
          //   printf("\n pos %d ",seek); 
           // ArrayLoading = CRpgUtil::GetArray1(buf); 
			break;
		case 0x69://vehiculos info
        //  printf("\n pos %d ",seek); 
        //  ArrayLoading = CRpgUtil::GetArray1(buf); 
			break;
		case 0x6A://vehiculos info
       //   printf("\n pos %d ",seek); 
       //   ArrayLoading = CRpgUtil::GetArray1(buf); 
			break;
		case 0x6B://vehiculos info
      //    printf("\n pos %d ",seek); 
      //    ArrayLoading = CRpgUtil::GetArray1(buf); 
			break;
		case 0x6C:	// informacion del grupo 2 dimenciones
         //   printf("\n pos %d ",seek); 
           //  ArrayLoading2 = CRpgUtil::GetArray2(buf); 
			break;
		case 0x6D:	// informacion de los objetos
		  // printf("\n pos %d ",seek); 
          // ArrayLoading = CRpgUtil::GetArray1(buf); 
			break;
		case 0x6E://inutil 
			break;
		case 0x6F://inutil 
			break;
		case 0x70://inutil
			break;
		case 0x71://inutil
			break;
		case 0x72://inutil
			break;
		}
	}

	bInit = true;
	return true;
}

