/**
	@file
	@brief		CBasicStreamを利用したBER圧縮整数の入出力。\n
				BER圧縮整数についてはこの辺で。\n
				http://www.stellar.ac/~komai/unix/ber/index.html

	@author		sue445
*/
#ifndef _INC_CBERSTREAM
#define _INC_CBERSTREAM

#include "sueLib/CBasicStream.h"
#include "sueLib/smart_buffer.h"

using namespace sueLib;


/// BER圧縮整数の入出力
class CBerStream : public CBasicStream{
public:
	CBerStream(){}										///< コンストラクタ
	~CBerStream(){}										///< デストラクタ

	int ReadBerNumber(int* lpReadByte=NULL);			///< BER圧縮整数を1つ取り出す
	int WriteBerNumber(int nData, bool bCalc=false);	///< BER圧縮整数を1つ書き出す
};


#endif
