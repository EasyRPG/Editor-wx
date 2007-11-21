/**
	@file
	@brief		CBasicStreamを利用したBER圧縮整数の入出力。\n
				BER圧縮整数についてはこの辺で。\n
				http://www.stellar.ac/~komai/unix/ber/index.html

	@author		sue445
*/
#include "CBerStream.h"
#include "CBer.h"


//=============================================================================
/**
	ストリームからBER圧縮整数を1つ取り出す

	@param	lpReadByte		[out] ストリームから読み込んだバイト数が返る(NULL指定時は返らない)

	@return					BER圧縮整数を普通の整数に直した値
*/
//=============================================================================
int CBerStream::ReadBerNumber(int* lpReadByte) // el espasio se deside en base a esto
{
	unsigned char c;
	int data = 0, readbyte = 0;


	while(!IsEof()){
		if(Read(&c, 1)==0)	break;// si el caracter es 0 termina
		readbyte++; //si no aumenta el numero leido

	 
		// 1000 0000 & c
		// para darse la condicion c tiene que ser menor a 0x80 0XXX XXXX 
		if((c & 0x80)==0){
			data = (data<<7) + c;
//		printf("d %d ",c);
        	//c
			// mas el ultimo digito posicionado en la primera poscion
			break;//terimana
		}
		else{
			data = (data<<7) + (c & 0x7F);
//			printf("dp %d ",c);
			//  0111 1111 & c
			// deja pasar todo menos el primer digito
			// mas el ultimo digito posicionado en la primera poscion
		}
	}

	//si el lpReadByte es cero retorna el pointer de readbyte
	if(lpReadByte)	*lpReadByte = readbyte;

	return data; //retorna la direccion final
}

//=============================================================================
/**
	BER圧縮整数を1つ書き出す

	@param	nData	[in] 変換元の整数
	@param	bCalc	[in] trueの時は必要サイズの計算だけを行いストリームには書き出さない

	@return			ストリームに書き出したバイト数(ストリームに書き出すのに必要なバイト数)
*/
//=============================================================================
int CBerStream::WriteBerNumber(int nData, bool bCalc)
{
	// BERの構造上一度バッファに書き出しておく必要がある
	smart_buffer buf = CBer::SetBerNumber(nData);
	if(buf.GetSize()>0 && !bCalc){
		Write(buf, buf.GetSize());
	}

	return buf.GetSize();
}

