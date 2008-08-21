/**
	@file
	@brief		�c�N�[���d�l�̔z��(1������2����)�������N���X�B\n
				�z��̒��g���o�b�t�@�Ƃ��Ē��ڊi�[����B\n
				�c�N�[���̔z��̗v�f�ԍ���1�`�����A�����ł͎����I��0�`�ň����B

	@author		sue445
*/
#include "CRpgArray.h"
#include "CRpgUtil.h"


////////////////////////////////////
// 1�����z��
////////////////////////////////////
//=============================================================================
/**
	�o�b�t�@�̒��g��BER���k�����Ƃ��Ď擾

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾��������
*/
//=============================================================================
int CRpgArray1::GetNumber(int col, int def) const
{
	return (IsExist(CDim1(col))) ? CRpgUtil::GetBerNumber(Get(CDim1(col))) : def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g��bool�^(0 or 1)�Ƃ��Ď擾

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾�����t���O
*/
//=============================================================================
bool CRpgArray1::GetFlag(int col, bool def) const
{
	return (IsExist(CDim1(col))) ? (CRpgUtil::GetBerNumber(Get(CDim1(col))) != 0 ) : def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g�𕶎���Ƃ��Ď擾(string��)

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾����������
*/
//=============================================================================
string CRpgArray1::GetString(int col, string def) const
{
//	return (IsExist(CDim1(col))) ? CRpgUtil::GetString(Get(CDim1(col))) : def;
	if(IsExist(CDim1(col))){
		smart_buffer buf = Get(CDim1(col));
		string str(buf, buf.GetSize());
		return str;
	}
	return def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g�����̂܂܎擾

	@param	col			[in] �z��̗v�f�ԍ�(1�`)

	@return				�擾�����o�b�t�@
*/
//=============================================================================
smart_buffer CRpgArray1::GetData(int col) const
{
	smart_buffer buf;
	return (IsExist(CDim1(col))) ? Get(CDim1(col)) : buf;
}

//=============================================================================
/**
	�o�b�t�@��BER���k�������Z�b�g

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	data		[in] ����
*/
//=============================================================================
void CRpgArray1::SetNumber(int col, int data)
{
	Set(CRpgUtil::SetBerNumber(data), CDim1(col));
	if(col > m_nMaxCol)		m_nMaxCol = col;
}

//=============================================================================
/**
	�o�b�t�@��bool�^(0 or 1)���Z�b�g

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	data		[in] �t���O
*/
//=============================================================================
void CRpgArray1::SetFlag(int col, bool data)
{
	Set(CRpgUtil::SetBerNumber(data), CDim1(col));
	if(col > m_nMaxCol)		m_nMaxCol = col;
}

//=============================================================================
/**
	�o�b�t�@�ɕ�������Z�b�g

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	data		[in] ������
*/
//=============================================================================
void CRpgArray1::SetString(int col, const string& data)
{
	smart_buffer buf(data.length());
	memcpy(buf, data.c_str(), data.length());
	Set(buf, CDim1(col));
	if(col > m_nMaxCol)		m_nMaxCol = col;
}

//=============================================================================
/**
	�o�b�t�@���Z�b�g

	@param	col			[in] �z��̗v�f�ԍ�(1�`)
	@param	buf			[in] �o�b�t�@
*/
//=============================================================================
void CRpgArray1::SetData(int col, const smart_buffer& buf)
{
	Set(buf, CDim1(col));
	if(col > m_nMaxCol)		m_nMaxCol = col;
}


////////////////////////////////////
// 2�����z��
////////////////////////////////////
//=============================================================================
/**
	�o�b�t�@�̒��g��BER���k�����Ƃ��Ď擾

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾��������
*/
//=============================================================================
int CRpgArray2::GetNumber(int row, int col, int def) const
{
	return (IsExist(CDim2(col,row))) ? CRpgUtil::GetBerNumber(Get(CDim2(col,row))) : def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g��bool�^(0 or 1)�Ƃ��Ď擾

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾�����t���O
*/
//=============================================================================
bool CRpgArray2::GetFlag(int row, int col, bool def) const
{
	return (IsExist(CDim2(col,row))) ? (CRpgUtil::GetBerNumber(Get(CDim2(col,row))) != 0 ) : def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g�𕶎���Ƃ��Ď擾(string��)

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	def			[in] �v�f�����݂��Ȃ������ꍇ�̏����l

	@return				�擾����������
*/
//=============================================================================
string CRpgArray2::GetString(int row, int col, string def) const
{
//	return (IsExist(CDim2(col,row))) ? CRpgUtil::GetString(Get(CDim2(col,row))) : def;
	if(IsExist(CDim2(col,row))){
		smart_buffer buf = Get(CDim2(col,row));
		string str(buf, buf.GetSize());
		return str;
	}
	return def;
}

//=============================================================================
/**
	�o�b�t�@�̒��g�����̂܂܎擾

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)

	@return				�擾�����o�b�t�@
*/
//=============================================================================
smart_buffer CRpgArray2::GetData(int row, int col) const
{
	smart_buffer buf;
	return (IsExist(CDim2(col,row))) ? Get(CDim2(col,row)) : buf;
}

//=============================================================================
/**
	�o�b�t�@��BER���k�������Z�b�g

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	data		[in] ����
*/
//=============================================================================
void CRpgArray2::SetNumber(int row, int col, int data)
{
	Set(CRpgUtil::SetBerNumber(data), CDim2(col,row));
	if(col > m_nMaxCol)		m_nMaxCol = col;
	if(row > m_nMaxRow)		m_nMaxRow = row;
}

//=============================================================================
/**
	�o�b�t�@��bool�^(0 or 1)���Z�b�g

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	data		[in] �t���O
*/
//=============================================================================
void CRpgArray2::SetFlag(int row, int col, bool data)
{
	Set(CRpgUtil::SetBerNumber(data), CDim2(col,row));
	if(col > m_nMaxCol)		m_nMaxCol = col;
	if(row > m_nMaxRow)		m_nMaxRow = row;
}

//=============================================================================
/**
	�o�b�t�@�ɕ�������Z�b�g

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	data		[in] ������
*/
//=============================================================================
void CRpgArray2::SetString(int row, int col, const string& data)
{
	smart_buffer buf(data.length());
	memcpy(buf, data.c_str(), data.length());
	Set(buf, CDim2(col,row));
	if(col > m_nMaxCol)		m_nMaxCol = col;
	if(row > m_nMaxRow)		m_nMaxRow = row;
}

//=============================================================================
/**
	�o�b�t�@���Z�b�g

	@param	row			[in] �z��̐e�v�f�̔ԍ�(1�`)
	@param	col			[in] �z��̎q�v�f�̔ԍ�(1�`)
	@param	buf			[in] �o�b�t�@
*/
//=============================================================================
void CRpgArray2::SetData(int row, int col, const smart_buffer& buf)
{
	Set(buf, CDim2(col,row));
	if(col > m_nMaxCol)		m_nMaxCol = col;
	if(row > m_nMaxRow)		m_nMaxRow = row;
}
