#pragma once

#include "r2_matrix44.hpp"
#include "r2_quaternion.hpp"
#include "r2_radian.hpp"
#include "r2_vector3.hpp"

#include "r2bix_interface_camera.hpp"

namespace r2bix
{
	constexpr r2::Vector3 WORLD_FRONT{ 0, 0, -1 };
	constexpr r2::Vector3 WORLD_UP{ 0, 1, 0 };
	constexpr r2::Vector3 WORLD_RIGHT{ 1, 0, 0 };

	class Camera3D : public iCamera
	{
	public:
		using Mat44 = r2::Matrix44;
		using Quat = r2::Quaternion;
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
			mbDirty = true;
		}
		void Move( const Vec3 move_by )
		{
			mPosition += move_by;
			mbDirty = true;
		}

		void SetRotationX( const Radian rotation_to )
		{
			mRotationX = rotation_to;
			mbDirty = true;
		}
		void SetRotationY( const Radian rotation_to )
		{
			mRotationY = rotation_to;
			mbDirty = true;
		}
		void SetRotationZ( const Radian rotation_to )
		{
			mRotationZ = rotation_to;
			mbDirty = true;
		}
		void RotationX( const Radian rotation_by )
		{
			mRotationX += rotation_by;
			mbDirty = true;
		}
		void RotationY( const Radian rotation_by )
		{
			mRotationY += rotation_by;
			mbDirty = true;
		}
		void RotationZ( const Radian rotation_by )
		{
			mRotationZ += rotation_by;
			mbDirty = true;
		}

		//
		//
		//
		void UpdateVectors();
		void LookAt( const Vec3 target );

		Mat44 GetViewMatrix() const;



	private:
		bool mbDirty;

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