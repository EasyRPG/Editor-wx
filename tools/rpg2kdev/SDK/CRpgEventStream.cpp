/**
	@file
	@brief		�o�b�t�@����C�x���g��ǂނ��߂̃X�g���[��
	@author		sue445
*/
#include "CRpgEventStream.h"


//=============================================================================
/**
	�X�g���[������C�x���g1�����擾

	@param	event			[out] �擾�����C�x���g

	@retval	true			�C�x���g�̎擾�ɐ���
	@retval	false			�C�x���g�̎擾�Ɏ��s
*/
//=============================================================================
bool CRpgEventStream::ReadEvent(CRpgEvent& event)
{
	event.m_deqParam.clear();
	event.m_str = "";

	if(IsEof())		return false;

	// �C�x���g�R�[�h
	event.m_nEventCode = ReadBerNumber();
	if(event.m_nEventCode==0)	return false;

	// �l�X�g��
	event.m_nNest = ReadBerNumber();

	// �e�L�X�g
	event.m_str = ReadString();

	// �����̐�
	event.m_nParamMax = ReadBerNumber();
	int max = event.m_nParamMax;
	while(max-->0){
		event.m_deqParam.push_back( ReadBerNumber() );
	}

	return true;
}
