#include "r2bix_input_MouseListener.h"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mbMousePositionUse( false)
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeys()
		, mKeyStatusContainer()
	{}
	Listener4Mouse::Listener4Mouse( const bool position_use, const bool left_click, const bool right_click ) :
		  mbMousePositionUse( position_use )
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

	void Listener4Mouse::Update( const ObservationKeyStatesT& observation_key_states, const r2bix_input::CursorPoint cursor_point )
	{
		if( mbMousePositionUse )
		{
			mCursorPoint_Last = mCursorPoint_Current;
			mCursorPoint_Current = cursor_point;
		}

		for( std::size_t i = 0u, end = mKeyStatusContainer.size(); end > i; ++i )
		{
			if( observation_key_states.test( mObservationKeys[i]) )
			{
				switch( mKeyStatusContainer[i] )
				{
				case eKeyStatus::None:
					mKeyStatusContainer[i] = eKeyStatus::Push;
					break;

				case eKeyStatus::Push:
					mKeyStatusContainer[i] = eKeyStatus::Pressed;
					break;

				//case eKeyStatus::Pressed:
				//	break;

				}
			}
			else
			{
				switch( mKeyStatusContainer[i] )
				{
				//case eKeyStatus::None:
				//	break;

				case eKeyStatus::Push:
				case eKeyStatus::Pressed:
					mKeyStatusContainer[i] = eKeyStatus::Release;
					break;

				case eKeyStatus::Release:
					mKeyStatusContainer[i] = eKeyStatus::None;
					break;
				}
			}
		}
	}
}