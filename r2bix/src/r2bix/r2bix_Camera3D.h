#pragma once

#include "r2_Quaternion.h"
#include "r2_Radian.h"
#include "r2_Vector3.h"

namespace r2bix
{
	class Camera3D
	{
	public:
		using Quat = r2::Quaternion;
		using Radian = r2::Radian;
		using Vec3 = r2::Vector3;

		static constexpr Vec3 WORLD_FRONT{ 0, 0, -1 };
		static constexpr Vec3 WORLD_UP{ 0, 1, 0 };
		static constexpr Vec3 WORLD_RIGHT{ 1, 0, 0 };



		Camera3D();

		//
		//
		//
		Vec3 GetPosition() const
		{
			return mPosition;
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

		Vec3 GetFront() const
		{
			return mFront;
		}
		Vec3 GetUp() const
		{
			return mUp;
		}
		Vec3 GetRight() const
		{
			return mRight;
		}

		//
		//
		//
		void SetPosition( const Vec3 new_position )
		{
			mPosition = new_position;
		}
		void SetRotationX( const Radian rotation_to )
		{
			mRotationX = rotation_to;
		}
		void SetRotationY( const Radian rotation_to )
		{
			mRotationY = rotation_to;
		}
		void SetRotationZ( const Radian rotation_to )
		{
			mRotationZ = rotation_to;
		}

		void Move( const Vec3 move_by )
		{
			mPosition += move_by;
		}
		void RotationX( const Radian rotation_by )
		{
			mRotationX += rotation_by;
		}
		void RotationY( const Radian rotation_by )
		{
			mRotationY += rotation_by;
		}
		void RotationZ( const Radian rotation_by )
		{
			mRotationZ += rotation_by;
		}

		//
		//
		//
		void UpdateVectors();

	private:
		Vec3 mPosition;
		Radian mRotationX;
		Radian mRotationY;
		Radian mRotationZ;

		Vec3 mFront;
		Vec3 mUp;
		Vec3 mRight;

		Quat mRotation;
	};
}