#pragma once

#include "r2_RectInt.h"

namespace r2bix_render
{
	class Camera
	{
	public:
		explicit Camera(
			  const r2::RectInt::PointT::ValueT& x, const r2::RectInt::PointT::ValueT& y
			, const r2::RectInt::SizeT::ValueT& width, const r2::RectInt::SizeT::ValueT& height
		);
		explicit Camera( const r2::RectInt::PointT& position, const r2::RectInt::SizeT& size );

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
		r2::RectInt::PointT GetPoint() const
		{
			return mPosition;
		}
		r2::RectInt::SizeT::ValueT GetWidth() const
		{
			return mCameraSpaceRect.GetWidth();
		}
		r2::RectInt::SizeT::ValueT GetHeight() const
		{
			return mCameraSpaceRect.GetHeight();
		}
		r2::RectInt GetCameraSpaceRect() const
		{
			return mCameraSpaceRect;
		}
		r2::RectInt GetRect() const
		{
			return mWorldSpaceRect;
		}

		//
		// Setter
		//
		void SetPoint( const r2::RectInt::PointT& point );
		void SetPoint( const int x, const int y );

	private:
		void buildRect( const r2::RectInt::PointT& position, const r2::RectInt::SizeT& size );

	private:
		r2::RectInt::PointT mPosition;
		r2::RectInt mCameraSpaceRect;
		r2::RectInt mWorldSpaceRect;
	};
}