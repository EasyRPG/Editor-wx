/**
	@file
	@brief		XYZ�t�@�C���̓��o�͂��s���N���X
	@author		sue445
*/
#ifndef _INC_CXYZIO
#define _INC_CXYZIO

#include "CImageIO.h"
#include "../CZLib.h"


namespace sueLib {

/// XYZ�t�@�C���̓��o�͂��s���N���X
class CXyzIO : virtual CImageIO, private CZLib {
private:
	/// XYZ�̃t�@�C���w�b�_
	struct XYZ_FILEHEADER{
		unsigned char  cID[4];		// ���ʗpID(XYZ1)
		unsigned short shWidth;		// �摜�̕�
		unsigned short shHeight;	// �摜�̍���
	};
	/// XYZ�̃p���b�g���
	struct XYZ_RGB{
		unsigned char red;
		unsigned char green;
		unsigned char blue;
	};

public:
	static bool Load(const char* szFile, CImage8& img);					///< �摜��ǂݍ���
	static bool Save(const char* szFile, const CImage8& img, int nCompLv=-1);	///< �摜�������o��
	static int  GetBitCount(const char* szFile)							///< �摜�̐F�����擾
	{
		CImage8 img;
		return (Load(szFile,img)) ? 8 : 0;
	}
};

} // end of namespace sueLib


#endif
