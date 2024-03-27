#include "r2bix_input_UIInputListener.h"

namespace r2bix_input
{
	UIInputListener::UIInputListener() :
		  mOrder( 0 )
		, mSize()
		, mbCursorResponse( false)
		, mObservationKeyContainer()
		, mCursorResponseCallback()
		, mContainer4KeyStatusChangedCallback()
	{}
	UIInputListener::UIInputListener( const int order ) :
		  mOrder( order )
		, mSize()
		, mbCursorResponse( false )
		, mObservationKeyContainer()
		, mCursorResponseCallback()
		, mContainer4KeyStatusChangedCallback()
	{}



	void UIInputListener::SetCallback4CursorResponse( const CursorResponseCallbackT& callback )
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
	void UIInputListener::SetCallback4KeyResponse( const r2bix_input::eKeyCode key_code, const Callback4KeyResponseT& callback )
	{
		mObservationKeyContainer.push_back( key_code );
		mContainer4KeyStatusChangedCallback.push_back( callback );
	}

	void UIInputListener::OnCursorResponse( const r2bix_ui::eCursorStatus cursor_state )
	{
		if( mbCursorResponse )
		{
			mCursorResponseCallback( cursor_state );
		}
	}
}