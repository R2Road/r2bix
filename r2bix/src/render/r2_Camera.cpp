#include "pch.h"
#include "r2_Camera.h"

namespace r2
{
	Camera::Camera( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size ) :
		mPosition( position )
		, mRect()
	{
		const int min_x = mPosition.GetX() - ( size.GetWidth() / 2 );
		const int min_y = mPosition.GetY() - ( size.GetHeight() / 2 );
		mRect.Set( min_x, min_y, size.GetWidth(), size.GetHeight() );
	}

	void Camera::SetPoint( const r2::RectInt::MyPointT& point )
	{
		mPosition = point;

		const int min_x = mPosition.GetX() - ( mRect.GetSize().GetWidth() / 2 );
		const int min_y = mPosition.GetY() - ( mRect.GetSize().GetHeight() / 2 );
		mRect.Set( min_x, min_y, mRect.GetSize().GetWidth(), mRect.GetSize().GetHeight() );
	}
	void Camera::SetPoint( const int x, const int y )
	{
		mPosition.Set( x, y );

		const int min_x = mPosition.GetX() - ( mRect.GetSize().GetWidth() / 2 );
		const int min_y = mPosition.GetY() - ( mRect.GetSize().GetHeight() / 2 );
		mRect.Set( min_x, min_y, mRect.GetSize().GetWidth(), mRect.GetSize().GetHeight() );
	}
}