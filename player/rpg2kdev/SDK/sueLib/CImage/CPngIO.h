/**
	@file
	@brief		PNG�t�@�C���̓��o�͂��s���N���X
	@note		<�Q�lURL> http://www.kcrt.net/program/index.html
	@author		sue445
*/
#ifndef _INC_CPNGIO
#define _INC_CPNGIO

#include "CImageIO.h"
#include <png.h>

// fopen�n�œǂݍ��ނ��ǂ���
//#define LIBPNG_STDIO

/*
zlib version 1.2.3�FCopyright (C) 1995-2005 Jean-loup Gailly and Mark Adler
<URL> http://www.gzip.org/zlib/

libpng version 1.2.12�FCopyright (c) 1998-2006 Glenn Randers-Pehrson
<URL> http://www.libpng.org/pub/png/
*/

// �����[�X�R���p�C����
#ifndef _DEBUG
	#pragma comment( lib, "libpng.lib" )
	#pragma comment( lib, "zlib.lib" )
// �f�o�b�O�R���p�C����
#else
	#pragma comment( lib, "libpngd.lib" )
	#pragma comment( lib, "zlibd.lib" )
#endif

namespace sueLib {

/// png_struct��png_info�������I�ɉ������N���X
class ktPngStructReleaser{
public:
	ktPngStructReleaser(png_structp p, png_infop q, bool write){
		m_p = p;
		m_q = q;
		m_bWrite = write;
	}
	~ktPngStructReleaser(){
		if(!m_bWrite)	png_destroy_read_struct( &m_p, &m_q, NULL);
		else			png_destroy_write_struct(&m_p, &m_q);
	}

private:
	png_structp	m_p;
	png_infop	m_q;
	bool m_bWrite;
};

/// PNG�t�@�C���̓��o�͂��s���N���X
class CPngIO : virtual CImageIO {
private:

#ifndef LIBPNG_STDIO
	//=============================================================================
	/**
		PNG�ǂݍ��ݎ��ɌĂяo�����R�[���o�b�N�֐�

		@param	png_ptr		[in] png_struct�ւ̃|�C���^
		@param	buf			[out] �ǂݍ��ݐ�o�b�t�@
		@param	size		[in] �ǂݍ��ރT�C�Y
	*/
	//=============================================================================
	static void PngReadFunc(png_struct *png_ptr, png_bytep buf, png_size_t size)
	{
		CBasicStream* pFile = (CBasicStream*)png_get_io_ptr(png_ptr);
		pFile->Read(buf, size);
	}

	//=============================================================================
	/**
		PNG�����o�����ɌĂяo�����R�[���o�b�N�֐�

		@param	png_ptr		[in] png_struct�ւ̃|�C���^
		@param	buf			[in] �����o�����o�b�t�@
		@param	size		[in] �����o���T�C�Y
	*/
	//=============================================================================
	static void PngWriteFunc(png_struct *png_ptr, png_bytep buf, png_size_t size)
	{
		CBasicStream* pFile = (CBasicStream*)png_get_io_ptr(png_ptr);
		pFile->Write(buf, size);
	}
#endif

public:
	//=============================================================================
	/**
		�摜�̐F�����擾

		@param	szFile			[in] �t�@�C����
		@param	bAlpha			[in] ���`�����l����W�J���邩�ǂ���

		@retval	��0				�摜�̐F��
		@retval	0				��Ή�
	*/
	//=============================================================================
	static int GetBitCount(const char* szFile, bool bAlpha=false)
	{
		char buf[8];
		png_structp	png_ptr;
		png_infop	info_ptr;

#ifdef LIBPNG_STDIO
		FILE* fp = fopen(szFile, "rb");
		if(!fp)									return false;
#else
		CBasicStream file;
		if(!file.OpenFromFile(szFile))			return false;	// �t�@�C�����J���Ȃ�
		file.Read(buf, sizeof(buf));
#endif

		if(!png_check_sig((png_bytep)buf, sizeof(buf)))	return 0;	// PNG�ł͂Ȃ�

		if(!(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL))){
			return 0;
		}
#ifdef LIBPNG_STDIO
		png_init_io(png_ptr, fp);
#endif

