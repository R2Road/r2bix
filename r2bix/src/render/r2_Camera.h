#pragma once

#include "r2/r2_RectInt.h"

namespace r2
{
	class Camera
	{
	public:
		Camera( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size );

		int GetX() const
		{
			return mPosition.GetX();
		}
		int GetY() const
		{
			return mPosition.GetY();
		}
		r2::RectInt::MyPointT GetPoint() const
		{
			return mPosition;
		}
		r2::RectInt GetRect() const
		{
			return mRect;
		}

		void SetPoint( const r2::RectInt::MyPointT& point );
		void SetPoint( const int x, const int y );

	private:
		void BuildRect( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size );

	private:
		r2::RectInt::MyPointT mPosition;
		r2::RectInt mRect;
	};
}