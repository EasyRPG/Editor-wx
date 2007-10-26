/**
	@file
	@brief		�摜�̃s�N�Z���f�[�^���Ǘ�����N���X
	@author		sue445
*/
#ifndef _INC_CIMAGE
#define _INC_CIMAGE

#include "../sueLib_Compile.h"
#include <stdio.h>
#include <memory.h>
#include "../smart_array.h"

#ifndef RGBA_MAKE
	#define RGBA_MAKE(r, g, b, a)	((unsigned long) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))) 
#endif


namespace sueLib {

unsigned char Alpha(unsigned long rgba);	///< Alpha�����o��
unsigned char Red(  unsigned long rgba);	///< Red�����o��
unsigned char Green(unsigned long rgba);	///< Green�����o��
unsigned char Blue( unsigned long rgba);	///< Blue�����o��
unsigned char CalcAlpha(unsigned char src, unsigned char dst, unsigned char alpha);	///< ������
unsigned char CalcAlpha2(unsigned char src, unsigned char dst, unsigned char alpha, unsigned char opacity);	///< ��+�s�����x����

#pragma pack(push)
#pragma pack(1) //�\���̂̃����o���E��1�o�C�g�ɂ���

/// WIN�J���[�e�[�u���v�f
typedef struct tagRGBQUAD {
	unsigned char	rgbBlue;		///< ��
	unsigned char	rgbGreen;		///< ��
	unsigned char	rgbRed;			///< ��
	unsigned char	rgbReserved;	///< �\��
} RGBQUAD;

/// OS/2 �J���[�e�[�u���v�f(CImage24�p�Ɏ኱�g��)
struct RGBTRIPLE {
	unsigned char		rgbBlue;	///< ��
	unsigned char		rgbGreen;	///< ��
	unsigned char		rgbRed;		///< ��

	/// �f�t�H���g�R���X�g���N�^
	RGBTRIPLE() : rgbBlue(0), rgbGreen(0), rgbRed(0) {}

	/// �R�s�[�R���X�g���N�^
	RGBTRIPLE(unsigned long color){ operator=(color); }

	/// ������Z�q
	RGBTRIPLE& operator=(unsigned long color)
	{
		rgbRed		= (unsigned char)((color & 0x00FF0000) >> 16);
		rgbGreen	= (unsigned char)((color & 0x0000FF00) >> 8);
		rgbBlue		= (unsigned char)( color & 0x000000FF);
		return *this;
	}

