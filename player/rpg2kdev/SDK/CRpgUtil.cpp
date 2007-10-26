/**
	@file
	@brief		�X�g���[��������Ƀo�b�t�@���璼�ڃf�[�^�𑀍삷��
	@author		sue445
*/
#include "CRpgUtil.h"
#include "CRpgIOBase.h"


//=============================================================================
/**
	�o�b�t�@���璼�ڃf�[�^���擾

	@param	buf			[in] ���͌��o�b�t�@

	@return				�擾�����o�b�t�@
*/
//=============================================================================
smart_buffer CRpgUtil::GetData(const smart_buffer& buf)
{
	CRpgIOBase st;
	smart_buffer temp;

	return (st.OpenFromMemory(buf.GetConstPtr(), buf.GetSize())) ? st.ReadData() : temp;
}

//=============================================================================
/**
	�o�b�t�@���當������擾

	@param	buf			[in] ���͌��o�b�t�@

	@return				�擾����������
*/
//=============================================================================
string CRpgUtil::GetString(const smart_buffer& buf)
{
	CRpgIOBase st;

	return (st.OpenFromMemory(buf.GetConstPtr(), buf.GetSize())) ? st.ReadString() : "";
}

//=============================================================================
/**
	�c�N�[���d�l��1�����z���ǂݍ���

	@param	buf		[in] ���͌��o�b�t�@

	@return			�擾����1�����z��
*/
//=============================================================================
CRpgArray1 CRpgUtil::GetArray1(const smart_buffer& buf)
{
	int col;
	CRpgIOBase		st;
	CRpgArray1		array;


	// �o�b�t�@������������Ă��Ȃ�
	if(buf.GetSize()==0)		return array;

	// �ǂݍ��ݗp�X�g���[���̏�����
	st.OpenFromMemory(buf.GetConstPtr(), buf.GetSize());

	// �f�[�^���i�[����
	while(!st.IsEof()){
		col = st.ReadBerNumber();
		if(col==0)	break;
		array.SetData(col, st.ReadData());
	}

	return array;
}

//=============================================================================
/**
	�c�N�[���d�l��2�����z���ǂݍ���

	@param	buf		[in] ���͌��o�b�t�@

	@return			�擾����2�����z��
*/
//=============================================================================
CRpgArray2 CRpgUtil::GetArray2(const smart_buffer& buf)
{
	int row, col, max;
	CRpgIOBase		st;
	CRpgArray2		array;


	// �o�b�t�@������������Ă��Ȃ�
	if(buf.GetSize()==0)		return array;

	// �ǂݍ��ݗp�X�g���[���̏�����
	st.OpenFromMemory(buf.GetConstPtr(), buf.GetSize());

	// ��ԍŏ��ɂ͔z��̃T�C�Y���i�[����Ă���
	max = st.ReadBerNumber();

	// �f�[�^���i�[����
	while(!st.IsEof()){
		row = st.ReadBerNumber();
		for(;;){
			col = st.ReadBerNumber();
			if(col==0)	break;
			array.SetData(row, col, st.ReadData());
		}
	}

	return array;
}
