/**
	@file
	@brief		�t�@�C�����͂ƃ��������͂𓯂��悤�Ɉ������߂̊�{�X�g���[��
	@author		sue445
*/
#include "CBasicStream.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>


//=============================================================================
/**
	�������f�[�^����X�g���[�����J��

	@param	pData		[in] �������f�[�^�ւ̃|�C���^
	@param	nLength		[in] �������f�[�^�̃T�C�Y
	@param	bWrite		[in] �������݃��[�h���ǂ���(�ȗ���:false)
	@note				���������̃X�g���[���łȂ��������o�����[�h�̏ꍇ�AnLength�Ŏw�肵��\n
						�T�C�Y�ȏ�������o�����Ƃ͂ł��܂���

	@retval	true		�X�g���[���̏������ɐ���
	@retval	false		�X�g���[���̏������Ɏ��s
*/
//=============================================================================
bool CBasicStream::OpenFromMemory(const void* pData, unsigned int nLength, bool bWrite)
{
	if(m_bOpened || pData==NULL || nLength==0)		return false;

	m_pData		= pData;
	m_nLength	= nLength;
	m_nPosition	= 0;
	m_bFile		= false;
	m_bOpened	= true;
	m_bWrite	= bWrite;

	return true;
}

//=============================================================================
/**
	�t�@�C������X�g���[�����J��

	@param	szFile		[in] �t�@�C����
	@param	bWrite		[in] �������݃��[�h���ǂ���(�ȗ���:false)

	@retval	true		�X�g���[���̏������ɐ���
	@retval	false		�X�g���[���̏������Ɏ��s
*/
//=============================================================================
bool CBasicStream::OpenFromFile(const char* szFile, bool bWrite)
{
	if(m_bOpened)		return false;

	if(!bWrite){
		m_nFile = _open( szFile, _O_BINARY | _O_RDONLY, _S_IREAD);
	}
	else{
		m_nFile = _open( szFile, _O_BINARY | _O_WRONLY | _O_CREAT | _O_TRUNC, _S_IWRITE);
	}
	if(m_nFile==-1)		return false;	// �t�@�C���̃I�[�v���Ɏ��s

	m_nLength	= static_cast< unsigned int >( _filelengthi64( m_nFile ) );
	m_nPosition	= 0;
	m_bFile		= true;
	m_bOpened	= true;
	m_bWrite	= bWrite;

	return true;
}

//=============================================================================
/**
	�X�g���[�����������

	@note		�f�X�g���N�^�Ŏ��s�����̂Ŗ����I�ɍs���K�v�͂���܂���
*/
//=============================================================================
void CBasicStream::Close()
{
	if(!m_bOpened)		return;

	m_pData = NULL;
	m_nLength = m_nPosition = 0;
	if(m_bFile){
		_close(m_nFile);
		m_nFile = -1;
		m_bFile = false;
	}
	m_bOpened = m_bWrite = false;
}

//=============================================================================
/**
	�X�g���[���̓ǂݏo���ʒu���Z�b�g����

	@param	nPos		[in] �ړ���
	@param	nOrigin		[in] ��ʒu(SEEK_SET:�擪, SEEK_END:�I�[, SEEK_CUR:���݈ʒu)
*/
//=============================================================================
void CBasicStream::SetSeek(int nPos, int nOrigin)
{
	if(!m_bOpened)		return;

	switch(nOrigin){
	case SEEK_CUR:
		m_nPosition += nPos;
		break;
	case SEEK_END:
		m_nPosition = m_nLength - nPos;
		break;
	case SEEK_SET:
		m_nPosition = nPos;
		break;
	default:
		return;
	}

	if(m_nPosition > m_nLength)		m_nPosition = m_nLength;

	if(m_bFile)		_lseeki64(m_nFile, m_nPosition, SEEK_SET);
}

//=============================================================================
/**
	�X�g���[������w��T�C�Y�ǂݍ���

	@param	pData	[out] �ǂݍ��ރf�[�^�̃|�C���^
	@param	nSize	[in] �ǂݍ��ރf�[�^�̃T�C�Y

	@return			���ۂɓǂݍ��񂾃T�C�Y
*/
//=============================================================================
unsigned int CBasicStream::Read(void* pData, unsigned int nSize)
{
	if(!m_bOpened || m_bWrite || IsEof() || pData==NULL || nSize==0)	return 0;

	const unsigned char* pSrc = reinterpret_cast< const unsigned char* >( m_pData );
	pSrc += m_nPosition;

	if(nSize > m_nLength-m_nPosition)	nSize = m_nLength - m_nPosition;

	if(m_bFile){
		_read(m_nFile, pData, nSize);
	}
	else{
//		memcpy(pData, pSrc, nSize);
		MemoryCopy(pData, pSrc, nSize);
	}
	m_nPosition += nSize;

	return nSize;
}

//=============================================================================
/**
	�X�g���[���Ɏw��T�C�Y�����o��

	@param	pData	[in] �����o���f�[�^�̃|�C���^
	@param	nSize	[in] �����o���f�[�^�̃T�C�Y

	@return			���ۂɏ����o�����T�C�Y
*/
//=============================================================================
unsigned int CBasicStream::Write(const void* pData, unsigned int nSize)
{
	if(!m_bOpened || !m_bWrite || pData==NULL || nSize==0)		return 0;

	unsigned char* pDst = (unsigned char*)reinterpret_cast< const unsigned char* >( m_pData );
	pDst += m_nPosition;

	if(!m_bFile && nSize > m_nLength-m_nPosition)	nSize = m_nLength - m_nPosition;

	if(m_bFile){
		_write(m_nFile, pData, nSize);
	}
	else{
//		memcpy(pDst, pData, nSize);
		MemoryCopy(pDst, pData, nSize);
	}
	m_nPosition += nSize;

	return nSize;
}

//=============================================================================
/**
	�������]��(4�o�C�g�P�ʂœ]������̂�(߄t�)�ϰ�Ȃ͂�)

	@param	pDst		[out] �]����|�C���^
	@param	pSrc		[in] �]�����|�C���^
	@param	nSize		[in] �]���T�C�Y
*/
//=============================================================================
void CBasicStream::MemoryCopy(void* pDst, const void* pSrc, unsigned int nSize)
{
	unsigned int* lpDst			= reinterpret_cast< unsigned int* >( pDst );
	const unsigned int* lpSrc	= reinterpret_cast< const unsigned int* >( pSrc );

	while(nSize>=4){
		*lpDst++ = *lpSrc++;
		nSize-=4;
	}

	// �[���͂��傤���Ȃ�����1�o�C�g�œ]��
	unsigned char* pDst1		= reinterpret_cast< unsigned char* >( lpDst );
	const unsigned char* pSrc1	= reinterpret_cast< const unsigned char* >( lpSrc );
	while(nSize){
		*pDst1++ = *pSrc1++;
		nSize--;
	}
}