	/// RGB�����������J���[�R�[�h��Ԃ�
	operator unsigned long() const { return (rgbRed<<16) | (rgbGreen<<8) | rgbBlue; }
};

#pragma pack(pop)

/// CBasicImage��CImgUtil���Ŏg�p���郿�l�Ȃǂ̌^
typedef double Float;	
//typedef float Float;

/// �摜�T�C�Y
typedef unsigned short ImgLength;

template< typename PIXEL > struct AlphaFunc;

/// 8bits��(�J���[�L�[����)
template<>
struct AlphaFunc< unsigned char >{
	AlphaFunc(unsigned char* pDst, const unsigned char* pSrc, int nDstWidth, int nSrcWidth, int x, int y,int left, int top, int width, int height)
	{
		// �Q�l����)��˂��炨���uWindows�v���t�F�b�V���i���Q�[���v���O���~���O2�v
	//	unsigned long dwRgbColorKey = rgbColorKey | (rgbColorKey<<8) | (rgbColorKey<<16) | (rgbColorKey<<24);
		unsigned long dwRgbColorKey = 0;	// �ǂ��������F��0�ŌŒ肾���炱��łn�j��
		while(height-- > 0){
			unsigned long* pcSrc = (unsigned long*)pSrc;
			unsigned long* pcDst = (unsigned long*)pDst;
			while((unsigned char*)pcSrc+4<=pSrc+width){
				unsigned long mask = (*pcSrc ^ dwRgbColorKey);
				// ��xor���Ƃ�΁A���S�Ɉ�v���Ă���ꍇ�A����unsigned char��0�ɂȂ�͂�
				mask = mask | ((mask  & 0x7F7F7F7F) + 0x7F7F7F7F);
				// ������mask��MSB��1�̃o�C�g�́A��v���Ă��Ȃ��̂œ]������K�v������
				mask = (mask & 0x80808080) >> 7;	// LSB�Ɉړ�
				mask = (mask + 0x7F7F7F7F) ^ 0x7F7F7F7F;
				*pcDst = ((*pcSrc ^ *pcDst) & mask) ^ *pcDst;
				pcDst++;
				pcSrc++;
			}

			// �[���̕␳(���ꂭ�炢for�ŉ񂵂Ă�������˂�)
			if((width & 0x03) != 0){
				int max = (width & 0x03);
				unsigned char* psrc = (unsigned char*)pcSrc;
				unsigned char* pdst = (unsigned char*)pcDst;
				while(max-- > 0){
					if(*psrc)	*pdst = *psrc;
					psrc++;
					pdst++;
				}
			}
			pDst += nDstWidth;
			pSrc += nSrcWidth;
		}
	}
};

/// 32bits��(�A���t�@�`�����l������)
template<>
struct AlphaFunc< unsigned long >{
	AlphaFunc(unsigned long* pDst, const unsigned long* pSrc, int nDstWidth, int nSrcWidth, int x, int y,int left, int top, int width, int height)
	{
		unsigned char cSrcR, cSrcG, cSrcB, cAlpha;
		unsigned char cDstR, cDstG, cDstB;

		while(height-->0){
			int w = width;
			const PIXEL*	_pSrc = pSrc;
			PIXEL*			_pDst = pDst;

			while(w-->0){
				cAlpha = Alpha(*_pSrc);
				cSrcR  = Red(*_pSrc);
				cSrcG  = Green(*_pSrc);
				cSrcB  = Blue(*_pSrc);
				cDstR  = Red(*_pDst);
				cDstG  = Green(*_pDst);
				cDstB  = Blue(*_pDst);

			//	/*
				// 1)����S���v�Z����
				*_pDst = (*_pDst & 0xFF000000) |
					CalcAlpha(cSrcR, cDstR, cAlpha)<<16 |
					CalcAlpha(cSrcG, cDstG, cAlpha)<<8 |
					CalcAlpha(cSrcB, cDstB, cAlpha);
			//	*/
				/*
				// 2)���l�ɂ����if����
				if(cAlpha==0x00){
					*_pDst = (*_pDst & 0xFF000000) | cDstR<<16 | cDstG<<8 | cDstB;
				}
				else if(cAlpha==0xFF){
					*_pDst = (*_pDst & 0xFF000000) | cSrcR<<16 | cSrcG<<8 | cSrcB;
				}
			//	else if(cAlpha==0x7F || cAlpha==0x80){
			//		*_pDst = (*_pDst & 0xFF000000) |
			//			((unsigned char)((cSrcR>>1)+(cDstR>>1)))<<16 |
			//			((unsigned char)((cSrcG>>1)+(cDstG>>1)))<<8 |
			//			( unsigned char)((cSrcB>>1)+(cDstB>>1));
			//	}
				else{
					*_pDst = (*_pDst & 0xFF000000) |
						CalcAlpha(cSrcR, cDstR, cAlpha)<<16 |
						CalcAlpha(cSrcG, cDstG, cAlpha)<<8 |
						CalcAlpha(cSrcB, cDstB, cAlpha);
				}
				*/

				_pSrc++;
				_pDst++;
			}

			pSrc += nSrcWidth;
			pDst += nDstWidth;
		}
	}
};

/// 8bits,32bits�ȊO(�ʏ�`��)
template< typename PIXEL >
struct AlphaFunc{
	AlphaFunc(PIXEL* pDst, const PIXEL* pSrc, int nDstWidth, int nSrcWidth, int x, int y,int left, int top, int width, int height)
	{
		unsigned int linesize = sizeof(PIXEL) * width;
		while(height-->0){
			memcpy(pDst, pSrc, linesize);
			pSrc += nSrcWidth;
			pDst += nDstWidth;
		}
	}
};

/// ��{�N���X(�e���v���[�g�ɂ́A1�s�N�Z���ӂ�Ɏg�p����^���w�肵�܂�)
template< typename PIXEL >
class CBasicImage {
private:
//protected:

//#pragma pack(push)
//#pragma pack(1) //�\���̂̃����o���E��1�o�C�g�ɂ���
	/// RGB�̏��ŕ��񂾍\����(CBasicImage�����ł͂���ŊǗ�����܂�)
	typedef struct tagRGBSTRUCT{
		unsigned char	red;			///< ��
		unsigned char	green;			///< ��
		unsigned char	blue;			///< ��
	} RGBSTRUCT;
//#pragma pack(pop)

