#include "r2bix_input_MachineInputCollector.h"

#include <numeric>

#include "r2bix_input_KeyboardInputListener.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector() :
			mKeyboardInputListener( nullptr )
		,	mObservationKeyList()
		,	mObservationKeyStates()
	{
		mObservationKeyList.fill( 0 );
	}

	void MachineInputCollector::Collect()
	{
		if( !HasWindowFocus() )
		{
			return;
		}

		if( nullptr == mKeyboardInputListener )
		{
			return;
		}

		int key_value = 0;

		for( unsigned char i = 0x01, end = static_cast< unsigned char >( mObservationKeyList.size() ); end > i; ++i )
		{
			if( 0 == mObservationKeyList[i] )
			{
				continue;
			}

			key_value = GetKeyState( i );

			if( key_value & 0x8000 )
			{
				int i = 0;
			}

			mObservationKeyStates[i] = key_value & 0x8000;
		}

		mKeyboardInputListener->Update( mObservationKeyStates );
	}



	void MachineInputCollector::AddListener( KeyboardInputListener* listener )
	{
		mKeyboardInputListener = listener;

		for( const auto k : mKeyboardInputListener->mObservationKeys )
		{
			++mObservationKeyList[k];
		}
	}
}