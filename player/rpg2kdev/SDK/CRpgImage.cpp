/**
	@file
	@brief		bmp,png,xyz�������I�ɔ��ʂ��ēǂݍ��񂾂肷��N���X
	@note		�t�@�C�����Ɋg���q���s�v�Ȃ͖̂���������܂��񂪁A�c�N�[�������Ŋi�[����Ă���
				�s�N�`���Ȃǂ̃t�@�C�����͑S�Ċg���q���܂܂�Ă��Ȃ��̂ł��̎d�l�ɍ��킹�Ă��܂��B
	@author		sue445
*/
#include "CRpgImage.h"
#include <string>
#include "sueLib/CImage/CBmpIO.h"
#include "sueLib/CImage/CPngIO.h"
#include "sueLib/CImage/CXyzIO.h"


using std::string;
using namespace sueLib;

//=============================================================================
/**
	�摜��ǂݍ���

	@param	szFile			[in] �t�@�C����(�g���q�͕s�v)

	@retval	true			�摜�̓ǂݍ��݂ɐ���
	@retval	false			�摜�̓ǂݍ��݂Ɏ��s
*/
//=============================================================================
bool CRpgImage::Load(const char* szFile)
{
	string str;


	// bmp
	str = szFile;
	str += ".bmp";
	if(CBmpIO::Load(str.c_str(), *this))		return true;

	// png
	str = szFile;
	str += ".png";
	if(CPngIO::Load(str.c_str(), *this, false))	return true;

	// xyz
	str = szFile;
	str += ".xyz";
	if(CXyzIO::Load(str.c_str(), *this))		return true;

	return false;
}

//=============================================================================
/**
	�摜��ۑ�����

	@param	eSaveType		[in] �ۑ��`��
	@param	szFile			[in] �t�@�C����(�g���q�͕s�v)

	@retval	true			�摜�̕ۑ��ɐ���
	@retval	false			�摜�̕ۑ��Ɏ��s
*/
//=============================================================================
bool CRpgImage::Save(const char* szFile, eRpgImage eSaveType) const
{
	string str = szFile;


	switch(eSaveType){
	// bmp
	case IMG_BMP:
		str += ".bmp";
		return CBmpIO::Save(str.c_str(), *this);
	// png
	case IMG_PNG:
		str += ".png";
		return CPngIO::Save(str.c_str(), *this);
	// xyz
	case IMG_XYZ:
		str += ".xyz";
		return CXyzIO::Save(str.c_str(), *this);
	}

	return false;
}
