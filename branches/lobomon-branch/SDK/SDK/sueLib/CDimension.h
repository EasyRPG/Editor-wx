/**
	@file
	@brief		多次元構造体
	@author		sue445
*/
#ifndef _INC_CDIMENTION
#define _INC_CDIMENTION

namespace sueLib {

typedef int DimType;

template< unsigned int DIMENSION > class CDimension;

//=============================================================================
/**
	多次元構造体(1次元用)

	@note	CDimensionテンプレートの部分的な定義
*/
//=============================================================================
template<>
class CDimension< 1 >{
private:
	DimType						x;		///< 自分の次元の座標

public:
	CDimension(DimType _x=0) : x(_x){}	/// デフォルトコンストラクタ

	operator DimType() const{ return x; }
//	friend CDimension;
};

//=============================================================================
/**
	多次元構造体(n次元用)

	@note	CDimensionテンプレートの一般的な定義
*/
//=============================================================================
template< unsigned int DIMENSION >
class CDimension{
private:
	DimType						x;		///< 自分の次元の座標
	CDimension< DIMENSION - 1 >	y;		///< 1つ下の次元

public:
	CDimension(DimType _x=0, ...) : x(_x), y(*((&_x)+1)){}	/// デフォルトコンストラクタ

	// 比較演算子(2つだけ実装すれば残り4つはコピペでいいｗ)
	bool operator==(const CDimension& obj) const{ return (x==obj.x && y==obj.y); }
	bool operator< (const CDimension& obj) const{
		return (x==obj.x) ? (y<obj.y) : (x<obj.x);
	}
	bool operator!=(const CDimension& obj) const{ return !(*this==obj); }
	bool operator<=(const CDimension& obj) const{ return (*this==obj || *this<obj); }
	bool operator>=(const CDimension& obj) const{ return !(*this<obj); }
	bool operator> (const CDimension& obj) const{ return !(*this<=obj); }

//	friend CDimension;
};

typedef CDimension< 1 >	CDim1;		///< 1次元
typedef CDimension< 2 >	CDim2;		///< 2次元
typedef CDimension< 3 >	CDim3;		///< 3次元

} // end of namespace sueLib

#endif
