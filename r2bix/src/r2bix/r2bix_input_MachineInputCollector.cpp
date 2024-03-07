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

		//
		// for Test
		//
		mObservationKeyList[0x1B] = 1;	// esc
		mObservationKeyList[0x41] = 1;	// a
		mObservationKeyList[0x44] = 1;	// d
		mObservationKeyList[0x53] = 1;	// s
		mObservationKeyList[0x57] = 1;	// w
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

		for( std::size_t i = 0, end = mKeyboardInputListener->mObservationKeyList.size(); end > i; ++i )
		{
			key_value = GetKeyState( mKeyboardInputListener->mObservationKeyList[i] );
			mKeyboardInputListener->mKeyFlags[i] = key_value & 0x8000;
		}
	}
}