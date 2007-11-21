/**
	@file
	@brief		Map????.lmu(LcfMapUnit)を管理するクラス
	@author		sue445
*/
#ifndef _INC_CRPGLMU
#define _INC_CRPGLMU

#include "CRpgIOBase.h"
#include "CRpgEvent.h"
#include "CRpgLdb.h"


const int CHIP_SIZE = 16;	///< チップサイズ

/// MapXXXX.lmu(LcfMapUnit)
class CRpgLmu : public CRpgIOBase{
private:
	const char* GetHeader(){ return "LcfMapUnit"; }	///< ファイルごとの固有ヘッダ(CRpgIOBaseからオーバーライドして使います)

	int m_nChipSet;			 ///< 0x01: id de chipset
	int m_nWidth;		   	 ///< 0x02: ancho(defaul l:20)
	int m_nHeight;			 ///< 0x03: alto (default l:15)
	int m_nTypeloop;         ///< 0x0B: type of loop
	int m_nBackground;       ///< 0x1F: Parallax background	
	string	m_strPanorama;	 ///< 0x20: cadena panurama
	int m_nHorizontalpan;    ///< 0x21: Horizontal pan	Stay still
	int m_nVerticalpan;		 ///< 0x22: Vertical pan	Stay still
	int m_nHorizontalautopan;///< 0x23: Horiz. auto-pan	No
    int m_nHorizontalpanspeed;//< 0x24:	Horiz. pan speed
	int m_nVerticalautopan;	  //< 0x25:	Vert. auto-pan	No
	int m_nVerticalpanspeed; ///< 0x26:	Vert. pan speed	0		   

	// Las capas, inferior y superior
	smart_array< smart_array< unsigned short > >	m_saUpper;		///< 0x47:上層マップ
	smart_array< smart_array< unsigned short > >	m_saLower;		///< 0x47:下層マップ

//	CRpgImage imgChipSet;	///< imgaen de chipset
//	CRpgImage imgPanorama;	///< imagne panorama

public:
	//estructura de los eventeos de mapa
	struct MAPEVENT{
		MAPEVENT(): x(0), y(0){}		///< デフォルトコンストラクタ

		string strName;					///< 0x01:名前
		int  x;							///< 0x02:X座標
		int  y;							///< 0x03:Y座標
		int  data;						///< 0x04:不明(´・ω・｀)

		/// ページ単位でのマップイベント
		struct MAPEVENT_PAGE{
			MAPEVENT_PAGE():
				nWalkPos(0), nWalkMuki(0), nWalkPattern(1), bWalkHalf(false), nStart(0){}	///< コンストラクタ

			struct EVENTAPPEAR{
				EVENTAPPEAR():
					nSw1(1), nSw2(1), nVarNum(1), nVarOver(0), 
					nItem(1), nChara(1), nTimer(0){}		///< コンストラクタ

				/**
					0ビット目:◇スイッチ[%04d:%s]がON(1)\n
					1ビット目:◇スイッチ[%04d:%s]がON(2)\n
					2ビット目:◇変数[%04d:%s]の値が[%d]以上\n
					3ビット目:◇アイテム[%04d:%s]を所持\n
					4ビット目:◇主人公[%04d:%s]がいる\n
					5ビット目:◇タイマー[%d分%02秒]以下
				*/
				int nFlag;		///< 0x01:チェックボックスのチェック状態(6ビットフラグ)

				int nSw1;		///< 0x02:スイッチ(1)		初期値:1
				int nSw2;		///< 0x03:スイッチ(2)		初期値:1
				int nVarNum;	///< 0x04:変数番号			初期値:1
				int nVarOver;	///< 0x05:変数が～以上
				int nItem;		///< 0x06:アイテム～を所持	初期値:1
				int nChara;		///< 0x07:主人公～がいる	初期値:1
				int nTimer;		///< 0x08:タイマー(秒)

			} EventAppear;						///< 0x02:出現条件

			// 歩行絵関連
			string	 strWalk;					///< 0x15:ファイル名

			/**
				歩行絵の時:左上から順に0～7\n
				チップセットの時:上層チップの位置\n
				※歩行絵か上層チップかはファイル名があるかどうかで判断
			*/
			int nWalkPos;						///< 0x16:歩行絵(上層チップ)の位置

			/**
				0:上\n
				1:右\n
				2:下\n
				3:左
			*/
			int nWalkMuki;						///< 0x17:向き

			/**
				0:LEFT\n
				1:MIDDLE(初期値？)\n
				2:RIGHT
			*/
			int nWalkPattern;					///< 0x18:歩行パターン

			bool bWalkHalf;						///< 0x19:半透明かどうか

			/**
				0:◇決定キーが押されたとき\n
				1:◇主人公から触れたとき\n
				2:◇イベントから触れたとき\n
				3:◇自動的に始まる\n
				4:◇定期的に並列処理する
			*/
			int nStart;							///< 0x21:開始条件

//			int nEventDataSize;					///< 0x33:イベントデータサイズ
			vector< CRpgEvent > vctEvent;		///< 0x34:イベントデータ本体

		};	// end of struct MAPEVENT_PAGE
		smart_array< MAPEVENT_PAGE > saPage;	///< 0x05:マップイベント

	};	// end of struct MAPEVENT
	smart_array< MAPEVENT >	saMapEvent;			///< マップイベントを一括格納

public:
	CRpgLmu(){}															///< costructor 
	~CRpgLmu(){}														///< destructor

	bool Init(int nMapNum, const CRpgLdb& ldb, const char* szDir="");	///< inizializador
//	bool GetUpperChip(int x, int y, CRpgImage& img) const;				///< 上層チップを取得
//	bool GetLowerChip(int x, int y, int anime, CRpgImage& img) const;	///< 下層チップを取得

	int GetChipSet()	const{ return m_nChipSet; }						///< id de chipset
	int GetWidth()		const{ return m_nWidth;   }						///< ancho
	int GetHeight()		const{ return m_nHeight;  }						///< alto

private:
	void GetMapEvent(smart_buffer& bufSrc);								///< マップイベントを取得
	void GetOceanType(unsigned short chip, bool bOcean[4]) const;		///< チップ番号から海タイプを判別
	void GetChipPos(int nChip, bool bUpper, int* lpX, int* lpY) const;	///< チップ番号からChipSet内の座標を取得
};

#endif
