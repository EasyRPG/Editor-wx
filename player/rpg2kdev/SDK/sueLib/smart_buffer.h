/**
	@file
	@brief		�I�u�W�F�N�g������Ɏ����I�Ƀo�b�t�@���������N���X
	@author		sue445
*/
#ifndef _INC_SMART_BUFFER
#define _INC_SMART_BUFFER

#include "smart_array.h"
#include <memory.h>
#include <string.h>

namespace sueLib {

/// �I�u�W�F�N�g������Ɏ����I�Ƀo�b�t�@���������N���X
class smart_buffer : public smart_array<char>{
public:
	smart_buffer(unsigned int nSize=0){ New(nSize); }		///< �R���X�g���N�^
	smart_buffer(const char* str){ SetString(str); }		///< �R���X�g���N�^(������ŏ�����)

	operator char*() { return GetPtr(); } 					///< �o�b�t�@�̃|�C���^�𒼐ڎ擾����

	template< typename T >
	char* operator+(T nOffset){ return GetPtr()+nOffset; }	///< �o�b�t�@�擪����̃I�t�Z�b�g

	//=============================================================================
	/**
		�o�b�t�@���쐬����

		@note				�쐬���ꂽ�o�b�t�@�͎����I��0�ŏ����������
		@param	nSize		[in] �o�b�t�@�̃T�C�Y

		@return				�o�b�t�@�̃|�C���^
	*/
	//=============================================================================
	char* New(unsigned int nSize=0)
	{
		Close();
		if(nSize){
			Resize(nSize);
			memset(GetPtr(), 0, GetSize());
		}
		return GetPtr();
	}	///< �o�b�t�@���쐬

	//=============================================================================
	/**
		������ŏ���������

		@param	str			[in] ������

		@return				������̃|�C���^
	*/
	//=============================================================================
	const char* SetString(const char* str)
	{
		int length = strlen(str);
		New(length+1);
		if(length>0)	strcpy(GetPtr(), str);
		return GetPtr();
	}


	void Close(){ Release(); }	///< �o�b�t�@�����


	//=============================================================================
	/**
		�������f�[�^����smart_buffer���쐬

		@param	pSrc		[in] �o�b�t�@�̃|�C���^
		@param	nSrcSize	[in] �o�b�t�@�T�C�Y

		@retval	true		�o�b�t�@�̍쐬�ɐ���
		@retval	false		�o�b�t�@�̍쐬�Ɏ��s
	*/
	//=============================================================================
	bool OpenFromData(const char* pSrc, unsigned int nSrcSize)
	{
		if(pSrc && nSrcSize && New(nSrcSize)){
			memcpy(GetPtr(), pSrc, GetSize());
			return true;
		}
		return false;
	}	///< �f�[�^����쐬

	//=============================================================================
	/**
		�������f�[�^����smart_buffer���쐬

		@note				�ʂ�smart_buffer�̓��e���R�s�[����
		@param	buf			[in] �R�s�[����smart_buffer�I�u�W�F�N�g

		@retval	true		�o�b�t�@�̍쐬�ɐ���
		@retval	false		�o�b�t�@�̍쐬�Ɏ��s
	*/
	//=============================================================================
	bool OpenFromData(const smart_buffer& buf)
	{
		if(buf.GetConstPtr() && buf.GetSize()){
			return OpenFromData(buf.GetConstPtr(), buf.GetSize());
		}
		return false;
	}

// stdio.h�C���N���[�h���̂ݎg�p
#ifdef _INC_STDIO
	//=============================================================================
	/**
		�t�@�C������쐬

		@param	szFile		[in] �t�@�C����
		@param	nOffset		[in] �ǂݍ��݊J�n�I�t�Z�b�g
		@param	nSize		[in] �ǂݍ��݃T�C�Y(�ȗ�����nOffset����t�@�C���I�[�܂œǂݍ���)
		@param	bTxtMode	[in] �e�L�X�g�p�ɏI�[��NULL��t������

		@note		stdio.h�C���N���[�h���̂ݎg�p�\

		@retval	true		�ǂݍ��ݐ���
		@retval	false		�ǂݍ��ݎ��s
	*/
	//=============================================================================
	bool OpenFromFile(const char* szFile, unsigned int nOffset=0, unsigned int nSize=0, bool bTxtMode=false)
	{
		FILE* fp = fopen(szFile, "rb");
		if(fp){
			fseek(fp, 0, SEEK_END);
			unsigned int filesize = (unsigned int)ftell(fp);

			if(nSize==0 || nSize+nOffset>filesize)		nSize = filesize - nOffset;
			New(nSize+bTxtMode);
			fseek(fp, nOffset, SEEK_SET);
			fread(GetPtr(), nSize, 1, fp);
			fclose(fp);
			return true;
		}
		return false;
	}	///< �t�@�C������쐬

	//=============================================================================
	/**
		�t�@�C���ɕۑ�

		@param	szFile		[in] �t�@�C����
		@param	bTxtSave	[in] �e�L�X�g�Ƃ��ĕۑ�����Ȃ� true / �o�C�i���Ƃ��ĕۑ�����Ȃ� false
		@param	nOffset		[in] �����o���J�n�I�t�Z�b�g
		@param	nSize		[in] �����o���T�C�Y(�ȗ�����nOffset����t�@�C���I�[�܂ŏ����o��)

		@retval	true		�����o������
		@retval	false		�����o�����s
	*/
	//=============================================================================
	bool SaveToFile(char* szFile, bool bTxtSave=false, unsigned int nOffset=0, unsigned int nSize=0) const
	{
		if(GetConstPtr() && GetSize()>0){
			// �o�C�i���ۑ�
			if(!bTxtSave){
				FILE* fp = fopen(szFile, "wb");
				if(fp){
					if(nSize==0 || nSize+nOffset>GetSize())		nSize = GetSize() - nOffset;
					fwrite(GetConstPtr()+nOffset, nSize, 1, fp);
					fclose(fp);
					return true;
				}
			}
			// �e�L�X�g�ۑ�
			else{
				FILE* fp = fopen(szFile, "wt");
				if(fp){
					fwrite(GetConstPtr()+nOffset, strlen(GetConstPtr()+nOffset), 1, fp);
					fclose(fp);
					return true;
				}
			}
		}
		return false;
	}	///< �t�@�C���ɕۑ�
#endif

};

} // end of namespace sueLib


#endif
