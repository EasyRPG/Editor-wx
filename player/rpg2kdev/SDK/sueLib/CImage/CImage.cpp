/**
	@file
	@brief		�摜�̃s�N�Z���f�[�^���Ǘ�����N���X
	@author		sue445
*/
#include "CImage.h"

namespace sueLib {

/// Alpha�����o��
unsigned char Alpha(unsigned long rgba)
{
	return (unsigned char)((rgba & 0xFF000000)>>24);
}
/// Red�����o��
unsigned char Red(unsigned long rgba)
{
	return (unsigned char)((rgba & 0x00FF0000)>>16);
}
/// Green�����o��
unsigned char Green(unsigned long rgba)
{
	return (unsigned char)((rgba & 0x0000FF00)>>8);
}
/// Blue�����o��
unsigned char Blue(unsigned long rgba)
{
	return (unsigned char)(rgba & 0x000000FF);
}
/// ������
unsigned char CalcAlpha(unsigned char src, unsigned char dst, unsigned char alpha)
{
	// �Q�l�����FWindows�v���t�F�b�V���i���Q�[���v���O���~���O2(��˂��炨��) P303
	return ((dst<<8)-dst + (src-dst)*alpha + 255)>>8;
}
/// ������(�s�����x���l��)
unsigned char CalcAlpha2(unsigned char src, unsigned char dst, unsigned char alpha, unsigned char opacity)
{
	return CalcAlpha(CalcAlpha(src,dst,alpha), dst, opacity);
}

} // end of namespace sueLib
