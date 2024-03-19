#include "r2bix_input_Listener4Keyboard.h"

#include "r2_Assert.h"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mObservationKeyContainer()
		, mContainer4KeyStatusChangedCallback()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order ) :
		  mOrder( order )
		, mObservationKeyContainer()
		, mContainer4KeyStatusChangedCallback()
	{}



	void Listener4Keyboard::SetKeyStatusChangedCallback( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback )
	{
		if( key_code == r2bix_input::eKeyCode::VK_LBUTTON || key_code == r2bix_input::eKeyCode::VK_RBUTTON || key_code == r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Keyboard : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyContainer.Add( key_code );
		mContainer4KeyStatusChangedCallback.push_back( callback );
	}



	void Listener4Keyboard::UpdateKey( const int key_index, const bool key_flag )
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