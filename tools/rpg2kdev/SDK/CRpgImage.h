/**
	@file
	@brief		bmp,png,xyz�������I�ɔ��ʂ��ēǂݍ��񂾂肷��N���X
	@note		�t�@�C�����Ɋg���q���s�v�Ȃ͖̂���������܂��񂪁A�c�N�[�������Ŋi�[����Ă���
				�s�N�`���Ȃǂ̃t�@�C�����͑S�Ċg���q���܂܂�Ă��Ȃ��̂ł��̎d�l�ɍ��킹�Ă��܂��B
	@author		sue445
*/
#ifndef _INC_CRPGIMAGE
#define _INC_CRPGIMAGE

#include "sueLib/CImage/CImage.h"

using namespace sueLib;

/// �c�N�[���ň�����摜�`��
enum eRpgImage{
	IMG_BMP,	///< BMP
	IMG_PNG,	///< PNG
	IMG_XYZ,	///< XYZ
};

/// bmp,png,xyz�������I�ɔ��ʂ��ēǂݍ��񂾂肷��N���X
class CRpgImage : public CImage8{
public:
	bool Load(const char* szFile);								///< �ǂݍ���
	bool Save(const char* szFile, eRpgImage eSaveType) const;	///< �ۑ�����
};

#endif