/**
	@file
	@brief		ZLib compression class
	@note		<Reference URL> http://oku.edu.mie-u.ac.jp/~okumura/compression/zlib.html
	@author		sue445
*/
#ifndef _INC_CZLIB
#define _INC_CZLIB

#include "CBasicStream.h"
#include "smart_buffer.h"

namespace sueLib {

class CZLib{
public:
	static	bool Decompress(CBasicStream* pstInput, CBasicStream* pstOutput, unsigned int* lpSize=NULL);					///< zlib�œW�J
	static	bool Compress(  CBasicStream* pstInput, CBasicStream* pstOutput, int nCompLv=-1, unsigned int* lpSize=NULL);	///< zlib�ň��k

	static	bool MemDecompress(const smart_buffer& bufSrc, smart_buffer& bufDst);						/// �������W�J
	static	bool MemCompress(  const smart_buffer& bufSrc, smart_buffer& bufDst, int nCompLv=-1);		/// ���������k
};

} // end of namespace sueLib

#endif
