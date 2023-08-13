//
// # Version Rule
// - 1.0.0 : ��� ����
// - 0.1.0 : ����ڰ� �ڵ带 �ٲ� ������ ��ȭ
// - 0.0.1 : ������ ��ȭ
//
// # Last Update		: 2023.08.06 PM.03.33
// # Version			: 1.0.0
//

#pragma once

#include "r2_Direction4Sequential.h"
#include "r2_Point.h"

template<typename T>
inline r2::Point<T> operator+( const r2::Point<T>& p, const r2::Direction4Sequential& d )
{
	return r2::Point<T>( p.GetX() + d.GetX(), p.GetY() + d.GetY() );
}

template<typename T>
inline void operator+=( r2::Point<T>& p, const r2::Direction4Sequential& d )
{
	return p.Plus( d.GetX(), d.GetY() );
}



template<typename T>
inline r2::Point<T> operator-( const r2::Point<T>& p, const r2::Direction4Sequential& d )
{
	return r2::Point<T>( p.GetX() - d.GetX(), p.GetY() - d.GetY() );
}

template<typename T>
inline void operator-=( r2::Point<T>& p, const r2::Direction4Sequential& d )
{
	return p.Minus( d.GetX(), d.GetY() );
}