	ImgLength		m_shWidth;					///< ��
	ImgLength		m_shHeight;					///< ����
	smart_array< PIXEL >		m_saImage;		///< �s�N�Z���f�[�^
	smart_array< RGBSTRUCT >	m_saPalette;	///< �p���b�g�f�[�^
	PIXEL*			m_pIndex;					///< �摜����p�̃|�C���^

public:

	friend class CBasicImage;

	//=============================================================================
	/**
		�R���X�g���N�^

		@param	width		[in] �摜�̕�
		@param	height		[in] �摜�̍���
	*/
	//=============================================================================
	CBasicImage(ImgLength width=0, ImgLength height=0):
		m_shWidth(0),
		m_shHeight(0),
		m_pIndex(NULL)
	{
		Create(width, height);
	}	///< �R���X�g���N�^


	~CBasicImage(){ Destroy(); }	///< �f�X�g���N�^

	/// �R�s�[�R���X�g���N�^
	CBasicImage(const CBasicImage& obj){ operator=(obj); }

	// ����R���X�g���N�^
	CBasicImage& operator=(const CBasicImage& obj)
	{
		m_shWidth	= obj.m_shWidth;
		m_shHeight	= obj.m_shHeight;
		m_pIndex	= obj.m_pIndex;

		if(obj.m_saImage!=NULL)		m_saImage.Copy(obj.m_saImage);
		else						m_saImage.Release();
		if(obj.m_saPalette!=NULL)	m_saPalette.Copy(obj.m_saPalette);
		else						m_saPalette.Release();

		return *this;
	}

	//=============================================================================
	/**
		�摜���쐬

		@note				nWidth��nHeight�̂ǂ��炩��0���w�肷��Ɖ����������܂�

		@param	width		[in] ��
		@param	height		[in] ����
	*/
	//=============================================================================
	void Create(ImgLength width, ImgLength height)
	{
		Destroy();

		if(width && height){
			m_shWidth	= width;
			m_shHeight	= height;
			m_saImage.Resize(m_shWidth * m_shHeight);

			// 8�r�b�g�ȉ��Ȃ�p���b�g�̊m��
			if(GetBitCount()<=8){
				m_saPalette.Resize( 1<<GetBitCount() );
			}
			Clear(true);
			Top();
		}
	}	///< �摜���쐬

	/// �摜�f�[�^�̉��
	void Destroy()
	{
		/*
		if(m_saImage!=NULL){
			m_saImage.Release();
			m_pIndex = NULL;
			m_shWidth = m_shHeight = 0;
		}
		if(m_saPalette!=NULL){
			m_saPalette.Release();
		}
		*/
		m_saImage.Release();
		m_pIndex = NULL;
		m_shWidth = m_shHeight = 0;
		m_saPalette.Release();
	}	///< �摜�f�[�^�̉��

	//=============================================================================
	/**
		�摜�f�[�^��0�ŏ���������

		@param	bPalInit		[in] �p���b�g�f�[�^�����������邩�ǂ���
	*/
	//=============================================================================
	void Clear(bool bPalInit=false)
	{
		if(IsInit()){
			memset(m_saImage.GetPtr(), 0, sizeof(PIXEL)*m_saImage.GetSize());
		}

		if(m_saPalette!=NULL && bPalInit){
			memset(m_saPalette.GetPtr(), 0, sizeof(RGBSTRUCT)*m_saPalette.GetSize());
		}
	}	///< �摜�f�[�^��0�ŏ���������

	//=============================================================================
	/**
		�p���b�g���Z�b�g����

		@param	index		[in] �p���b�g�ԍ�
		@param	red			[in] ��
		@param	green		[in] ��
		@param	blue		[in] ��

		@retval	true		�p���b�g�̃Z�b�g�ɐ���
		@retval	false		�p���b�g�̃Z�b�g�Ɏ��s
	*/
	//=============================================================================
	bool SetPalette(unsigned short index, unsigned char red, unsigned char green, unsigned char blue)
	{
		if(m_saPalette!=NULL && index<m_saPalette.GetSize()){
			m_saPalette[index].red		= red;
			m_saPalette[index].green	= green;
			m_saPalette[index].blue		= blue;

			return true;
		}
		return false;
	}

