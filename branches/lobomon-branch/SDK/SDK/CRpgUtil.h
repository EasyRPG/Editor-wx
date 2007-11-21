/**
	@file
	@brief		ストリームを介せずにバッファから直接データを操作する
	@author		sue445
*/
#ifndef _INC_CRPGUTIL
#define _INC_CRPGUTIL

#include "CBer.h"
#include "CRpgArray.h"


/// ストリームを介せずにバッファから直接データを操作する
class CRpgUtil : public CBer{
private:

public:
     	//static permite llamar a las funciones si instanciar el objeto
    static int get_set_sizeused(int size, bool rw);
    static	smart_buffer	GetData(  const smart_buffer& buf);
	static	string			GetString(const smart_buffer& buf);
	static	CRpgArray1		GetArray1(const smart_buffer& buf);
	static	CRpgArray2		GetArray2(const smart_buffer& buf);
	static  CRpgArray2      GetArray2_1(const smart_buffer& buf);
};



#endif
