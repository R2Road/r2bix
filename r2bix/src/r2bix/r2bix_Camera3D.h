#pragma once

#include "r2_Vector3.h"

namespace r2bix
{
	class Camera3D
	{
	public:
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

		void SetPosition( const Vec3 new_position )
		{
			mPosition = new_position;
		}
		void SetUp( const Vec3 new_up )
		{
			mUp = r2::normalize( new_up );
		}

		//
		//
		//
		void Move( const Vec3 move_amount )
		{
			mPosition += move_amount;
		}

	private:
		Vec3 mPosition;
		Vec3 mUp;
	};
}