		if(!(info_ptr = png_create_info_struct(png_ptr))){
			png_destroy_read_struct( &png_ptr, NULL, NULL);
			return 0;
		}

		ktPngStructReleaser pngreleaser(png_ptr, info_ptr, false);

#ifdef LIBPNG_STDIO
		fseek(fp, 0, SEEK_SET);
#else
		// �t�@�C���`�F�b�N�p�Ɉ�x�ǂݍ���ł���̂ŁA�ǂݍ��݃|�C���^�����ɖ߂�
		file.SetSeek(0, SEEK_SET);

		// �ǂݍ��ݗp�̃R�[���o�b�N�֐���libpng�ɋ�����
		png_set_read_fn(png_ptr,(png_voidp)&file,(png_rw_ptr)PngReadFunc);
#endif
		png_read_info(png_ptr, info_ptr);

		// �A���t�@�`�����l������
		if(!bAlpha)		png_set_strip_alpha(png_ptr);
		png_read_update_info(png_ptr, info_ptr);

		png_uint_32 PngWidth;
		png_uint_32 PngHeight;
		int bpp;
		int ColorType;
		png_get_IHDR(png_ptr, info_ptr, &PngWidth, &PngHeight, &bpp, &ColorType, NULL, NULL, NULL);

		int bitcount = png_get_channels(png_ptr, info_ptr) * bpp;
		// ���`�����l�����܂܂�Ă����32bits����
		if(bAlpha && png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))		bitcount = 32;

#ifdef LIBPNG_STDIO
	fclose(fp);
#endif
		return bitcount;
	}

	//=============================================================================
	/**
		�摜��ǂݍ���

		@param	szFile			[in] �t�@�C����
		@param	img				[out] �o�͐��CBasicImage
		@param	bAlpha			[in] ���`�����l����W�J���邩�ǂ���

		@retval	true			�摜�̓ǂݍ��݂ɐ���
		@retval	false			�摜�̓ǂݍ��݂Ɏ��s
	*/
	//=============================================================================
	template< typename PIXEL >
	static bool Load(const char* szFile, CBasicImage< PIXEL >& img, bool bAlpha=false)
	{
		char buf[8];
		png_structp	png_ptr;
		png_infop	info_ptr;
		unsigned int i;

#ifdef LIBPNG_STDIO
		FILE* fp = fopen(szFile, "rb");
		if(!fp)									return false;
		fread(buf, sizeof(buf), 1, fp);
#else
		CBasicStream file;
		if(!file.OpenFromFile(szFile))			return false;	// �t�@�C�����J���Ȃ�
		file.Read(buf, sizeof(buf));
#endif

		if(!png_check_sig((png_bytep)buf, sizeof(buf)))	return false;	// PNG�ł͂Ȃ�

		if(!(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)))
			return false;

#ifdef LIBPNG_STDIO
		png_init_io(png_ptr, fp);
#endif

		if(!(info_ptr = png_create_info_struct(png_ptr))){
			png_destroy_read_struct( &png_ptr, NULL, NULL);
#ifdef LIBPNG_STDIO
			fclose(fp);
#endif
			return false;
		}

		ktPngStructReleaser pngreleaser(png_ptr, info_ptr, false);

#ifdef LIBPNG_STDIO
		fseek(fp, 0, SEEK_SET);
#else
		// �t�@�C���`�F�b�N�p�Ɉ�x�ǂݍ���ł���̂ŁA�ǂݍ��݃|�C���^�����ɖ߂�
		file.SetSeek(0, SEEK_SET);

		// �ǂݍ��ݗp�̃R�[���o�b�N�֐���libpng�ɋ�����
		png_set_read_fn(png_ptr,(png_voidp)&file,(png_rw_ptr)PngReadFunc);
