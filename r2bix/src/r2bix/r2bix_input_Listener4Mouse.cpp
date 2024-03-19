#include "r2bix_input_Listener4Mouse.h"

#include "r2_Assert.h"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mOrder( 0 )
		, mbMousePositionUse( false)
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeyContainer()

		, mCursorMovedCallback()
		, mContainer4KeyStatusChangedCallback()
	{}
	Listener4Mouse::Listener4Mouse( const int order ) :
		mOrder( order )
		, mbMousePositionUse()
		, mCursorPoint_Current()
		, mCursorPoint_Last()
		, mObservationKeyContainer()

		, mCursorMovedCallback()
		, mContainer4KeyStatusChangedCallback()
	{}



	void Listener4Mouse::SetKeyStatusChangedCallback( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback )
	{
		if( key_code != r2bix_input::eKeyCode::VK_LBUTTON && key_code != r2bix_input::eKeyCode::VK_RBUTTON && key_code != r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Mouse : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyContainer.Add( key_code );
		mContainer4KeyStatusChangedCallback.push_back( callback );
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
			switch( mObservationKeyContainer[key_index].key_status )
			{
			case eKeyStatus::None:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Push;
				mContainer4KeyStatusChangedCallback[key_index]( mObservationKeyContainer[key_index].key_status );
				break;

			case eKeyStatus::Push:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Pressed;
				mContainer4KeyStatusChangedCallback[key_index]( mObservationKeyContainer[key_index].key_status );
				break;

			//case eKeyStatus::Pressed:
			//	break;

			}
		}
		else
		{
			switch( mObservationKeyContainer[key_index].key_status )
			{
			//case eKeyStatus::None:
			//	break;

			case eKeyStatus::Push:
			case eKeyStatus::Pressed:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::Release;
				mContainer4KeyStatusChangedCallback[key_index]( mObservationKeyContainer[key_index].key_status );
				break;

			case eKeyStatus::Release:
				mObservationKeyContainer[key_index].key_status = eKeyStatus::None;
				mContainer4KeyStatusChangedCallback[key_index]( mObservationKeyContainer[key_index].key_status );
				break;
			}
		}
	}
}