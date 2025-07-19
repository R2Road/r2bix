#include "r2bix_Camera3D.h"

namespace r2bix
{
	Camera3D::Camera3D() :
		  mPosition()
		, mRotationX()
		, mRotationY()
		, mRotationZ()

		, mLook( 0, 0, -1 )
		, mUp( 0, 1, 0 )
	{}
}