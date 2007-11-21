/**
	@file
	@brief		mapを利用した多次元配列
	@author		sue445
*/
#ifndef _INC_CMAPTABLE
#define _INC_CMAPTABLE

#include "sueLib_Compile.h"
#include "CDimension.h"
#include <map>
using namespace std;

namespace sueLib {

template< class ValueType, unsigned int DIMENSION >
class CMapTable{
private:
	map< CDimension< DIMENSION >, ValueType >	m_Data;	///< データ本体
	ValueType		m_Default;	///< キーが見つからなかった時の初期値

public:
	/// デフォルトコンストラクタ
	CMapTable(){}

	//=============================================================================
	/**
		初期化

		@param		def	[in] キーが見つからなかった時の初期値

		@note		値にデフォルトコンストラクタが実装されていれば実行する必要は無い\n
					あくまで値にintなどが指定された時の救済策
	*/
	//=============================================================================
	void Init(ValueType def)
	{
		Release();
		m_Default = def;
	}

	//=============================================================================
	/**
		解放
	*/
	//=============================================================================
	void Release()
	{
		m_Data.clear();
	}

	//=============================================================================
	/**
		データが存在するかどうか

		@retval	true		見つかった
		@retval	false		見つからなかった
	*/
	//=============================================================================
	bool IsExist(CDimension< DIMENSION > dim) const
	{
//		map< CDimension, ValueType >::const_iterator it = m_Data.find(dim);
		return (m_Data.find(dim) != m_Data.end());
	}

	//=============================================================================
	/**
		データをセットする

		@param	dim			[in] 座標
		@param	bOverWrite	[in] true:キーが重複していたら上書きする / false:キーが重複してたら上書きしない
	*/
	//=============================================================================
	void Set(ValueType data, CDimension< DIMENSION > dim, bool bOverWrite=true)
	{
	//    map< CDimension< DIMENSION >,ValueType> mymapa;
	//	map<CDimension<DIMENSION>,ValueType>::const_iterator it = m_Data.find(dim);
//		map< CDimension< DIMENSION >,ValueType>::iterator it;
  //       it= m_Data.find(dim);
    	if((m_Data.find(dim)) == m_Data.end()){
			m_Data.insert( pair< CDimension< DIMENSION >, ValueType >(dim, data));
		}
		else if(bOverWrite){
			m_Data[dim] = data;
		}
	}

	//=============================================================================
	/**
		データを取得する

		@param	dim			[in] 座標

		@return				取得した値(キーが見つからなかった時は初期値を返す)
	*/
	//=============================================================================
	ValueType Get(CDimension< DIMENSION > dim) const
	{
	//	map< CDimension< DIMENSION >, ValueType >::const_iterator it = m_Data.find(dim);
		if( (m_Data.find(dim)) != m_Data.end())		return ((m_Data.find(dim))->second);
		return m_Default;
	}
};

} // end of namespace sueLib

#endif
