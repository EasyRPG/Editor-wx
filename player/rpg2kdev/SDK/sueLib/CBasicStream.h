/**
	@file
	@brief		�t�@�C�����͂ƃ��������͂𓯂��悤�Ɉ������߂̊�{�X�g���[��
	@author		sue445
*/
#ifndef _INC_CBASICSTREAM
#define _INC_CBASICSTREAM


#include "sueLib_Compile.h"
#include <stdio.h>
//#include <memory.h>


/// ��{�X�g���[��
class CBasicStream{
private:
	bool  m_bOpened;		///< �X�g���[�����J����Ă��邩�ǂ���
	bool  m_bFile;			///< �t�@�C�����̓��[�h���ǂ���
	bool  m_bWrite;			///< �����o�����[�h���ǂ���
	const void* m_pData;		///< �������f�[�^
	int   m_nFile;			///< �t�@�C���n���h��
	unsigned int m_nLength;		///< �X�g���[���̒���
	unsigned int m_nPosition;	///< �X�g���[���̌��݈ʒu

public:
	CBasicStream():
		m_bOpened(false),
		m_bFile(false),
		m_bWrite(false),
		m_pData(NULL),
		m_nFile(-1),
		m_nLength(0),
		m_nPosition(0){}	///< �R���X�g���N�^

	~CBasicStream(){ Close(); }	///< �f�X�g���N�^

	virtual bool OpenFromMemory(const void* pData, unsigned int nLength, bool bWrite=false);	///< �������f�[�^����X�g���[�����J��
	virtual bool OpenFromFile(const char* szFile, bool bWrite=false);	///< �t�@�C������X�g���[�����J��
	virtual void Close();							
///< �X�g���[�������
	virtual void SetSeek(int nPos, int nOrigin);				///< �X�g���[���|�C���^���ړ�����
	virtual unsigned int Read(void* pData, unsigned int nSize);		///< �X�g���[������ǂݍ���
	virtual unsigned int Write(const void* pData, unsigned int nSize);	///< �X�g���[���ɏ����o��

	virtual bool IsOpened()          const{ return m_bOpened; }		///< �X�g���[�����J����Ă��邩�ǂ���
	virtual bool IsEof()             const{ return (m_nPosition==m_nLength); }	///< �X�g���[�����I�[���ǂ���
	virtual bool IsWriteMode()       const{ return m_bWrite; }		///< �����o�����[�h���ǂ���
	virtual unsigned int GetLength() const{ return m_nLength; }		///< �X�g���[���̒������擾
	virtual unsigned int GetSeek()   const{ return m_nPosition; }		///< �X�g���[���̌��݈ʒu���擾

private:
	void MemoryCopy(void* pDst, const void* pSrc, unsigned int nSize);	///< �������]��
};

#endif