#endif


		png_read_info(png_ptr, info_ptr);

		png_uint_32 PngWidth;
		png_uint_32 PngHeight;
		int bpp;
		int ColorType;
		png_get_IHDR(png_ptr, info_ptr, &PngWidth, &PngHeight, &bpp, &ColorType, NULL, NULL, NULL);

		int bitcount = png_get_channels(png_ptr, info_ptr) * bpp;
		// ���`�����l�����܂܂�Ă����32bits����
		if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)){
			int row = png_get_rowbytes(png_ptr, info_ptr);
			if(bAlpha/* && PngWidth*4==row*/){
				bitcount = 32;
			}
		}

		if(bitcount != img.GetBitCount()){		// �F�����Ⴄ
#ifdef LIBPNG_STDIO
			fclose(fp);
#endif
			return false;
		}
		if(PngWidth>65535 || PngHeight>65535){	// �摜���傫������(�Ȃ��Ǝv������)
#ifdef LIBPNG_STDIO
			fclose(fp);
#endif
			return false;
		}

		// �J���[�z����q�f�a����a�f�q�ɔ��]
		png_set_bgr(png_ptr);

		if(bAlpha && bitcount==32){
			// �A���t�@�`�����l���Ɋ֌W���鏈���̐ݒ�
			if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))		png_set_expand(png_ptr);

			// �P�U�r�b�g�̉摜�ł��W�r�b�g�Ŏ��[����悤�ɐݒ�
			if(bpp > 8)												png_set_strip_16(png_ptr);
			if(ColorType == PNG_COLOR_TYPE_GRAY)					png_set_gray_to_rgb(png_ptr);

			if(sizeof(PIXEL)==4 && !(ColorType & PNG_COLOR_MASK_ALPHA))		png_set_filler(png_ptr, 0, 1);

			// �p���b�g�g�p�摜�f�[�^�̎����W�J�w��
			if(ColorType == PNG_COLOR_TYPE_PALETTE)					png_set_expand(png_ptr);

			// �W�r�b�g�ȉ��̃O���[�X�P�[���摜���W�r�b�g���܂œW�J������悤�w��
			if(ColorType == PNG_COLOR_TYPE_GRAY && bpp <= 8)		png_set_expand(png_ptr);
		}
		else{
			if(ColorType & PNG_COLOR_MASK_ALPHA)		png_set_strip_alpha(png_ptr);
		}


		// �ύX�����ݒ�𔽉f������
		png_read_update_info(png_ptr, info_ptr);

		img.Create((unsigned short)PngWidth, (unsigned short)PngHeight);

		// �p���b�g���̓ǂݍ���
		for(i = 0; i < img.GetPalSize(); i++){
			img.SetPalette(i, info_ptr->palette[i].red, info_ptr->palette[i].green, info_ptr->palette[i].blue);
		}

		png_bytep *lines = new png_bytep[img.GetHeight()];
		PIXEL* p = img.Top();
		for(i = 0; i < img.GetHeight(); i++){
			lines[i] = (png_bytep)p;
			p = img.NextLine();
		}
		// �摜�f�[�^�̓ǂݍ���
		png_read_image(png_ptr, lines);

		// �ǂݍ��ݏ����̏I��
		png_read_end(png_ptr, info_ptr);
		delete[] lines;

#ifdef LIBPNG_STDIO
	fclose(fp);
