#include "r2bix_input_Listener4Mouse.h"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mOrder( 0 )
		, mbMousePositionUse( false)
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeys()
		, mKeyStatusContainer()

		, mCursorMovedCallback()
	{}
	Listener4Mouse::Listener4Mouse( const int order, const bool position_use, const bool left_click, const bool right_click ) :
		  mOrder( order )
		, mbMousePositionUse( position_use )
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeys()
		, mKeyStatusContainer()
	{
		if( left_click )
		{
			mObservationKeys.Add( r2bix_input::eKeyCode::VK_LBUTTON );
		}
		if( right_click )
		{
			mObservationKeys.Add( r2bix_input::eKeyCode::VK_RBUTTON );
		}

		mKeyStatusContainer.resize( mObservationKeys.Size(), eKeyStatus::None );
	}

	void Listener4Mouse::UpdateCursor( const r2bix_input::CursorPoint cursor_point )
	{
		if( mbMousePositionUse )
		{
			mCursorPoint_Last = mCursorPoint_Current;
			mCursorPoint_Current = cursor_point;

			if( mCursorPoint_Last != mCursorPoint_Current )
			{
				if( mCursorMovedCallback )
				{
					mCursorMovedCallback( cursor_point );
				}
			}
		}
	}
	void Listener4Mouse::UpdateKey( const int key_index, const bool key_flag )
	{
		if( key_flag )
		{
			switch( mKeyStatusContainer[key_index] )
			{
			case eKeyStatus::None:
				mKeyStatusContainer[key_index] = eKeyStatus::Push;
				break;

			case eKeyStatus::Push:
				mKeyStatusContainer[key_index] = eKeyStatus::Pressed;
				break;

			//case eKeyStatus::Pressed:
			//	break;

			}
		}
		else
		{
			switch( mKeyStatusContainer[key_index] )
			{
			//case eKeyStatus::None:
			//	break;

			case eKeyStatus::Push:
			case eKeyStatus::Pressed:
				mKeyStatusContainer[key_index] = eKeyStatus::Release;
				break;

			case eKeyStatus::Release:
				mKeyStatusContainer[key_index] = eKeyStatus::None;
				break;
			}
		}
	}
}