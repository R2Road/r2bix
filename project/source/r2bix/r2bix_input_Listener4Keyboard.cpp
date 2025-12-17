#include "r2bix_input_Listener4Keyboard.h"

#include "r2_assert.hpp"

namespace r2bix_input
{
	Listener4Keyboard::Listener4Keyboard() :
		  mOrder( 0 )
		, mMode( eListenMode::Pass )
		, mbActivate( true )
		, mObservationKeyList()
		, mContainer4KeyStepChangedCallback()
	{}
	Listener4Keyboard::Listener4Keyboard( const int order, const eListenMode mode ) :
		  mOrder( order )
		, mMode( mode )
		, mbActivate( true )
		, mObservationKeyList()
		, mContainer4KeyStepChangedCallback()
	{}



	void Listener4Keyboard::SetCallback4KeyStepChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStepChangedT& callback )
	{
		if( key_code == r2bix_input::eKeyCode::VK_LBUTTON || key_code == r2bix_input::eKeyCode::VK_RBUTTON || key_code == r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Keyboard : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyList.Add( key_code );
		mContainer4KeyStepChangedCallback.push_back( callback );
	}



	void Listener4Keyboard::Listen( const r2bix_input::KeyCodeTypeT key_code, const bool key_signal_flag )
	{
		auto& observation_key = mObservationKeyList.GetByKeycode( key_code );

		//
		// Invalid ObservationKey
		//
		if( 0 == observation_key.key_code )
		{
			return;
		}

		//
		// Update KeyStep
		//
		observation_key.key_status.Update( key_signal_flag );

		//
		// Check KeyStep Changed
		//
		if( !observation_key.key_status.GetChanged() )
		{
			return;
		}

		//
		// Callback
		//
		mContainer4KeyStepChangedCallback[observation_key.key_index]( observation_key.key_status.GetStep() );
	}
}