#include "r2bix_render_Camera.h"

namespace r2bix_render
{
	Camera::Camera(
		const r2::RectInt::PointT::ValueT& x, const r2::RectInt::PointT::ValueT& y
		, const r2::RectInt::SizeT::ValueT& width, const r2::RectInt::SizeT::ValueT& height
	) :
		  mPosition( x, y )
		, mCameraSpaceRect()
		, mWorldSpaceRect()
	{
		buildRect( mPosition, { width - 1, height - 1 } );
	}
	Camera::Camera( const r2::RectInt::PointT& position, const r2::RectInt::SizeT& size ) :
		mPosition( position )
		, mCameraSpaceRect()
		, mWorldSpaceRect()
	{
		buildRect( mPosition, { size.GetWidth() - 1, size.GetHeight() - 1 } );
	}

	void Camera::SetPoint( const r2::RectInt::PointT& point )
	{
		mPosition = point;

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}
	void Camera::SetPoint( const int x, const int y )
	{
		mPosition.Set( x, y );

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}

	void Camera::buildRect( const r2::RectInt::PointT& position, const r2::RectInt::SizeT& size )
	{
		const int half_width = size.GetWidth() / 2;
		const int half_height = size.GetHeight() / 2;

		mCameraSpaceRect.Set( -half_width, -half_height, size.GetWidth(), size.GetHeight() );

		const int min_x = position.GetX() - half_width;
		const int min_y = position.GetY() - half_height;
		mWorldSpaceRect.Set( min_x, min_y, size.GetWidth(), size.GetHeight() );
	}
}