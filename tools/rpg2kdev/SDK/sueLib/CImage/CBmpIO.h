/**
	@file
	@brief		BMP�t�@�C���̓��o�͂��s���N���X
	@author		sue445
*/
#ifndef _INC_CBMPIO
#define _INC_CBMPIO

#include "CImageIO.h"


namespace sueLib {

/// BMP�t�@�C���̓��o�͂��s���N���X
class CBmpIO : virtual CImageIO {
private:

#pragma pack(push)
#pragma pack(1) //�\���̂̃����o���E��1�o�C�g�ɂ���
	/// �r�b�g�}�b�v�t�@�C���w�b�_
	typedef struct tagBITMAP_FILE_HEADER {
		unsigned short	bfType;			///< "BM"
		unsigned long	bfSize;			///< �t�@�C���T�C�Y
		unsigned short	bfReserved1;	///< �\�� Zero
		unsigned short	bfReserved2;	///< �\�� Zero
		unsigned long	bfOffBits;		///< �擪����C���[�W�f�[�^�܂ł̃I�t�Z�b�g
	} BITMAPFILEHEADER;

	// ========= WIN BMP/DIB FORMAT
	/// WIN�C���[�W�f�[�^���
	typedef struct tagBITMAP_INFO_HEADER {
		unsigned long	biSize;				///< ���̍\���̂̃T�C�Y
		long			biWidth;			///< �摜�̉���
		long			biHeight;			///< �摜�̍���
		unsigned short	biPlanes;			///< �\�� 1
		unsigned short	biBitCount;			///< �F��
		unsigned long	biCompression;		///< ���k�̎��
		unsigned long	biSizeImage;		///< �C���[�W�̃o�C�g��
		long			biXPelsPerMeter;	///< �����𑜓x
		long			biYPelsPerMeter;	///< �����𑜓x
		unsigned long	biClrUsed;			///< �g�p����J���[�C���f�b�N�X�̐�
		unsigned long	biClrImportant;		///< ���F���Ȃ��J���[�C���f�b�N�X��
	} BITMAPINFOHEADER;

	/*
	/// WIN�J���[�e�[�u���v�f
	typedef struct tagRGBQUAD {
		unsigned char		rgbBlue;		///< ��
		unsigned char		rgbGreen;		///< ��
		unsigned char		rgbRed;			///< ��
		unsigned char		rgbReserved;	///< �\��
	} RGBQUAD;
	*/

	/// WIN�w�b�_���
	typedef struct tagBITMAP_INFO {
		BITMAPINFOHEADER	bmiHeader;		///< �r�b�g�}�b�v�w�b�_
		RGBQUAD	bmiColors[1];				///< �J���[�e�[�u���̈�Ԗ�
	} BITMAPINFO;

	// ========= OS/2 BMP/DIB FORMAT
	/// OS/2 �C���[�W�f�[�^���
	typedef struct tagBITMAP_CORE_HEADER {
		unsigned long	biSize;			///< ���̍\���̂̃T�C�Y
		unsigned short	biWidth;		///< �摜�̉���
		unsigned short	biHeight;		///< �摜�̍���
		unsigned short	biPlanes;		///< �\�� 1
		unsigned short	biBitCount;		///< �F��
	} BITMAPCOREHEADER;

	/*
	/// OS/2 �J���[�e�[�u���v�f
	typedef struct tagRGBTRIPLE {
		unsigned char		rgbBlue;	///< ��
		unsigned char		rgbGreen;	///< ��
		unsigned char		rgbRed;		///< ��
	} RGBTRIPLE;
	*/

	/// OS/2 �w�b�_���
	typedef struct tagBITMAP_CORE_INFO {
		BITMAPCOREHEADER	bmiHeader;		///< �r�b�g�}�b�v�w�b�_
		RGBTRIPLE			bmiColors[1];	///< �J���[�e�[�u���̈�Ԗ�
	} BITMAPCOREINFO;
#pragma pack(pop)

public:
	//=============================================================================
	/**
		�摜�̐F�����擾

		@param	szFile			[in] �t�@�C����

		@retval	��0				�摜�̐F��
		@retval	0				��Ή�
	*/
	//=============================================================================
	static int GetBitCount(const char* szFile)
	{
		CBasicStream file;
		BITMAPFILEHEADER header;
		BITMAPINFOHEADER info;
		BITMAPCOREHEADER core;


		if(!file.OpenFromFile(szFile))		return 0;	// �t�@�C�����J���Ȃ�

		file.Read(&header, sizeof(header));
		if(header.bfType!=0x4D42)			return 0;	// �w�b�_����v���Ȃ�

		file.Read(&info, sizeof(info));
		// WIN
		if(info.biSize==sizeof(BITMAPINFOHEADER)){
			return info.biBitCount;
		}
		// OS/2
		else if(info.biSize==sizeof(BITMAPCOREHEADER)){
			// WIN�ł͂Ȃ������̂œǂݍ��݂��Ȃ���
			file.SetSeek(sizeof(BITMAPFILEHEADER), SEEK_SET);
			file.Read(&core, sizeof(core));

			return core.biBitCount;
		}

		return 0;
	}

