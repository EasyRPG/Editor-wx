/**
	@file
	@brief		�X�g���[��������Ƀo�b�t�@���璼�ڃf�[�^�𑀍삷��
	@author		sue445
*/
#ifndef _INC_CRPGUTIL
#define _INC_CRPGUTIL

#include "CBer.h"
#include "CRpgArray.h"


/// �X�g���[��������Ƀo�b�t�@���璼�ڃf�[�^�𑀍삷��
class CRpgUtil : public CBer{
public:
	static	smart_buffer	GetData(  const smart_buffer& buf);
	static	string			GetString(const smart_buffer& buf);
	static	CRpgArray1		GetArray1(const smart_buffer& buf);
	static	CRpgArray2		GetArray2(const smart_buffer& buf);
};

#endif
