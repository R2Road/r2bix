#include "r2bix_input_Listener4Mouse.hpp"

#include "r2_assert.hpp"

namespace r2bix_input
{
	Listener4Mouse::Listener4Mouse() :
		  mOrder( 0 )
		, mMode( eListenMode::Pass )
		, mbActivate( true )

		, mCallback4CursorMoved()
		, mCallback4KeyStepChanged()
		, mObservationKeyList()
	{}
	Listener4Mouse::Listener4Mouse( const int order, const eListenMode mode ) :
		  mOrder( order )
		, mMode( mode )
		, mbActivate( true )

		, mCallback4CursorMoved()
		, mCallback4KeyStepChanged()
		, mObservationKeyList()
	{}



	void Listener4Mouse::SetCallback4CursorMoved( const Callback4CursorMovedT& callback )
	{
		mCallback4CursorMoved = callback;
	}
	void Listener4Mouse::SetCallback4KeyStepChanged( const Callback4KeyStepChangedT& callback )
	{
		mCallback4KeyStepChanged = callback;
	}
	void Listener4Mouse::AddObservationKey( const r2bix_input::eKeyCode key_code )
	{
		if( key_code != r2bix_input::eKeyCode::VK_LBUTTON && key_code != r2bix_input::eKeyCode::VK_RBUTTON && key_code != r2bix_input::eKeyCode::VK_MBUTTON )
		{
			R2ASSERT( false, "Listener4Mouse : 허용되지 않는 키를 등록한다." );
			return;
		}

		mObservationKeyList.Add( key_code );
	}



	void Listener4Mouse::Listen4Cursor( const r2bix_input::CursorPoint cursor_point )
	{
		if( mCallback4CursorMoved )
		{
			mCallback4CursorMoved( cursor_point );
		}
	}
	void Listener4Mouse::Listen4Key( const int key_index, const r2bix_input::eKeyStep key_step )
	{
		if( mCallback4KeyStepChanged )
		{
			mCallback4KeyStepChanged( key_index, key_step );
		}
	}
}