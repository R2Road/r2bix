#pragma once

#include "r2_Vector3.h"

namespace r2bix_render
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

	private:
		Vec3 mPosition;
		Vec3 mUp;
	};
}