#include "r2bix_input_Listener4Keyboard.h"

#include "r2_assert.hpp"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mbActivate( true )
		, mObservationKeyList()
		, mContainer4KeyStatusChangedCallback()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order ) :
		  mOrder( order )
		, mbActivate( true )
		, mObservationKeyList()
		, mContainer4KeyStatusChangedCallback()
	{}



	void Listener4Keyboard::SetCallback4KeyStatusChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStatusChangedT& callback )
	{
		if( key_code == r2bix_input::eKeyCode::VK_LBUTTON || key_code == r2bix_input::eKeyCode::VK_RBUTTON || key_code == r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Keyboard : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyList.Add( key_code );
		mContainer4KeyStatusChangedCallback.push_back( callback );
	}



	bool Listener4Keyboard::Listen( const r2bix_input::KeyCodeTypeT key_code, const r2bix_input::eKeyStep key_step )
	{
		bool ret = false;

		auto& observation_key = mObservationKeyList.GetByKeycode( key_code );

		//
		// Invalid ObservationKey
		//
		if( 0 == observation_key.key_code )
		{
			return ret;
		}

		ret = mContainer4KeyStatusChangedCallback[observation_key.key_index]( key_step );

		return ret;
	}
}