	//=============================================================================
	/**
		�摜��ǂݍ���

		@param	szFile			[in] �t�@�C����
		@param	img				[out] �o�͐��CBasicImage

		@retval	true			�摜�̓ǂݍ��݂ɐ���
		@retval	false			�摜�̓ǂݍ��݂Ɏ��s
	*/
	//=============================================================================
	template< typename PIXEL >
	static bool Load(const char* szFile, CBasicImage< PIXEL >& img)
	{
		CBasicStream file;
		BITMAPFILEHEADER header;
		BITMAPINFOHEADER info;
		BITMAPCOREHEADER core;
		unsigned int i;


		if(!file.OpenFromFile(szFile))		return false;	// �t�@�C�����J���Ȃ�

		file.Read(&header, sizeof(header));
		if(header.bfType!=0x4D42)			return false;	// �w�b�_����v���Ȃ�

		file.Read(&info, sizeof(info));
		// WIN
		if(info.biSize==sizeof(BITMAPINFOHEADER)){
			if(info.biBitCount!=img.GetBitCount())			return false;	// �F�����Ⴄ
			if(info.biWidth>65535 || info.biHeight>65535)	return false;	// �摜���傫������(�Ȃ��Ǝv������)

			img.Create((unsigned short)info.biWidth, (unsigned short)info.biHeight);

			// �p���b�g��ǂݍ���
			RGBQUAD rgb;
			for(i = 0; i < img.GetPalSize(); i++){
				file.Read(&rgb, sizeof(rgb));
				img.SetPalette(i, rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
			}
		}
		// OS/2
		else if(info.biSize==sizeof(BITMAPCOREHEADER)){
			// WIN�ł͂Ȃ������̂œǂݍ��݂��Ȃ���
			file.SetSeek(sizeof(BITMAPFILEHEADER), SEEK_SET);
			file.Read(&core, sizeof(core));

			if(core.biBitCount!=img.GetBitCount())			return false;	// �F�����Ⴄ

			img.Create(core.biWidth, core.biHeight);

			// �p���b�g��ǂݍ���
			RGBTRIPLE rgb;
			for(i = 0; i < img.GetPalSize(); i++){
				file.Read(&rgb, sizeof(rgb));
				img.SetPalette(i, rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
			}
		}
		else{
			return false;
		}

		// �O�̂��߂Ɏ����œǂݍ��݈ʒu���Z�b�g����
		file.SetSeek(header.bfOffBits, SEEK_SET);

		// BMP�t�@�C���͍����̃s�N�Z������n�܂��Ă���̂ŁA�t����i�[����
		PIXEL* p = img.Locate(0, img.GetHeight()-1);
		const unsigned int linesize = sizeof(PIXEL) * img.GetWidth();	// 1�s���̃f�[�^��
		const unsigned int lineskip = (4 - linesize % 4) % 4;
		for(i = 0; i < img.GetHeight(); i++){
			file.Read(p, linesize);
			p = img.PrevLine();

			// 4�o�C�g���E
			if(lineskip>0)	file.SetSeek(lineskip, SEEK_CUR);
		}

		return true;
	}	///< �摜��ǂݍ���


	//=============================================================================
	/**
		�摜�������o��

		@param	szFile			[in] �t�@�C����
		@param	img				[in] ���͌���CBasicImage

		@retval	true			�摜�̏����o���ɐ���
		@retval	false			�摜�̏����o���Ɏ��s
	*/
	//=============================================================================
	template< typename PIXEL >
	static bool Save(const char* szFile, const CBasicImage< PIXEL >& img)
	{
		CBasicStream file;
		BITMAPFILEHEADER header;
		BITMAPINFOHEADER info;
		unsigned int i;


		if(!img.IsInit())						return false;	// ����������ĂȂ�

		if(!file.OpenFromFile(szFile, true))	return false;	// �t�@�C�����J���Ȃ�

		// BITMAPINFOHEADER
		info.biSize				= sizeof(BITMAPINFOHEADER);
		info.biWidth			= img.GetWidth();
		info.biHeight			= img.GetHeight();
		info.biPlanes			= 1;
		info.biBitCount			= img.GetBitCount();
		info.biCompression		= 0;
		info.biSizeImage		= 0;
		info.biXPelsPerMeter	= 0;
		info.biYPelsPerMeter	= 0;
		info.biClrUsed			= img.GetPalSize();
		info.biClrImportant		= 0;

		// BITMAPFILEHEADER
		header.bfType			= 0x4D42;
		header.bfSize			= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ((img.GetWidth() * sizeof(PIXEL) +3) & ~3)*img.GetHeight() + sizeof(RGBQUAD)*img.GetPalSize();
		header.bfReserved1		= 0;
		header.bfReserved2		= 0;
		header.bfOffBits		= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*img.GetPalSize();


		file.Write(&header, sizeof(header));
		file.Write(&info  , sizeof(info));

		RGBQUAD rgb = {0};
		for(i = 0; i < img.GetPalSize(); i++){
			img.GetPalette(i, &rgb.rgbRed, &rgb.rgbGreen, &rgb.rgbBlue);
			file.Write(&rgb, sizeof(rgb));
		}

		// BMP�t�@�C���͍����̃s�N�Z������n�܂��Ă���̂ŁA�t����i�[����
		const PIXEL* p = img.GetPtr(0, img.GetHeight()-1);
		const unsigned int linesize = sizeof(PIXEL) * img.GetWidth();	// 1�s���̃f�[�^��
		const unsigned int lineskip = (4 - linesize % 4) % 4;
		const unsigned char tmp[3] = {0, 0, 0};
		for(i = 0; i < img.GetHeight(); i++){
			file.Write(p, linesize);
			p -= img.GetWidth();

			// 4�o�C�g���E
			if(lineskip>0)	file.Write(tmp, lineskip);
		}

		return true;
	}	///< �摜�������o��
};

} // end of namespace sueLib

#endif
