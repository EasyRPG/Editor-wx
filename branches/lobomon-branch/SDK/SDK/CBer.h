/**
	@file
	@brief		ストリームを介せずにBER圧縮整数を操作する
	@author		sue445
*/
#ifndef _INC_CBER
#define _INC_CBER

#include <stdio.h>
#include "sueLib/smart_buffer.h"

using namespace sueLib;

/// BER操作系
class CBer{
private:
	static	int  int2ber(int nData, void* pDst=NULL, unsigned int nSize=0);	///< int -> BER

public:
	static	void MemoryReverse(void* pData, unsigned int nSize);	///< メモリデータを反転する

	static	int				GetBerNumber(smart_buffer& buf);		///< バッファから直接BER圧縮整数を取得
	static	smart_buffer	SetBerNumber(int nData);				///< バッファに直接BER圧縮整数をセット
};

#endif