#endif
		return true;
	}	///< �摜��ǂݍ���


	//=============================================================================
	/**
		�摜�������o��

		@param	szFile			[in] �t�@�C����
		@param	img				[in] ���͌���CBasicImage
		@param	nCompLv			[in] �ۑ����̈��k���x��(0(�����k)�`9(�ō����k), -1�ŕW�����k)
		@param	nFilter			[in] �ۑ����̃t�B���^

		@retval	true			�摜�̏����o���ɐ���
		@retval	false			�摜�̏����o���Ɏ��s
	*/
	//=============================================================================
	template< typename PIXEL >
	static bool Save(const char* szFile, const CBasicImage< PIXEL >& img, int nCompLv=-1, int nFilter=PNG_ALL_FILTERS)
	{
		unsigned int i;
		png_structp	png_ptr;
		png_infop	info_ptr;

		if(!img.IsInit())						return false;	// ����������ĂȂ�

#ifdef LIBPNG_STDIO
		FILE* fp = fopen(szFile, "wb");
		if(!fp)									return false;
#else
		CBasicStream file;
		if(!file.OpenFromFile(szFile, true))	return false;	// �t�@�C�����J���Ȃ�
#endif

		if(!(png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL))) return false;
		if(!(info_ptr = png_create_info_struct(png_ptr))){
			png_destroy_write_struct(&png_ptr, png_infopp_NULL);
			return false;
		}
		ktPngStructReleaser pngreleaser(png_ptr, info_ptr, true);

		if(setjmp(png_jmpbuf(png_ptr))){
			// �G���[�̎������ɗ���B
			return false;
		}

#ifdef LIBPNG_STDIO
		png_init_io(png_ptr, fp);                              // libpng��fp��m�点�܂�
#else
		// �����o���p�̃R�[���o�b�N�֐���libpng�ɋ�����(flush�֐��ɂ��Ă͂悭������Ȃ��̂Ŏw�肵�Ȃ�)
		png_set_write_fn(png_ptr,(png_voidp)&file,(png_rw_ptr)PngWriteFunc, NULL);
#endif

		// �ۑ����̃t�B���^�ƈ��k���x����ݒ�
		png_set_filter(png_ptr, 0, nFilter);
		png_set_compression_level(png_ptr, nCompLv);

		// �p���b�g���̏�������
		if(img.GetPalSize()>0){
			png_color* plt = new png_color[img.GetPalSize()];
			if(!plt)				return false;	// �������̊m�ۂɎ��s

			for(i = 0; i < img.GetPalSize(); i++){
				img.GetPalette(i, &plt[i].red, &plt[i].green, &plt[i].blue);
			}
			png_set_PLTE(png_ptr, info_ptr, plt, img.GetPalSize());

			delete[] plt;
		}

		int nColorType;
		if(img.GetPalSize()>0)		nColorType = PNG_COLOR_TYPE_PALETTE;
		else if(sizeof(PIXEL)==4)	nColorType = PNG_COLOR_TYPE_RGB_ALPHA;
		else						nColorType = PNG_COLOR_TYPE_RGB;
		// IHDR�`�����N����ݒ肵�܂�
		png_set_IHDR(png_ptr, info_ptr, img.GetWidth(), img.GetHeight(), 8,
						nColorType, PNG_INTERLACE_NONE,
						PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		/*
		// PNG�ɏ������܂��R�����g
		png_text text_ptr[1];
		text_ptr[0].key = "Description";
		text_ptr[0].text = "ktcDIB::Save() Data";
		text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
		png_set_text(png_ptr, info_ptr, text_ptr, 1);
		*/

		png_write_info(png_ptr, info_ptr);	// PNG�t�@�C���̃w�b�_���������݂܂�

		png_bytep *lines = new png_bytep[img.GetHeight()];
		const PIXEL* p = img.GetPtr(0, 0);
		for(i = 0; i < img.GetHeight(); i++) {
			lines[i] = (png_bytep)p;
			p += img.GetWidth();
		}
		png_set_bgr(png_ptr);
		png_write_image(png_ptr, lines);		// �摜�f�[�^���������݂܂�

		png_write_end(png_ptr, info_ptr);		// �c��̏����������݂܂�

		delete[] lines;

#ifdef LIBPNG_STDIO
		fclose(fp);
#endif
		return true;
	}	///< �摜�������o��
};

} // end of namespace sueLib


#endif
