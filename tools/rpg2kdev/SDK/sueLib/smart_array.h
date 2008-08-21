/**
	@file
	@brief		�Q�ƃJ�E���^���X�}�[�g�|�C���^
				�E�E�E�̔z���

	@author		trino
*/
#ifndef __SMART_ARRAY__
#define __SMART_ARRAY__

#include "sueLib_Compile.h"

/// �Q�ƃJ�E���^���X�}�[�g�|�C���^
template< class P >
class smart_array
{
public:
	//=============================================================================
	/**
		�f�t�H���g�R���X�g���N�^�B
		�E�E�E�E������ۂł���B
	*/
	//=============================================================================
	smart_array():m_pnCounter( NULL ),m_aObject( NULL ),m_nSize( 0 ){}	///< �f�t�H���g�R���X�g���N�^


	//=============================================================================
	/**
		�R�s�[�R���X�g���N�^�B
		�A�b�v�L���X�g��OK

		@param	p		[in] smart_array�̔z��f�[�^
	*/
	//=============================================================================
	template< class D >
	smart_array( const smart_array< D >& p ){
		if( p != NULL ){
			//�|�C���^�R�s�[
			m_aObject = p.m_aObject;
			m_pnCounter = p.m_pnCounter;
			//�Q�ƃJ�E���^�{�{
			(*m_pnCounter)++;
			//�T�C�Y
			m_nSize = p.m_nSize;
		}else{
			m_aObject = NULL;
			m_pnCounter = NULL;
			m_nSize = 0;
		}
	}	///< �R�s�[�R���X�g���N�^
	smart_array( const smart_array& p ){
		if( p != NULL ){
			m_aObject = p.m_aObject;
			m_pnCounter = p.m_pnCounter;
			(*m_pnCounter)++;
			m_nSize = p.m_nSize;
		}else{
			m_aObject = NULL;
			m_pnCounter = NULL;
			m_nSize = 0;
		}
	}

	//=============================================================================
	/**
		���|�C���^�R���X�g���N�^(��)
		�T�C�Y��n���Ƃ��낢����������Ƃ����邩���B

		@param	p		[in] �z��|�C���^
		@param	nSize	[in] �z��̃T�C�Y
	*/
	//=============================================================================
	smart_array( P* p, unsigned int nSize = 0xFFFFFFFF ){
		//�I�u�W�F�N�g�ۊ�
		m_aObject = p;
		//����p���m��
		m_pnCounter = new unsigned int;
		//�Q�ƃJ�E���^�Z�b�g
		*m_pnCounter = 1;
		//�T�C�Y
		m_nSize = nSize;
	}	///< ���|�C���^�R���X�g���N�^

//	smart_array( unsigned int nSize ){ smart_array(new P[nSize], nSize); }	///< �T�C�Y�w��R���X�g���N�^


	//=============================================================================
	/**
		������Z�q

		@param	p		[in] smart_array�̔z��f�[�^

		@return			�������g�̃I�u�W�F�N�g
	*/
	//=============================================================================
	template< class D >
	smart_array< P >& operator =( const smart_array< D >& p ){
		//���g���₳�����폜
		Release();
		if( p != NULL ){
			//�����o�R�s�[
			m_pnCounter = p.m_pnCounter;
			m_aObject = p.m_aObject;
			m_nSize = p.m_nSize;
			//�Q�ƃJ�E���^UP!!
			(*m_pnCounter)++;
		}
		return *this;
	}	///< ������Z�q
	smart_array& operator =( const smart_array& p ){
		Release();
		if( p != NULL ){
			m_pnCounter = p.m_pnCounter;
			m_aObject = p.m_aObject;
			m_nSize = p.m_nSize;
			(*m_pnCounter)++;
		}
		return *this;
	}
	template< class D >
	smart_array< P >& operator =( D* p ){
		//�T�C�Y���킩��Ȃ��̂Ŕ񐄏�

		//���g�������폜
		Release();
		//�ʂ�ہI�I
		if( p != NULL ){
			//����p���m��
			m_pnCounter = new unsigned int;
			//���
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = 0xFFFFFFFF;
		}

		return *this;
	}

	//=============================================================================
	/**
		�ė��p

		@param	p		[in] smart_array�̔z��f�[�^
		@param	nSize	[in] �z��̃T�C�Y

		@return			�������g�̃I�u�W�F�N�g
	*/
	//=============================================================================
	template< class D >
	smart_array< P >& Reset( D* p, unsigned int nSize ){
		Release();
		if( p != NULL ){
			//����p���m��
			m_pnCounter = new unsigned int;
			//���
			m_aObject = p;
			*m_pnCounter = 1;
			m_nSize = nSize;
		}
		return *this;
	}	///< �ė��p

