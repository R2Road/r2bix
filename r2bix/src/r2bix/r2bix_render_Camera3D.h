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
		void SetPosition( const Vec3 new_position )
		{
			mPosition = new_position;
		}

	private:
		Vec3 mPosition;
	};
}