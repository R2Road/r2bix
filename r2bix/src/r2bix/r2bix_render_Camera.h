#pragma once

#include "r2_RectInt.h"

namespace r2bix_render
{
	class Camera
	{
	public:
		using RectT = r2::RectInt;
		using PointT = RectT::PointT;
		using SizeT = RectT::SizeT;



		explicit Camera(
			  const PointT::ValueT& x, const PointT::ValueT& y
			, const SizeT::ValueT& width, const SizeT::ValueT& height
		);
		explicit Camera( const PointT& position, const SizeT& size );



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
		PointT GetPoint() const
		{
			return mPosition;
		}
		SizeT::ValueT GetWidth() const
		{
			return mCameraSpaceRect.GetWidth();
		}
		SizeT::ValueT GetHeight() const
		{
			return mCameraSpaceRect.GetHeight();
		}
		RectT GetCameraSpaceRect() const
		{
			return mCameraSpaceRect;
		}
		RectT GetRect() const
		{
			return mWorldSpaceRect;
		}



		//
		// Setter
		//
		void SetPoint( const PointT& point );
		void SetPoint( const int x, const int y );



	private:
		void buildRect( const PointT& position, const SizeT& size );



	private:
		PointT mPosition;
		RectT mCameraSpaceRect;
		RectT mWorldSpaceRect;
	};
}