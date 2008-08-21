/**
	@file
	@brief		�c�N�[���d�l�̔z��(1������2����)�������N���X�B\n
				�z��̒��g���o�b�t�@�Ƃ��Ē��ڊi�[����B\n
				�c�N�[���̔z��̗v�f�ԍ���1�`�����A�����ł͎����I��0�`�ň����B

	@author		sue445
*/
#ifndef _INC_CRPGARRAY
#define _INC_CRPGARRAY

#include <vector>
#include <string>
#include "sueLib/smart_buffer.h"
#include "sueLib/CMapTable.h"

using std::vector;
using std::string;
using namespace sueLib;

/// 1�����z��
class CRpgArray1 : private CMapTable< smart_buffer, 1 >{
private:
	int		m_nMaxCol;												///< ��̍ő吔

public:
	CRpgArray1() : m_nMaxCol(0){}									///< �f�t�H���g�R���X�g���N�^
	~CRpgArray1(){}													///< �f�X�g���N�^

	void Init(){ Release(); m_nMaxCol = 0; }						///< �z���������
	unsigned int GetMaxSize() const{ return m_nMaxCol; }			///< �z��̍ő�v�f����Ԃ�

	int				GetNumber(int col, int  def=0) const;			///< �������擾
	bool			GetFlag(  int col, bool def=false) const;		///< bool�^�t���O���擾
	string			GetString(int col, string def="") const;		///< ��������擾
	smart_buffer	GetData(  int col) const;						///< �o�b�t�@���擾

	void SetNumber(int col, int  data);								///< �������Z�b�g
	void SetFlag(  int col, bool data);								///< bool�^�t���O���Z�b�g
	void SetString(int col, const string& data);					///< ��������Z�b�g
	void SetData(  int col, const smart_buffer& buf);				///< �o�b�t�@���Z�b�g
};

/// 2�����z��
class CRpgArray2 : private CMapTable< smart_buffer, 2 >{
private:
	int		m_nMaxCol;														///< ��̍ő吔
	int		m_nMaxRow;														///< �s�̍ő吔

public:
	CRpgArray2() : m_nMaxCol(0), m_nMaxRow(0){}								///< �f�t�H���g�R���X�g���N�^
	~CRpgArray2(){}															///< �f�X�g���N�^

	void Init(){ Release(); m_nMaxCol = m_nMaxRow = 0; }					///< ������
	unsigned int GetMaxCol() const { return m_nMaxCol; }					///< �z��̗񐔂��擾
	unsigned int GetMaxRow() const { return m_nMaxRow; }					///< �z��̍s�����擾

	int				GetNumber(int row, int col, int  def=0) const;			///< �������擾
	bool			GetFlag(  int row, int col, bool def=false) const;		///< bool�^�t���O���擾
	string			GetString(int row, int col, string def="") const;		///< ��������擾
	smart_buffer	GetData(  int row, int col) const;						///< �o�b�t�@���擾

	void SetNumber(int row, int col, int  data);							///< �������Z�b�g
	void SetFlag(  int row, int col, bool data);							///< bool�^�t���O���Z�b�g
	void SetString(int row, int col, const string& data);					///< ��������Z�b�g
	void SetData(  int row, int col, const smart_buffer& buf);				///< �o�b�t�@���Z�b�g
};

#endif
