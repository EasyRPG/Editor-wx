/**
	@file
	@brief		ストリームを介せずにBER圧縮整数を操作する
	@author		sue445
*/
#include "CBer.h"
#include "CBerStream.h"


//=============================================================================
/**
	int→BER変換(1回目にサイズを調べておいて、2回目でデータをセットする)

	@param	nData		[in] 変換元の整数
	@param	pDst		[out] 出力先バッファ(サイズ計算をしたい場合はNULLを指定します)
	@param	nSize		[in] 出力先バッファのサイズ

	@return				ストリームに書き出したバイト数(ストリームに書き出すのに必要なバイト数)
*/
//=============================================================================
int CBer::int2ber(int nData, void* pDst, unsigned int nSize)
{
	unsigned int data = (unsigned int)nData;
	unsigned int i = 0, j;
	unsigned char* c = reinterpret_cast< unsigned char* >( pDst );

	for(;;){
		j = data & 0x7F;

		if(pDst && i<nSize){
			if(i==0)	c[i] = (unsigned char)j;
			else		c[i] = (unsigned char)(j|0x80);
		}
		i++;

		data>>=7;
		if(data==0)		break;
	}

	if(pDst)	MemoryReverse(pDst, nSize);

	return i;
}

//=============================================================================
/**
	メモリの中身を反転する

	@param	pData		[in,out] 反転するメモリデータ
	@param	nSize		[in] メモリデータのサイズ
*/
//=============================================================================
void CBer::MemoryReverse(void* pData, unsigned int nSize)
{
	if(pData==NULL || nSize<2)		return;

	unsigned char* p = reinterpret_cast< unsigned char* >( pData );
	unsigned char  c;
	unsigned int max = nSize / 2;

	for(unsigned int i = 0; i < max; i++){
		c				= p[i];
		p[i]			= p[nSize-1-i];
		p[nSize-1-i]	= c;
	}
}

//=============================================================================
/**
	バッファから直接BER圧縮整数を取得する

	@param	buf			[in] BER圧縮整数が格納されているバッファ

	@return				BER圧縮整数を普通の整数に直した値
*/
//=============================================================================
int CBer::GetBerNumber(smart_buffer& buf)
{int i;
	CBerStream st;

	if(st.OpenFromMemory(buf, buf.GetSize())){
		i= st.ReadBerNumber();
		  printf(" numero %d",i);
return i;

	}

	return 0;
}

//=============================================================================
/**
	バッファにBER圧縮整数をセットする

	@param	nData		[in] 変換元の整数

	@return				出力したバッファ
*/
//=============================================================================
smart_buffer CBer::SetBerNumber(int nData)
{
	smart_buffer buf;
	int size = int2ber(nData);

	if(size>0){
		buf.New(size);
		int2ber(nData, buf, buf.GetSize());
		return buf;
	}

	return buf;
}
