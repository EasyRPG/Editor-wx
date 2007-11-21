/**
	@file
	@brief		ツクール2000/2003系ファイルの入出力の基本となるクラス
	@note		いろいろなところからこのクラスを継承しますし、このクラス単体でも使用できます。

	@author		sue445
*/
#include "CRpgIOBase.h"


//=============================================================================
/**
	ファイルを開く(ヘッダチェック有り)

	@param	szFile		[in] 開くファイル

	@retval	true		ファイルのオープンに成功
	@retval	false		ファイルのオープンに失敗
*/
//=============================================================================
bool CRpgIOBase::OpenFile(const char* szFile)
{
	// ファイルが開けない
	if(!OpenFromFile(szFile, false)){	
     printf("no encuentro el nombre\n ");                         
 return false;}

	// ヘッダが一致しない
	if(ReadString() != GetHeader())	{		
          printf("la cabecera es distint no encuentro el nombre\n ");              
                    	return false;}

	return true;
}

//=============================================================================
/**
	ツクール仕様のデータ([データサイズ][実データ]という形式)を読み込む

	@return	buf			出力したバッファ
*/
//=============================================================================
smart_buffer CRpgIOBase::ReadData()
{	CRpgIOBase		st;
	smart_buffer buf;
	int length = ReadBerNumber();	// バッファ長
// printf(" bufer  %d \n",length);
	if(length>0){
		buf.New(length);
		Read(buf, length);
	}/*
if(length==1)
{
st.OpenFromMemory(buf.GetConstPtr(), buf.GetSize());
 printf(" dato  %d \n",st.ReadBerNumber());
}*/
	return buf;
}

//=============================================================================
/**
	ツクール仕様の文字列を読み込む

	@return	str			取得した文字列
*/
//=============================================================================
string CRpgIOBase::ReadString()
{
	smart_buffer buf = ReadData();
	string str;

	if(buf.GetSize()>0)		str.assign(buf.GetPtr(), buf.GetSize());

	return str;
}


//=============================================================================
/**
	unsigned char -> bool配列

	@param	num			[in] 入力元のデータ
	@param	flag		[out] 出力先の配列
*/
//=============================================================================
void CRpgIOBase::ByteToBool(unsigned char num, bool flag[8]) const
{
	/*
	ZeroMemory(flag, sizeof(bool)*8);
	if(num & 0x01)	flag[0] = true;
	if(num & 0x02)	flag[1] = true;
	if(num & 0x04)	flag[2] = true;
	if(num & 0x08)	flag[3] = true;
	if(num & 0x10)	flag[4] = true;
	if(num & 0x20)	flag[5] = true;
	if(num & 0x40)	flag[6] = true;
	if(num & 0x80)	flag[7] = true;
	*/

	/*
	flag[0] = ((num & 0x01) != 0);
	flag[1] = ((num & 0x02) != 0);
	flag[2] = ((num & 0x04) != 0);
	flag[3] = ((num & 0x08) != 0);
	flag[4] = ((num & 0x10) != 0);
	flag[5] = ((num & 0x20) != 0);
	flag[6] = ((num & 0x40) != 0);
	flag[7] = ((num & 0x80) != 0);
	*/

	unsigned int i, mask = 1;
	for(i = 0; i < 8; i++){
		flag[i] = ((num & mask) != 0);
		mask <<= 1;
	}
}

