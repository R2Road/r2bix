#include "r2bix_input_UIInputListener.h"

namespace r2bix_ui
{
	UIInputListener::UIInputListener() :
		  mOrder( 0 )
		, mSize()
		, mbCursorResponse( false)
		, mObservationKeyContainer()
		, mCursorResponseCallback()
		, mCallback4KeyResponse()
	{}
	UIInputListener::UIInputListener( const int order ) :
		  mOrder( order )
		, mSize()
		, mbCursorResponse( false )
		, mObservationKeyContainer()
		, mCursorResponseCallback()
		, mCallback4KeyResponse()
	{}



	void UIInputListener::SetCallback4CursorResponse( const Callback4CursorResponseT& callback )
	{
		if( callback )
		{
			mbCursorResponse = true;
		}
		else
		{
			mbCursorResponse = false;
		}

		mCursorResponseCallback = callback;
	}
	void UIInputListener::SetCallback4KeyResponse( const Callback4KeyResponseT& callback )
	{
		mCallback4KeyResponse = callback;
	}

	void UIInputListener::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		mObservationKeyContainer.push_back( key_code );
	}

	bool UIInputListener::OnCursorResponse( const r2bix_input::CursorPoint cursor_point )
	{
		if( mbCursorResponse )
		{
			return mCursorResponseCallback( cursor_point );
		}

		return false;
	}
}