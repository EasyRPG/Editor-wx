/**
	@file
	@brief		ツクール2000/2003系ファイルの入出力の基本となるクラス
	@note		いろいろなところからこのクラスを継承しますし、このクラス単体でも使用できます。

	@author		sue445
*/
#ifndef _INC_CRPGIOBASE
#define _INC_CRPGIOBASE

#include "CBerStream.h"
#include "CRpgArray.h"
#include "CRpgUtil.h"
#include <stdio.h>
#include <string>

using std::string;
/*
#ifndef FNAME_MAX32
#define FNAME_MAX32		512
#endif

#ifndef ZeroMemory
#define ZeroMemory(buf,size)	memset(buf, 0, size)
#endif

#define MAX_RPGNAME		21		///< 全角10文字
*/

/*
#pragma pack(push)
#pragma pack(1) //構造体のメンバ境界を1バイトにする

#ifndef POINT
/// 座標構造体
struct POINT{
	int x;	///< X位置
	int y;	///< Y位置
};
#endif

#pragma pack(pop)
*/

/// ツクール系ファイルの入出力の基本となるクラス
class CRpgIOBase : public CBerStream{
private:
	virtual const char* GetHeader(){ return ""; }		///< ファイル識別用の文字列(継承先で指定します)

protected:
	bool OpenFile(const char* szFile);					///< ファイルを開く(識別チェック有り)
	bool bInit;											///< 初期化されているかどうか

public:
	CRpgIOBase() : bInit(false){}						///< コンストラクタ
	~CRpgIOBase(){}										///< デストラクタ

	smart_buffer	ReadData();							///< データを読み込む
	string			ReadString();						///< 文字列を読み込む
	bool			IsInit() const{ return bInit; }		///< 初期化されているかどうか

	void ByteToBool(unsigned char num, bool flag[8]) const;	///< unsigned char -> bool配列

	//=============================================================================
	/**
		2次元smart_arrayを[y][x]配列とみなして初期化する

		@param	array		[out] smart_arrayの二次元配列
		@param	x			[in] X方向の要素数
		@param	y			[in] Y方向の要素数
	*/
	//=============================================================================
	template< class T >
	void InitArray2(smart_array< smart_array< T > >& array, int x, int y) const
	{
		array.Resize(y);
		for(int j = 0; j < y; j++){
			array[j].Resize(x);
		}
	}	///< 2次元smart_arrayを[y][x]配列とみなして初期化する

	//=============================================================================
	/**
		バッファの中身を2次元smart_arrayにぶち込む

		@param	array		[out] smart_arrayの二次元配列
		@param	buf			[in] 入力元のバッファ
		@param	x			[in] X方向の要素数
		@param	y			[in] Y方向の要素数

		@retval	true		配列の格納に成功
		@retval	false		配列の格納に失敗
	*/
	//=============================================================================
	template< class T >
	bool BufferToArray2(smart_array< smart_array< T > >& array, smart_buffer& buf, int x, int y) const
	{
		CBasicStream st;
		T data;

		// なぜか初期化失敗
		if(!st.OpenFromMemory(buf, buf.GetSize()))	return false;

		// 先にsmart_arrayを初期化
		InitArray2(array, x, y);

		for(int j = 0; j < y; j++){
			for(int i = 0; i < x; i++){
				st.Read(&data, sizeof(T));
				array[j][i] = data;
			}
		}

		return true;
	}	///< バッファの中身を2次元smart_arrayにぶち込む
};

#endif
