/**
	@file
	@brief		デバッグコンパイル時にのみ反映される設定
	@author		sue445
*/
#ifndef _INC_SUELIB_COMPILE
#define _INC_SUELIB_COMPILE

#ifdef _DEBUG
# pragma warning(disable:4786) // 識別子が長すぎるwarningを無効化
#endif

#if (_MSC_VER>1200)	// VC++.NET以降
# pragma warning(disable:4996) // 古い形式として宣言されましたwarningを無効化
#endif

#endif
