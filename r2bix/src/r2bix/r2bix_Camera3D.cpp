#include "r2bix_Camera3D.h"

#include "r2_quaternion.hpp"
#include "r2_matrix44_transform_vector3.hpp"

namespace r2bix
{
	Camera3D::Camera3D() :
		  mbDirty( false )
		, mPosition()
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
		const r2::Quaternion yaw( WORLD_UP, mRotationY );
		const r2::Quaternion pitch( WORLD_RIGHT, mRotationX );
		const r2::Quaternion roll( WORLD_FRONT, mRotationZ );

		mRotation = ( ( yaw * pitch ) * roll );

		mFront = mRotation * WORLD_FRONT;
		mRight = mRotation * WORLD_RIGHT;
		mUp = r2::cross( mRight, mFront );

		mbDirty = false;
	}
	void Camera3D::LookAt( const Vec3 target )
	{
		// 카메라가 target을 바라보게 만드는 행렬
		const r2::Matrix33 cam_mat = r2::build_mat33_lookat_vec3( target, mPosition, WORLD_UP );

		// 행렬을 쿼터니언으로 변환.
		mRotation = r2::mat2quat( cam_mat );

		mFront = mRotation * WORLD_FRONT;
		mRight = mRotation * WORLD_RIGHT;
		mUp = r2::cross( mRight, mFront );

		mbDirty = false;
	}

	Camera3D::Mat44 Camera3D::GetViewMatrix() const
	{
		// 카메라 행렬의 역행렬을 만든다.
		// > 카메라 행렬의 구성 : 회전 > 이동
		// > 카메라 행렬의 역행렬 구성 : 이동 > 회전

		const Mat44 rotation_matrix( r2::quat2mat44( r2::inverse( mRotation ) ) );
		const Mat44 translate_matrix( r2::build_mat44_translate_vec3( -mPosition.x, -mPosition.y, -mPosition.z ) );

		// 이동 > 회전
		return ( rotation_matrix * translate_matrix );
	}
}