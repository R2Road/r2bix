#pragma once

#include "r2/r2_RectInt.h"

namespace r2render
{
	class Camera
	{
	public:
		Camera( const r2::RectInt::MyPointT& position, const r2::RectInt::MySizeT& size );

		//
		// Getter
		//
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
		r2::RectInt::MySizeT::ValueT GetWidth() const
		{
			return mRect.GetWidth();
		}
		r2::RectInt::MySizeT::ValueT GetHeight() const
		{
			return mRect.GetHeight();
		}
		r2::RectInt GetRect() const
		{
			return mRect;
		}

		//
		// Setter
		//
		void SetPoint( const r2::RectInt::MyPointT& point );
		void SetPoint( const int x, const int y );

	private:
		void buildRect( const r2::RectInt::MyPointT& position, const r2::RectInt::MySizeT& size );

	private:
		r2::RectInt::MyPointT mPosition;
		r2::RectInt mRect;
	};
}