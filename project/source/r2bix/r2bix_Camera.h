#pragma once

#include "r2_rect_int.hpp"

#include "r2bix_interface_camera.hpp"

namespace r2bix
{
	class Camera_deprecated : public iCamera
	{
	public:
		using RectT = r2::RectInt;
		using PointT = RectT::PointT;
		using SizeT = RectT::SizeT;



		explicit Camera_deprecated(
			  const PointT::ValueT& x, const PointT::ValueT& y
			, const SizeT::ValueT& width, const SizeT::ValueT& height
		);
		explicit Camera_deprecated( const PointT& position, const SizeT& size );



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