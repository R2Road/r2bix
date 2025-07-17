#include "r2bix_Camera3D.h"

namespace r2bix
{
	Camera3D::Camera3D() :
		  mPosition()
		, mUp( 0, 1, 0 )
		, mLook( 0, 0, -1 )
	{}
}