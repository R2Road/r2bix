#include "r2bix_Camera3D.h"

#include "r2_Quaternion.h"

namespace r2bix
{
	Camera3D::Camera3D() :
		  mPosition()
		, mRotationX()
		, mRotationY()
		, mRotationZ()

		, mFront( WORLD_FRONT )
		, mUp( WORLD_UP )
		, mRight( WORLD_RIGHT )

		, mRotation()
	{}

	void Camera3D::UpdateVectors()
	{
		const r2::Quaternion yaw( r2::VEC3_Y, mRotationY );
		const r2::Quaternion pitch( WORLD_RIGHT, mRotationX );
		const r2::Quaternion roll( WORLD_FRONT, mRotationZ );

		mRotation = ( ( yaw * pitch ) * roll );

		mFront = mRotation * WORLD_FRONT;
		mRight = mRotation * WORLD_RIGHT;
		mUp = r2::cross( mRight, mFront );
	}
}