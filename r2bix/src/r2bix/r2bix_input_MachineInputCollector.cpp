#include "r2bix_input_MachineInputCollector.h"

#include <numeric>

#include "r2bix_input_KeyboardInputListener.h"

namespace r2bix_input
{
	MachineInputCollector::MachineInputCollector() :
			mKeyboardInputListener( nullptr )
		,	mObservationKeyList()
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

		for( std::size_t i = 0, end = mKeyboardInputListener->mObservationKeyList.size(); end > i; ++i )
		{
			key_value = GetKeyState( mKeyboardInputListener->mObservationKeyList[i] );
			mKeyboardInputListener->mKeyFlags[i] = key_value & 0x8000;
		}
	}
}