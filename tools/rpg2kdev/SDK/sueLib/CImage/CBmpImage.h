/**
	@file
	@brief		CBasicImage��HBITMAP�ɕϊ�����
	@author		sue445
*/
#ifndef _INC_CBMPIMAGE
#define _INC_CBMPIMAGE

#include <windows.h>
#include "CImage.h"
#include "../smart_buffer.h"

namespace sueLib {

/*
/// �A���t�@�`�����l���̖�����(32bits�ȊO�ł͎��s���Ȃ�)
template< typename PIXEL > struct AlphaDisable;

template<>
struct AlphaDisable< unsigned long >{
	AlphaDisable(CBasicImage< unsigned long >& img)
	{
		unsigned long* p = img.Top();
		while(!img.IsEof()){
			if((*p & 0xFF000000)==0)		*p = 0x00FFFFFF;
			p = img.Next();
		}
	}
};
template< typename PIXEL >
struct AlphaDisable{
	AlphaDisable(CBasicImage< PIXEL >& img){}
};
*/

template< typename PIXEL >
class CBmpImage : public CBasicImage< PIXEL >{
private:
	/// �㉺���](4�o�C�g�␳�L��)
	void MirrorY(CBasicImage< PIXEL >& imgDst, CBasicImage< PIXEL >& imgSrc)
	{
		imgDst.Create(((imgSrc.GetWidth()*sizeof(PIXEL)+3) & ~3)/sizeof(PIXEL), imgSrc.GetHeight());
		imgDst.Locate(0, 0);					// �ォ�牺��
		imgSrc.Locate(0, imgSrc.GetHeight()-1);	// ��������
		DWORD widthsize = imgSrc.GetWidth()*sizeof(PIXEL);
		while(!imgDst.IsEof()){
			memcpy(imgDst.Index(), imgSrc.Index(), widthsize);
			imgDst.NextLine();
			imgSrc.PrevLine();
		}
	}
	void AlphaDisable(CImage32& img)
	{
		unsigned long* p = img.Top();
		while(!img.IsEof()){
			if((*p & 0xFF000000)==0)		*p = 0x00FFFFFF;
			p = img.Next();
		}
	}
	void AlphaDisable(CImage24& img){}
	void AlphaDisable(CImage16& img){}
	void AlphaDisable(CImage8& img){}

public:
	/// �f�t�H���g�R���X�g���N�^
	CBmpImage(ImgLength width=0, ImgLength height=0) : CBasicImage< PIXEL >(width,height) {}

	/// �R�s�[�R���X�g���N�^
	CBmpImage(const CBasicImage< PIXEL >& obj){ operator=(obj); }

	/// ����R���X�g���N�^
	CBmpImage& operator=(const CBasicImage< PIXEL >& obj)
	{
		ImgLength x, y;
		unsigned char r, g, b;
		unsigned short i;

		// CBasicImage����friend���Ă�private�ɃA�N�Z�X�ł��Ȃ�(��
		Create(obj.GetWidth(), obj.GetHeight());

		for(y = 0; y < GetHeight(); y++){
			for(x = 0; x < GetWidth(); x++){
				SetPixel(x, y, obj.GetPixel(x, y));
			}
		}

		CopyPalette(obj);

		return *this;
	}

	/// �r�b�g�}�b�v���擾
	HBITMAP GetBitmap(HWND hWnd, int nLeft=0, int nTop=0, int nWidth=0, int nHeight=0)
	{
		CBasicImage< PIXEL > imgTemp;	// 4�o�C�g�␳����DIB�f�[�^
		BITMAPINFO* pinfo = (BITMAPINFO*)malloc( sizeof(BITMAPINFOHEADER)+GetPalSize()*sizeof(RGBQUAD) );

		if(nLeft<0)		nLeft = 0;
		if(nTop<0)		nTop = 0;
		if(nWidth<=0  || nWidth>GetWidth()-nLeft)	nWidth  = GetWidth() - nLeft;
		if(nHeight<=0 || nHeight>GetHeight()-nTop)	nHeight = GetHeight() - nTop;

		if(nLeft==0 && nTop==0 && nWidth==GetWidth() && nHeight==GetHeight()){
			MirrorY(imgTemp, *this);
			AlphaDisable(imgTemp);
		}
		else{
			CBasicImage< PIXEL > img;	// �Z�a�I��p
			img.Create(nWidth, nHeight);
			Locate(nLeft, nTop);
			DWORD widthsize = nWidth * sizeof(PIXEL);
			for(int i = 0; i < nHeight; i++){
				memcpy(img.Index(), Index(), widthsize);
				NextLine();
				img.NextLine();
			}
			MirrorY(imgTemp, img);
			AlphaDisable(imgTemp);
		}

		// �r�b�g�}�b�v�����쐬
		ZeroMemory(pinfo, sizeof(BITMAPINFO));
		pinfo->bmiHeader.biSize				= sizeof(BITMAPINFOHEADER);
		pinfo->bmiHeader.biWidth			= nWidth;
		pinfo->bmiHeader.biHeight			= nHeight;
		pinfo->bmiHeader.biPlanes			= 1;
		pinfo->bmiHeader.biBitCount			= (WORD)GetBitCount();
		pinfo->bmiHeader.biCompression		= BI_RGB;
		pinfo->bmiHeader.biSizeImage		= imgTemp.GetWidth()*imgTemp.GetHeight()*sizeof(PIXEL);
		pinfo->bmiHeader.biXPelsPerMeter	= 0;
		pinfo->bmiHeader.biYPelsPerMeter	= 0;
		pinfo->bmiHeader.biClrUsed			= 0;
		pinfo->bmiHeader.biClrImportant		= 0;

		// �p���b�g���R�s�[
		if(GetPalSize()>0){
			int max = GetPalSize();
			RGBQUAD* rgb = (RGBQUAD*)&pinfo->bmiColors[0];
			for(int i = 0; i < max; i++){
				GetPalette(i, &rgb->rgbRed, &rgb->rgbGreen, &rgb->rgbBlue);
				rgb++;
			}
		}

		PAINTSTRUCT	ps;
		HDC			hdc = BeginPaint(hWnd, &ps);

		HBITMAP hRet = CreateDIBitmap(hdc, &pinfo->bmiHeader, CBM_INIT, imgTemp.Top(), pinfo, DIB_RGB_COLORS);
		EndPaint(hWnd, &ps);

//		free(pinfo);
		return hRet;
	}
};

typedef CBmpImage< unsigned char  >			CBmp8;	///< 8bits  color only
typedef CBmpImage< unsigned short >			CBmp16;	///< 16bits color only
typedef CBmpImage< sueLib::RGBTRIPLE >		CBmp24;	///< 24bits color only
//typedef CBmpImage< RGBTRIPLE >			CBmp24;	///< 24bits color only
typedef CBmpImage< unsigned long  >			CBmp32;	///< 32bits color only

} // end of namespace sueLib

#endif
