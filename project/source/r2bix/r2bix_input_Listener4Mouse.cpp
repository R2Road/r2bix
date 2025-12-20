#include "r2bix_input_Listener4Mouse.hpp"

#include "r2_assert.hpp"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mOrder( 0 )
		, mMode( eListenMode::Pass )
		, mbActivate( true )
		, mObservationKeyList()
		, mCallback4CursorMoved()
		, mContainer4KeyStepChangedCallback()
	{}
	Listener4Mouse::Listener4Mouse( const int order, const eListenMode mode ) :
		  mOrder( order )
		, mMode( mode )
		, mbActivate( true )
		, mObservationKeyList()
		, mCallback4CursorMoved()
		, mContainer4KeyStepChangedCallback()
	{}



	void Listener4Mouse::SetCallback4CursorMoved( const Callback4CursorMovedT& callback )
	{
		mCallback4CursorMoved = callback;
	}
	void Listener4Mouse::SetCallback4KeyStepChanged( const r2bix_input::eKeyCode key_code, const Callback4KeyStepChangedT& callback )
	{
		if( key_code != r2bix_input::eKeyCode::VK_LBUTTON && key_code != r2bix_input::eKeyCode::VK_RBUTTON && key_code != r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Mouse : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyList.Add( key_code );
		mContainer4KeyStepChangedCallback.push_back( callback );
	}



	bool Listener4Mouse::Listen4Cursor( const r2bix_input::CursorPoint cursor_point )
	{
		if( !mCallback4CursorMoved )
		{
			return false;
		}

		return mCallback4CursorMoved( cursor_point );
	}
	bool Listener4Mouse::Listen4Key( const r2bix_input::KeyCodeTypeT key_code, const bool key_signal_flag )
	{
		auto& observation_key = mObservationKeyList.GetByKeycode( key_code );

		//
		// Invalid ObservationKey
		//
		if( 0 == observation_key.GetKeyCode() )
		{
			return false;
		}

		//
		// Update KeyStep
		//
		observation_key.Update( key_signal_flag );

		//
		// Check KeyStep Changed
		//
		if( !observation_key.GetChanged() )
		{
			return false;
		}

		//
		// Callback
		//
		return mContainer4KeyStepChangedCallback[observation_key.GetKeyIndex()](observation_key.GetKeyStep());
	}
}