	//=============================================================================
	/**
		�p���b�g���擾����

		@param	index		[in] �p���b�g�ԍ�
		@param	red			[out] ��
		@param	green		[out] ��
		@param	blue		[out] ��

		@retval	true		�p���b�g�̎擾�ɐ���
		@retval	false		�p���b�g�̎擾�Ɏ��s
	*/
	//=============================================================================
	bool GetPalette(unsigned short index, unsigned char* red, unsigned char* green, unsigned char* blue) const
	{
		if(m_saPalette!=NULL && index<m_saPalette.GetSize()){
			*red	= m_saPalette[index].red;
			*green	= m_saPalette[index].green;
			*blue	= m_saPalette[index].blue;

			return true;
		}

		return false;
	}

	//=============================================================================
	/**
		�ʂ̉摜�̃p���b�g���R�s�[����

		@param	img			[in] �R�s�[���摜
	*/
	//=============================================================================
	void CopyPalette(const CBasicImage< PIXEL >& img)
	{
		unsigned char r, g, b;
		unsigned int i;

		if(img.GetPalSize() >0){
			for(i = 0; i < img.GetPalSize(); i++){
				img.GetPalette(i, &r, &g, &b);
				SetPalette(i, r, g, b);
			}
		}
	}

	bool IsInit() const { return (m_saImage!=NULL); }					///< ����������Ă��邩�ǂ���
	bool operator!() const{ return !IsInit(); }							///< ����������Ă��Ȃ����true

	ImgLength		GetWidth()    const { return m_shWidth; }			///< �摜�̕����擾
	ImgLength		GetHeight()   const { return m_shHeight; }			///< �摜�̍������擾
	unsigned char	GetBitCount() const { return sizeof(PIXEL)*8; }		///< �摜�̐F�����擾
	unsigned short	GetPalSize()  const { return (unsigned short)m_saPalette.GetSize(); }///< �p���b�g�T�C�Y���擾

	bool IsEof() { return (m_pIndex==m_saImage.GetEndPtr()); }	///< �摜�̏I�[���ǂ���
	bool IsTop() { return (m_pIndex==m_saImage.GetPtr()); }		///< �摜�̐擪���ǂ���

	///////////////// �s�N�Z������p�̊֐�
	//=============================================================================
	/**
		�s�N�Z���f�[�^���Z�b�g����

		@param	x			[in] x�ʒu
		@param	y			[in] y�ʒu
		@param	pixel		[in] �s�N�Z���f�[�^
	*/
	//=============================================================================
	void SetPixel(ImgLength x, ImgLength y, PIXEL pixel)
	{
		if(x<m_shWidth && y<m_shHeight){
			m_saImage[y*m_shWidth+x] = pixel;
		}
	}

	//=============================================================================
	/**
		�s�N�Z���f�[�^���擾����

		@param	x			[in] x�ʒu
		@param	y			[in] y�ʒu

		@return				�s�N�Z���f�[�^
	*/
	//=============================================================================
	PIXEL GetPixel(ImgLength x, ImgLength y) const
	{
		if(x<m_shWidth && y<m_shHeight){
			return m_saImage[y*m_shWidth+x];
		}

		return 0;
	}

	PIXEL* Index(){  return m_pIndex; }									///< ���݂̃s�N�Z��

	PIXEL* Top(){ m_pIndex = m_saImage.GetPtr(); return m_pIndex; }		///< �摜�̐擪��(����)�Ɉړ�

	/// ���̃s�N�Z���Ɉړ�
	PIXEL* Next()
	{
		if(!IsEof())	m_pIndex++;
		return m_pIndex;
	}

	/// �O�̃s�N�Z���Ɉړ�
	PIXEL* Prev()
	{
		if(!IsTop())	m_pIndex--;
		return m_pIndex;
	}

	/// ���̍s�Ɉړ�
	PIXEL* NextLine()
	{
		m_pIndex += m_shWidth;
		if(m_pIndex>m_saImage.GetEndPtr())	m_pIndex = m_saImage.GetEndPtr();
		return m_pIndex;
	}

