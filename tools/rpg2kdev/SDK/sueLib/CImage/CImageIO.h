/**
	@file
	@brief		�摜�t�@�C�����o�͂̊�{�ƂȂ�N���X
	@author		sue445
*/
#ifndef _INC_CIMAGEIO
#define _INC_CIMAGEIO

#include "../sueLib_Compile.h"
#include "CImage.h"
#include "../CBasicStream.h"


namespace sueLib {

/// �摜�t�@�C�����o�͂̊�{�ƂȂ�N���X
class CImageIO{
public:
	template< typename PIXEL >
	static bool Load(const char* szFile, CBasicImage< PIXEL >& img){ return false; }	///< �摜��ǂݍ���

	template< typename PIXEL >
	static bool Save(const char* szFile, const CBasicImage< PIXEL >& img){ return false; }	///< �摜�������o��

	static int GetBitCount(const char* szFile){ return 0; }								///< �摜�̐F�����擾
};

} // end of namespace sueLib

#endif
