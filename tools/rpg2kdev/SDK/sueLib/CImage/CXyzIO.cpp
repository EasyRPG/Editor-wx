/**
	@file
	@brief		XYZ�t�@�C���̓��o�͂��s���N���X
	@author		sue445
*/
#include "CXyzIO.h"
#include "../smart_buffer.h"
#include "CBmpImage.h"

namespace sueLib {

//=============================================================================
/**
	�摜��ǂݍ���

	@param	szFile			[in] �t�@�C����
	@param	img				[out] �o�͐��CImage8(XYZ��8�r�b�g�I�����[�̂���)

	@retval	true			�摜�̓ǂݍ��݂ɐ���
	@retval	false			�摜�̓ǂݍ��݂Ɏ��s
*/
//=============================================================================
bool CXyzIO::Load(const char* szFile, CImage8& img)
{
	CBasicStream file;
	XYZ_FILEHEADER header;
	unsigned int i;


	if(!file.OpenFromFile(szFile))			return false;	// �t�@�C�����J���Ȃ�

	file.Read(&header, sizeof(header));
	if(memcmp(header.cID, "XYZ1", 4)!=0)	return false;	// �w�b�_����v���Ȃ�

	img.Create(header.shWidth, header.shHeight);

	// zlib�W�J�p�̃o�b�t�@���m��
	smart_buffer buf(header.shWidth*header.shHeight + sizeof(XYZ_RGB)*256);

	CBasicStream dec;	// zlib�ɓn���o�͗p�̃X�g���[��
	dec.OpenFromMemory(buf.GetPtr(), buf.GetSize(), true);

	if(!Decompress(&file, &dec)){
		return false;
	}

	// �p���b�g��
	const XYZ_RGB* plt = (XYZ_RGB*)buf.GetPtr();
	for(i = 0; i < 256; i++){
		img.SetPalette(i, plt[i].red, plt[i].green, plt[i].blue);
	}

	// �摜�f�[�^��
	const unsigned char* pData = (const unsigned char*)(buf.GetPtr()+sizeof(XYZ_RGB)*256);
	memcpy(img.Top(), pData, header.shWidth*header.shHeight);


	return true;
}


//=============================================================================
/**
	�摜�������o��

	@param	szFile			[in] �t�@�C����
	@param	img				[in] ���͌���CImage8(XYZ��8�r�b�g�I�����[�̂���)
	@param	nCompLv			[in] �ۑ����̈��k���x��(0(�����k)�`9(�ō����k), -1�ŕW�����k)

	@retval	true			�摜�̏����o���ɐ���
	@retval	false			�摜�̏����o���Ɏ��s
*/
//=============================================================================
bool CXyzIO::Save(const char* szFile, const CImage8& img, int nCompLv)
{
	CBasicStream file;
	XYZ_FILEHEADER	header;
	unsigned int i;


	if(!img.IsInit())						return false;	// ����������ĂȂ�

	if(!file.OpenFromFile(szFile, true))	return false;	// �t�@�C�����J���Ȃ�

	// �w�b�_�̏���
	memcpy(header.cID, "XYZ1", 4);
	header.shWidth  = img.GetWidth();
	header.shHeight = img.GetHeight();

	file.Write(&header, sizeof(header));

	// zlib���k�p�̃o�b�t�@���m��
	smart_buffer buf(header.shWidth*header.shHeight + sizeof(XYZ_RGB)*256);

	// �p���b�g��
	XYZ_RGB* plt = (XYZ_RGB*)buf.GetPtr();
	for(i = 0; i < 256; i++){
		img.GetPalette(i, &plt[i].red, &plt[i].green, &plt[i].blue);
	}

	// �摜�f�[�^��
	unsigned char* pData = (unsigned char*)(buf.GetPtr()+sizeof(XYZ_RGB)*256);
	memcpy(pData, img.GetPtr(0, 0), header.shWidth*header.shHeight);

	CBasicStream dec;	// zlib�ɓn�����͗p�̃X�g���[��
	dec.OpenFromMemory(buf.GetPtr(), buf.GetSize());

	if(!Compress(&dec, &file, nCompLv)){
		return false;
	}

	return true;
}


} // end of namespace sueLib

