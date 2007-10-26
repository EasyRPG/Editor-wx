/**
	@file
	@brief		�C�x���g�f�[�^1��
	@author		sue445
*/
#include "CRpgEvent.h"


//=============================================================================
/**
	�C�x���g���̈������擾

	@param	lpData			[out] �擾��������

	@retval	true			�����̎擾�ɐ���
	@retval	false			�����̎擾�Ɏ��s�^�����X�^�b�N����
*/
//=============================================================================
bool CRpgEvent::GetParam(int* lpData)
{
	if(m_deqParam.empty())	return false;

	if(lpData)	*lpData = m_deqParam.front();
	m_deqParam.pop_front();

	return true;
}