	/// �O�̍s�Ɉړ�
	PIXEL* PrevLine()
	{
		m_pIndex -= m_shWidth;
		if(m_pIndex<m_saImage.GetPtr())	m_pIndex = m_saImage.GetPtr();
		return m_pIndex;
	}

	//=============================================================================
	/**
		���W���w�肵�Ĉړ�

		@param	x			[in] x�ʒu
		@param	y			[in] y�ʒu

		@return				�s�N�Z���f�[�^�ւ̃|�C���^
	*/
	//=============================================================================
	PIXEL* Locate(ImgLength x, ImgLength y)
	{
		if(x<m_shWidth && y<m_shHeight)	m_pIndex = &m_saImage[y*m_shWidth+x];
		return m_pIndex;
	}	///< ���W���w�肵�Ĉړ�

	//=============================================================================
	/**
		���̍��W�̃|�C���^���擾

		@param	x			[in] x�ʒu
		@param	y			[in] y�ʒu

		@return				�s�N�Z���f�[�^�ւ̃|�C���^
	*/
	//=============================================================================
	const PIXEL* GetPtr(ImgLength x, ImgLength y) const
	{
		if(x<m_shWidth && y<m_shHeight)	return &m_saImage[y*m_shWidth+x];
		return &m_saImage[0];
	}	///< ���W���w�肵�Ĉړ�

	//=============================================================================
	/**
		�Z�a��h��Ԃ�

		@param	color		[in] �F
		@param	left		[in] ����x���W
		@param	top			[in] ����y���W
		@param	width		[in] ��(�ȗ���:�������g�̕�)
		@param	height		[in] ����(�ȗ���:�������g�̍���)

		@return				�s�N�Z���f�[�^�ւ̃|�C���^
	*/
	//=============================================================================
	void FillRect(PIXEL color, ImgLength left=0, ImgLength top=0, ImgLength width=0, ImgLength height=0)
	{
		if(left > GetWidth())	left = GetWidth();
		if(top > GetHeight())	top  = GetHeight();
		if(width == 0)			width  = GetWidth()  - left;
		if(height == 0)			height = GetHeight() - top;

		PIXEL* pDst = Locate(left, top);

		while(height-->0){
			int w = width;
			PIXEL* p = pDst;

			while(w-->0){
				*p++ = color;
			}

			pDst = NextLine();
		}
	}

	//=============================================================================
	/**
		���`�����l�������̒l�Ŗ��߂�(32bits only)

		@param	alpha		[in] ���l
	*/
	//=============================================================================
	void FillAlpha(unsigned char alpha)
	{
		if(sizeof(PIXEL)==4 && IsInit()){
			PIXEL* p		= m_saImage.GetPtr();
			PIXEL* p_end	= m_saImage.GetEndPtr();
			while(p < p_end){
				*p = (*p & 0x00FFFFFF) | (alpha << 24);
				p++;
			}
		}
	}	///< ���`�����l�������̒l�Ŗ��߂�(32bits only)

	//=============================================================================
	/**
		�`��͈͂̃`�F�b�N�����A�K�v�ɉ����Đ��l�␳��������

		@param	imgSrc		[in,out] �R�s�[���摜
		@param	x			[in,out] �R�s�[��x���W
		@param	y			[in,out] �R�s�[��y���W
		@param	left		[in,out] �R�s�[��x���W
		@param	top			[in,out] �R�s�[��y���W
		@param	width		[in,out] �R�s�[����
		@param	height		[in,out] �R�s�[������
	*/
	//=============================================================================
	bool RectCheck(const CBasicImage< PIXEL >& imgSrc, int& x, int& y,
		int& left, int& top, int& width, int& height) const
	{
		if(!IsInit() || !imgSrc.IsInit())		return false;

		if(left < 0)						left = 0;
		if(top < 0)							top  = 0;
		else if(left >= imgSrc.GetWidth())	left = imgSrc.GetWidth() - 1;
		else if(top >= imgSrc.GetHeight())	top  = imgSrc.GetHeight() - 1;

		if(width == 0)		width  = imgSrc.GetWidth()  - left;
		if(height == 0)		height = imgSrc.GetHeight() - top;

		if(x < 0){
			width += x;		// x�͕��Ȃ̂Ō��ʓI�Ɍ��Z
			left  -= x;		// x�͕��Ȃ̂Ō��ʓI�ɉ��Z
			x = 0;
		}
		if(y < 0){
			height += y;	// y�͕��Ȃ̂Ō��ʓI�Ɍ��Z
			top    -= y;	// y�͕��Ȃ̂Ō��ʓI�ɉ��Z
			y = 0;
		}

		if(width > GetWidth()-x)	width  = GetWidth()  - x;
		if(height > GetHeight()-y)	height = GetHeight() - y;

		if(width<=0 || height<=0)	return false;

		return true;
	}

