#include "pch.h"
#include "r2_Camera.h"

namespace r2
{
	Camera::Camera( const r2::RectInt& rect ) :
		mPosition( rect.GetOrigin().GetX(), rect.GetOrigin().GetY() )
		, mRect( rect )
	{}
}