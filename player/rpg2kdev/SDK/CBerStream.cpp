/**
	@file
	@brief		BER compressed integer input/output using CBasicStream.\n
				Read about BER compressed integer in this URI:\n
				http://www.stellar.ac/~komai/unix/ber/index.html

	@author		sue445
*/
#include "CBerStream.h"
#include "CBer.h"


//=============================================================================
/**
	�X�g���[������BER���k������1���o��

	@param	lpReadByte		[out] �X�g���[������ǂݍ��񂾃o�C�g�����Ԃ�(NULL�w�莞�͕Ԃ�Ȃ�)
http://kanjidict.stc.cx/4160
	@return					BER���k�����𕁒ʂ̐����ɒ������l
*/
//=============================================================================
int CBerStream::ReadBerNumber(int* lpReadByte)
{
	unsigned char c;
	int data = 0, readbyte = 0;


	while(!IsEof()){
		if(Read(&c, 1)==0)	break;
		readbyte++;

		// End of block
		if((c & 0x80)==0){
			data = (data<<7) + c;
			break;
		}
		else{
			data = (data<<7) + (c & 0x7F);
		}
	}

	// ���ۂɓǂݍ��񂾃o�C�g��Ԃ�
	if(lpReadByte)	*lpReadByte = readbyte;

	return data;
}

//=============================================================================
/**
	BER���k������1�����o��

	@param	nData	[in] �ϊ����̐���
	@param	bCalc	[in] true�̎��͕K�v�T�C�Y�̌v�Z�������s���X�g���[���ɂ͏����o���Ȃ�

	@return			�X�g���[���ɏ����o�����o�C�g��(�X�g���[���ɏ����o���̂ɕK�v�ȃo�C�g��)
*/
//=============================================================================
int CBerStream::WriteBerNumber(int nData, bool bCalc)
{
	// BER�̍\�����x�o�b�t�@�ɏ����o���Ă����K�v������
	smart_buffer buf = CBer::SetBerNumber(nData);
	if(buf.GetSize()>0 && !bCalc){
		Write(buf, buf.GetSize());
	}

	return buf.GetSize();
}

