#include "r2bix_Camera.h"

namespace r2bix
{
	Camera::Camera(
		const PointT::ValueT& x, const PointT::ValueT& y
		, const SizeT::ValueT& width, const SizeT::ValueT& height
	) :
		  mPosition( x, y )
		, mCameraSpaceRect()
		, mWorldSpaceRect()
	{
		buildRect( mPosition, { width - 1, height - 1 } );
	}
	Camera::Camera( const PointT& position, const SizeT& size ) :
		mPosition( position )
		, mCameraSpaceRect()
		, mWorldSpaceRect()
	{
		buildRect( mPosition, { size.GetWidth() - 1, size.GetHeight() - 1 } );
	}



	void Camera::SetPoint( const PointT& point )
	{
		mPosition = point;

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}
	void Camera::SetPoint( const int x, const int y )
	{
		mPosition.Set( x, y );

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}



	void Camera::buildRect( const PointT& position, const SizeT& size )
	{
		const int half_width = size.GetWidth() / 2;
		const int half_height = size.GetHeight() / 2;

		mCameraSpaceRect.Set( -half_width, -half_height, size.GetWidth(), size.GetHeight() );

		const int min_x = position.GetX() - half_width;
		const int min_y = position.GetY() - half_height;
		mWorldSpaceRect.Set( min_x, min_y, size.GetWidth(), size.GetHeight() );
	}
}