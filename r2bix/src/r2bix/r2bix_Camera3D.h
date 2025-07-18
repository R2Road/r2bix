#pragma once

#include "r2_Degree.h"
#include "r2_Vector3.h"

namespace r2bix
{
	class Camera3D
	{
	public:
		using Degree = r2::Degree;
		using Vec3 = r2::Vector3;

		Camera3D();

		//
		//
		//
		Vec3 GetPosition() const
		{
			return mPosition;
		}
		Vec3 GetUp() const
		{
			return mUp;
		}
		Vec3 GetLook() const
		{
			return mLook;
		}
		Degree GetRotationX() const
		{
			return mRotationX;
		}
		Degree GetRotationY() const
		{
			return mRotationY;
		}
		Degree GetRotationZ() const
		{
			return mRotationZ;
		}

		void SetPosition( const Vec3 new_position )
		{
			mPosition = new_position;
		}
		void SetUp( const Vec3 new_up )
		{
			mUp = r2::normalize( new_up );
		}
		void SetLook( const Vec3 new_look )
		{
			mLook = new_look;
		}
		void SetRotationX( const Degree rotation_x )
		{
			mRotationX = rotation_x;
		}
		void SetRotationY( const Degree rotation_y )
		{
			mRotationY = rotation_y;
		}
		void SetRotationZ( const Degree rotation_z )
		{
			mRotationZ = rotation_z;
		}

		//
		//
		//
		void Move( const Vec3 move_amount )
		{
			mPosition += move_amount;
		}

		void RotationX( const Degree rotation_amount )
		{
			mRotationX += rotation_amount;
		}
		void RotationY( const Degree rotation_amount )
		{
			mRotationY += rotation_amount;
		}
		void RotationZ( const Degree rotation_amount )
		{
			mRotationZ += rotation_amount;
		}

	private:
		Vec3 mPosition;
		Vec3 mUp;
		Vec3 mLook;

		Degree mRotationX;
		Degree mRotationY;
		Degree mRotationZ;
	};
}