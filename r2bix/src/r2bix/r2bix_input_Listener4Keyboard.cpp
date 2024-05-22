#include "r2bix_input_Listener4Keyboard.h"

#include "r2_Assert.h"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mbActivate( true )
		, mObservationKeyContainer()
		, mContainer4KeyStatusChangedCallback()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order ) :
		  mOrder( order )
		, mbActivate( true )
		, mObservationKeyContainer()
		, mContainer4KeyStatusChangedCallback()
	{}



	void Listener4Keyboard::SetCallback4KeyStatusChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback )
	{
		if( key_code == r2bix_input::eKeyCode::VK_LBUTTON || key_code == r2bix_input::eKeyCode::VK_RBUTTON || key_code == r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Keyboard : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyContainer.Add( key_code );
		mContainer4KeyStatusChangedCallback.push_back( callback );
	}



	void Listener4Keyboard::UpdateKey( r2bix_input::KeyCodeTypeT key_code, const bool key_flag )
	{
		auto& observation_key = mObservationKeyContainer.GetByKeycode( key_code );

		//
		// Invalid ObservationKey
		//
		if( 0 == observation_key.key_code )
		{
			return;
		}

		//
		//
		//
		if( key_flag )
		{
			switch( observation_key.key_status )
			{
			case eKeyStatus::None:
				observation_key.key_status = eKeyStatus::Push;
				mContainer4KeyStatusChangedCallback[observation_key.key_index]( observation_key.key_status );
				break;

			case eKeyStatus::Push:
				observation_key.key_status = eKeyStatus::Pressed;
				mContainer4KeyStatusChangedCallback[observation_key.key_index]( observation_key.key_status );
				break;

				//case eKeyStatus::Pressed:
				//	break;

			}
		}
		else
		{
			switch( observation_key.key_status )
			{
				//case eKeyStatus::None:
				//	break;

			case eKeyStatus::Push:
			case eKeyStatus::Pressed:
				observation_key.key_status = eKeyStatus::Release;
				mContainer4KeyStatusChangedCallback[observation_key.key_index]( observation_key.key_status );
				break;

			case eKeyStatus::Release:
				observation_key.key_status = eKeyStatus::None;
				mContainer4KeyStatusChangedCallback[observation_key.key_index]( observation_key.key_status );
				break;
			}
		}
	}
}