	//=============================================================================
	/**
		�傫�������w�肵�č쐬����(�^�͎������g�̌^�ŌŒ�)

		@param	nSize	[in] �z��̃T�C�Y

		@return			�������g�̃I�u�W�F�N�g
	*/
	//=============================================================================
	smart_array< P >& Resize(unsigned int nSize ){
#ifndef _DEBUG
		return Reset(new P[nSize], nSize);
#else
		P* p = new P[nSize];
		if(p==NULL)		throw "Buffer Error";
		return Reset(p, nSize);
#endif
	}	///< �z��̑傫�������w�肵�č쐬

	//=============================================================================
	/**
		�������g�̌^�̃T�C�Y���擾

		@return			�������g�̌^�̃T�C�Y
	*/
	//=============================================================================
	unsigned int SizeOf() const { return sizeof(P); }	///< �������g�̌^�̃T�C�Y���擾


	//=============================================================================
	/**
		������R�s�[���Ă���

		@param		p		�R�s�[��
	*/
	//=============================================================================
	void Copy(const smart_array p){
		/*
		Resize(p.GetSize());
		for(unsigned int i = 0; i < GetSize(); i++){
			*(GetPtr()+i) = p[i];
		}
		*/
		if(p!=NULL){
			unsigned int i = p.GetSize();
			Resize(i);
			P* p1		= m_aObject;
			const P* p2	= p.m_aObject;
			while(i-->0){
				*p1++ = *p2++;
			}
		}
	}


	//=============================================================================
	/**
		�f�B�X�g���N�^�B
	*/
	//=============================================================================
	virtual ~smart_array(){
		Release();
	}	///< �f�B�X�g���N�^

	//=============================================================================
	/**
		�z��̂ӂ������B

		@param	i		[in] �z��̗v�f�ԍ�

		@return			�z��̗v�f
	*/
	//=============================================================================
#ifndef _DEBUG
	P& operator[]( unsigned int i ) const { return m_aObject[i]; }	///< �z��̂ӂ������
#else
	//=============================================================================
	/**
		�z��̂ӂ������B

		@note			�f�o�b�O�p�B�z��𒴂���Ɨ�O�𓊂��Ă���B
		@param	i		[in] �z��̗v�f�ԍ�

		@return			�z��̗v�f
	*/
	//=============================================================================
	P& operator[]( unsigned int i ) const {
		if( i < m_nSize ){
			return  m_aObject[i];
		}else{
			throw "Buffer Overflow";
		}
	}	//< �z��̂ӂ������
#endif

	//=============================================================================
	/**
		��r���Z�q�B
		NULL�`�F�b�N�ɂ��g���܂��B

		@param	p		[in] �|�C���^��smart_array�̃I�u�W�F�N�g

		@retval	true	2�͓�������
		@retval	false	2�͈Ⴄ����
	*/
	//=============================================================================
	bool operator==( const P* p ) const{
		return m_aObject == p;
	}	///< ��r���Z�q
	bool operator==( const smart_array< P >& p ) const{
		return m_aObject == p.m_aObject;
	}
	bool operator!=( const P* p ) const{
		return m_aObject != p;
	}
	bool operator!=( const smart_array< P >& p ) const{
		return m_aObject != p.m_aObject;
	}

	//=============================================================================
	/**
		�R���e�i�I�Ȃ���

		@return			�z��̗v�f��
	*/
	//=============================================================================
#ifndef _DEBUG
	unsigned int GetSize() const { return m_nSize; }	///< �z��̃T�C�Y���擾
#endif
#ifdef _DEBUG
	unsigned int GetSize() const {
		if( m_nSize == 0xFFFFFFFF ){
			throw "undefined size";
		}else{
			return m_nSize;
		}
	}	///< �R���e�i�I�Ȃ���
#endif
	P* GetPtr(){ return m_aObject; }				///< �z��̐擪�̃|�C���^���擾
	P* GetEndPtr(){ return m_aObject + m_nSize; }	///< �z��̏I�[�̃|�C���^���擾
	const P* GetConstPtr() const{ return m_aObject; }	///< �z��̐擪�̃|�C���^���擾(const��)


#if (_MSC_VER<=1200)	// VC++6.0�ȑO
	friend class smart_array;
#else					// VC++.NET�ȍ~
	template< class Y > friend class smart_array;
#endif

//protected:
	//=============================================================================
	/**
		�I�u�W�F�N�g�����
	*/
	//=============================================================================
	void Release(){
		//�ʂ�ے�
		if( m_aObject == NULL ){
			return;
		}
		//�Q�ƃJ�E���^���O�Ȃ琧��DATA���폜
		if( --(*m_pnCounter) == 0 ){
			delete m_pnCounter;
			delete[] m_aObject;
		}
		//�����̂ӂ������B
		m_pnCounter = NULL;
		m_aObject = NULL;
		m_nSize = 0;
		return;
	}	///< �I�u�W�F�N�g�����


//private:
protected:
	unsigned int* m_pnCounter;	///< �Q�ƃJ�E���^
	P* m_aObject;				///< �z��f�[�^�{��

	unsigned int m_nSize;		///< �z��̗v�f��


};


#endif