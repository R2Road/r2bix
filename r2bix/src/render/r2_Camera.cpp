#include "pch.h"
#include "r2_Camera.h"

namespace r2
{
	Camera::Camera( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size ) :
		mPosition( position )
		, mRect( position.GetX(), position.GetY(), size.GetWidth(), size.GetHeight() )
	{}
}