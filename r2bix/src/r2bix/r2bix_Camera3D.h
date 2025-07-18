#pragma once

#include "r2_Radian.h"
#include "r2_Vector3.h"

namespace r2bix
{
	class Camera3D
	{
	public:
		using Radian = r2::Radian;
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
		Radian GetRotationX() const
		{
			return mRotationX;
		}
		Radian GetRotationY() const
		{
			return mRotationY;
		}
		Radian GetRotationZ() const
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
		void SetRotationX( const Radian rotation_x )
		{
			mRotationX = rotation_x;
		}
		void SetRotationY( const Radian rotation_y )
		{
			mRotationY = rotation_y;
		}
		void SetRotationZ( const Radian rotation_z )
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

		void RotationX( const Radian rotation_amount )
		{
			mRotationX += rotation_amount;
		}
		void RotationY( const Radian rotation_amount )
		{
			mRotationY += rotation_amount;
		}
		void RotationZ( const Radian rotation_amount )
		{
			mRotationZ += rotation_amount;
		}

	private:
		Vec3 mPosition;
		Vec3 mUp;
		Vec3 mLook;

		Radian mRotationX;
		Radian mRotationY;
		Radian mRotationZ;
	};
}