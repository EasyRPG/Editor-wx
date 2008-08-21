/**
	@file
	@brief		ZLib compression class
	@note		<Reference URL> http://oku.edu.mie-u.ac.jp/~okumura/compression/zlib.html
	@author		sue445
*/
#include "CZLib.h"
#include <zlib.h>

/*
zlib Ver1.23�FCopyright (C) 1995-2005 Jean-loup Gailly and Mark Adler
<URL> http://www.gzip.org/zlib/
*/
// �����[�X�R���p�C����
#ifndef _DEBUG
	#pragma comment( lib, "zlib.lib" )
// �f�o�b�O�R���p�C����
#else
	#pragma comment( lib, "zlibd.lib" )
#endif

//#define ERROR_PRINT			// printf�ɂ��G���[�o�͂��s�����ǂ���


namespace sueLib {

//static const int nInBufSize		= 1024*10;		// ���̓o�b�t�@�T�C�Y�i�C�Ӂj
//static const int nOutBufSize	= 1040*10;		// �o�̓o�b�t�@�T�C�Y�i����~1.001�{12�j
static const int nInBufSize		= 1024*32;		// ���̓o�b�t�@�T�C�Y�i�C�Ӂj
static const int nOutBufSize	= (int)(nInBufSize * 1.001) + 12;		// �o�̓o�b�t�@�T�C�Y�i����~1.001�{12�j

//=============================================================================
/**
	zlib�œW�J

	@param	pstInput		[in] ���̓X�g���[��
	@param	pstOutput		[out] �o�̓X�g���[��(NULL���w�肷��Ώ����o�����s�킸�A�K�v�T�C�Y�̌v�Z�݂̂��s��)
	@param	lpSize			[out] �W�J��T�C�Y�̎擾��(NULL�Ŏ擾���Ȃ�)

	@retval	true			����
	@retval	false			���s
*/
//=============================================================================
bool CZLib::Decompress(CBasicStream* pstInput, CBasicStream* pstOutput, unsigned int* lpSize)
{
	z_stream z; 							// ���C�u�����Ƃ��Ƃ肷�邽�߂̍\����
	unsigned char inbuf[nInBufSize];		// ���̓o�b�t�@
	unsigned char outbuf[nOutBufSize]; 		// �o�̓o�b�t�@
	int count, status;
	unsigned int outsize = 0;				// �����o�����T�C�Y(�߂�l�p)

	if(!pstInput || !pstInput->IsOpened() || pstInput->IsWriteMode())		return false;	// ���̓X�g���[��������������Ă��Ȃ�
	if(pstOutput && (!pstOutput->IsOpened() || !pstOutput->IsWriteMode()))	return false;	// �o�̓X�g���[�����s��


	// ���ׂẴ������Ǘ������C�u�����ɔC����
	z.zalloc = Z_NULL;	// �����̃������m�ۂɎg���܂�
	z.zfree  = Z_NULL;	// �����̃���������Ɏg���܂�
	z.opaque = Z_NULL;	// zalloc �� zfree �ɓn����� �v���C�x�[�g�f�[�^�E�I�u�W�F�N�g

	// ������
	z.next_in = Z_NULL;
	z.avail_in = 0;

	if(inflateInit(&z) != Z_OK){
#ifdef ERROR_PRINT
		printf("inflateInit: %s\n", (z.msg) ? z.msg : "???");
#endif
		return false;
	}

	z.next_out  = outbuf;		// �o�̓|�C���^
	z.avail_out = nOutBufSize;	// �o�̓o�b�t�@�c��
	status = Z_OK;

	while(status != Z_STREAM_END){
		if(z.avail_in == 0){	// ���͎c�ʂ��[���ɂȂ�� 
			z.next_in  = inbuf;	// ���̓|�C���^�����ɖ߂�
			z.avail_in = pstInput->Read(inbuf, nInBufSize);
		}
		status = inflate(&z, Z_NO_FLUSH);	// �W�J
		if(status == Z_STREAM_END){			// ����
			break;
		}
		else if(status != Z_OK){			// �G���[
#ifdef ERROR_PRINT
			printf("inflate: %s\n", (z.msg) ? z.msg : "???");
#endif
			return false;
		}
		if(z.avail_out == 0){				// �o�̓o�b�t�@���s�����
			// �܂Ƃ߂ď����o��
			if(pstOutput)	outsize += pstOutput->Write(outbuf, nOutBufSize);
			else			outsize += nOutBufSize;

			z.next_out  = outbuf;			// �o�̓|�C���^�����ɖ߂�
			z.avail_out = nOutBufSize;		// �o�̓o�b�t�@�c�ʂ����ɖ߂�
		}
	}

	// �c���f���o��
	if((count = nOutBufSize - z.avail_out) != 0){
		if(pstOutput)	outsize += pstOutput->Write(outbuf, count);
		else			outsize += count;
	}

	// ��n��
	if(inflateEnd(&z) != Z_OK){
#ifdef ERROR_PRINT
		printf("inflateEnd: %s\n", (z.msg) ? z.msg : "???");
#endif
		return false;
	}

	if(lpSize)		*lpSize = outsize;
	return true;
}

//=============================================================================
/**
	zlib�ň��k

	@param	pstInput		[in] ���̓X�g���[��
	@param	pstOutput		[out] �o�̓X�g���[��(NULL���w�肷��Ώ����o�����s�킸�A�K�v�T�C�Y�̌v�Z�݂̂��s��)
	@param	lpSize			[out] ���k��T�C�Y�̎擾��(NULL�Ŏ擾���Ȃ�)
	@param	nCompLv			[in] �ۑ����̈��k���x��(0(�����k)�`9(�ō����k), -1�ŕW�����k)

	@retval	true			����
	@retval	false			���s
*/
//=============================================================================
bool CZLib::Compress(CBasicStream* pstInput, CBasicStream* pstOutput, int nCompLv, unsigned int* lpSize)
{
	z_stream z; 							// ���C�u�����Ƃ��Ƃ肷�邽�߂̍\����
	unsigned char inbuf[nInBufSize];		// ���̓o�b�t�@
	unsigned char outbuf[nOutBufSize]; 		// �o�̓o�b�t�@
	int count, flush, status;
	unsigned int outsize = 0;				// �����o�����T�C�Y(�߂�l�p)

	if(!pstInput || !pstInput->IsOpened() || pstInput->IsWriteMode())		return false;	// ���̓X�g���[��������������Ă��Ȃ�
	if(pstOutput && (!pstOutput->IsOpened() || !pstOutput->IsWriteMode()))	return false;	// �o�̓X�g���[�����s��
	if(nCompLv<-1 || nCompLv>9)		return false;	// ���k���x������������


	// ���ׂẴ������Ǘ������C�u�����ɔC����
	z.zalloc = Z_NULL;	// �����̃������m�ۂɎg���܂�
	z.zfree  = Z_NULL;	// �����̃���������Ɏg���܂�
	z.opaque = Z_NULL;	// zalloc �� zfree �ɓn����� �v���C�x�[�g�f�[�^�E�I�u�W�F�N�g


	// ������
	// ��2�����͈��k�̓x���B0�`9 �͈̔͂̐����ŁC0 �͖����k
	// Z_DEFAULT_COMPRESSION (= 6) ���W��
//	/*
	if(deflateInit(&z, nCompLv) != Z_OK){
#ifdef ERROR_PRINT
		printf("deflateInit: %s\n", (z.msg) ? z.msg : "???");
#endif
		return false;
	}
//	*/


	/*
//	z.next_in = Z_NULL;	// ���̓|�C���^����̓o�b�t�@�̐擪��
	if(deflateInit2(&z, nCompLv, Z_DEFLATED, 15, 9, Z_DEFAULT_STRATEGY) != Z_OK){
#ifdef ERROR_PRINT
		printf("deflateInit2: %s\n", (z.msg) ? z.msg : "???");
#endif
		return false;
	}
	*/

	z.avail_in = 0; 			// ���̓o�b�t�@���̃f�[�^�̃o�C�g��
	z.next_out = outbuf;		// �o�̓|�C���^
	z.avail_out = nOutBufSize;	// �o�̓o�b�t�@�̃T�C�Y

	// �ʏ�� deflate() �̑�2������ Z_NO_FLUSH �ɂ��ČĂяo��
	flush = Z_NO_FLUSH;

	while(1){
		if(z.avail_in == 0){	// ���͂��s�����
			z.next_in = inbuf;	// ���̓|�C���^����̓o�b�t�@�̐擪��
			z.avail_in = pstInput->Read(inbuf, nInBufSize);

			// ���͂��Ō�ɂȂ����� deflate() �̑�2������ Z_FINISH �ɂ���
			if(z.avail_in < nInBufSize)		flush = Z_FINISH;
		}
		status = deflate(&z, flush);	// ���k����
		if(status == Z_STREAM_END){		// ����
			break;
		}
		else if(status != Z_OK){		// �G���[
#ifdef ERROR_PRINT
			printf("deflate: %s\n", (z.msg) ? z.msg : "???");
#endif
			return false;
		}
		if(z.avail_out == 0){			// �o�̓o�b�t�@���s�����
			// �܂Ƃ߂ď����o��
			if(pstOutput)	outsize += pstOutput->Write(outbuf, nOutBufSize);
			else			outsize += nOutBufSize;

			z.next_out = outbuf;		// �o�̓o�b�t�@�c�ʂ����ɖ߂�
			z.avail_out = nOutBufSize;	// �o�̓|�C���^�����ɖ߂�
		}
	}

	// �c���f���o��
	if((count = nOutBufSize - z.avail_out) != 0){
		if(pstOutput)	outsize += pstOutput->Write(outbuf, count);
		else			outsize += count;
	}

	// ��n��
	if(deflateEnd(&z) != Z_OK){
#ifdef ERROR_PRINT
		printf("deflateEnd: %s\n", (z.msg) ? z.msg : "???");
#endif
		return false;
	}

	if(lpSize)	*lpSize = outsize;
	return true;
}

//=============================================================================
/**
	�������W�J

	@param	bufSrc		[in] ���͌��o�b�t�@(���k�f�[�^)
	@param	bufDst		[out] �o�͐�o�b�t�@(�I���W�i���f�[�^)

	@retval	true		����
	@retval	false		���s
*/
//=============================================================================
bool CZLib::MemDecompress(const smart_buffer& bufSrc, smart_buffer& bufDst)
{
	CBasicStream stSrc, stDst;
	unsigned int nSize;

	// ���̓X�g���[���̏������Ɏ��s
	if(!stSrc.OpenFromMemory(bufSrc.GetConstPtr(), bufSrc.GetSize(), false))	return false;

	// �W�J��̃T�C�Y�̎擾�Ɏ��s
	if(!Decompress(&stSrc, NULL, &nSize))			return false;

	if(nSize>0){
		bufDst.Resize(nSize);

		// �o�̓X�g���[���̏������Ɏ��s
		if(!stDst.OpenFromMemory(bufDst.GetPtr(), bufDst.GetSize(), true))	return false;

		// ���̓X�g���[���������߂�
		stSrc.SetSeek(0, SEEK_SET);

		// �W�J�Ɏ��s
		if(!Decompress(&stSrc, &stDst))					return false;
	}
	else{
		bufDst.Release();
	}

	return true;
}

//=============================================================================
/**
	���������k

	@param	bufSrc		[in] ���͌��o�b�t�@(�I���W�i���f�[�^)
	@param	bufDst		[out] �o�͐�o�b�t�@(���k�f�[�^)
	@param	nCompLv		[in] �ۑ����̈��k���x��(0(�����k)�`9(�ō����k), -1�ŕW�����k)

	@retval	true		����
	@retval	false		���s
*/
//=============================================================================
bool CZLib::MemCompress(const smart_buffer& bufSrc, smart_buffer& bufDst, int nCompLv)
{
	CBasicStream stSrc, stDst;
	unsigned int nSize;

	// ���̓X�g���[���̏������Ɏ��s
	if(!stSrc.OpenFromMemory(bufSrc.GetConstPtr(), bufSrc.GetSize(), false))	return false;

	// ���k��̃T�C�Y�̎擾�Ɏ��s
	if(!Compress(&stSrc, NULL, nCompLv, &nSize))		return false;

	bufDst.Resize(nSize);

	// �o�̓X�g���[���̏������Ɏ��s
	if(!stDst.OpenFromMemory(bufDst.GetPtr(), bufDst.GetSize(), true))	return false;

	// ���̓X�g���[���������߂�
	stSrc.SetSeek(0, SEEK_SET);

	// ���k�Ɏ��s
	if(!Compress(&stSrc, &stDst, nCompLv, NULL))	return false;

	return true;
}

} // end of namespace sueLib

