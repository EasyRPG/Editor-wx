/**
	@file
	@brief		�o�b�t�@����C�x���g��ǂނ��߂̃X�g���[��
	@author		sue445
*/
#ifndef _INC_CRPGEVENTSTREAM
#define _INC_CRPGEVENTSTREAM

#include "CRpgIOBase.h"
#include "CRpgEvent.h"


/// �o�b�t�@����C�x���g��ǂނ��߂̃X�g���[��
class CRpgEventStream : public CRpgIOBase{
public:
	CRpgEventStream(){}					///< �R���X�g���N�^
	~CRpgEventStream(){}				///< �f�X�g���N�^

	bool ReadEvent(CRpgEvent& event);	///< �C�x���g��1�ǂݍ���
};

#endif