	//=============================================================================
	/**
		�摜��`�悷��

		@param	img			[in] �R�s�[���摜
		@param	x			[in] �R�s�[��x���W
		@param	y			[in] �R�s�[��y���W
		@param	left		[in] �R�s�[��x���W
		@param	top			[in] �R�s�[��y���W
		@param	width		[in] �R�s�[����(�ȗ���:���摜�̕�)
		@param	height		[in] �R�s�[������(�ȗ���:���摜�̍���)
		@param	bAlpha		[in]	32bits:���`�����l���v�Z�����邩�ǂ���(false�ŃR�s�[���摜��Z�a�R�s�[����)
									8bits:0�Ԃ𔲂��F�Ƃ��ď���
									����ȊO:����

		@retval	true		�`�搬��
		@retval	false		�`�掸�s
	*/
	//=============================================================================
	bool Blt(const CBasicImage< PIXEL >& img, int x=0, int y=0,
		int left=0, int top=0, int width=0, int height=0, bool bAlpha=true)
	{
		if(!RectCheck(img, x, y, left, top, width, height))		return false;

		const PIXEL*	pSrc = img.GetPtr(left, top);
		PIXEL*			pDst = Locate(x, y);

		if(bAlpha){
			AlphaFunc< PIXEL >(pDst, pSrc, GetWidth(), img.GetWidth(), x, y, left, top, width, height);
		}
		// ���ʂ̏���(�s�N�Z�������̂܂܏㏑������)
		else{
			unsigned int linesize = sizeof(PIXEL) * width;
			while(height-->0){
				memcpy(pDst, pSrc, linesize);
				pSrc += img.GetWidth();
				pDst += GetWidth();
			}
			/*
			for(unsigned int j = 0; j < height; j++){
				for(unsigned int i = 0; i < width; i++){
					SetPixel(x+i, y+j, img.GetPixel(left+i, top+j));
				}
			}
			*/
		}

		return true;
	}

	//=============================================================================
	/**
		�g��/�k�������摜���擾����

		@param	nZoom		[in] �g�嗦(���w��)

		@return				�g��/�k��������̉摜
	*/
	//=============================================================================
	CBasicImage< PIXEL > Zoom(int nZoom) const
	{
		// ����
		if(nZoom==100)		return *this;

		return Zoom((Float)nZoom/100.0);
	}
	//=============================================================================
	/**
		�g��/�k�������摜���擾����

		@param	fZoom		[in] �g�嗦(�����w��)

		@return				�g��/�k��������̉摜
	*/
	//=============================================================================
	CBasicImage< PIXEL > Zoom(Float fZoom) const
	{
		CBasicImage< PIXEL > img;
		ImgLength x, y;

		// ����
		if(fZoom==1.0)		return *this;

		if(IsInit()){
			img.Create((ImgLength)(GetWidth()*fZoom), (ImgLength)(GetHeight()*fZoom));
			img.CopyPalette(*this);
			for(y = 0; y < img.GetHeight(); y++){
				for(x = 0; x < img.GetWidth(); x++){
					img.SetPixel(x, y, GetPixel((ImgLength)(x/fZoom),(ImgLength)(y/fZoom)));
				}
			}
		}

		return img;
	}
};

typedef CBasicImage< unsigned char  >		CImage8;	///< 8bits  color only
typedef CBasicImage< unsigned short >		CImage16;	///< 16bits color only
typedef CBasicImage< sueLib::RGBTRIPLE >	CImage24;	///< 24bits color only
//typedef CBasicImage< RGBTRIPLE >			CImage24;	///< 24bits color only
typedef CBasicImage< unsigned long  >		CImage32;	///< 32bits color only

} // end of namespace sueLib

#endif
